
#include "audio-file-utils.h"
#include "plugin-support.h"

#include <obs-module.h>

#include <fstream>
#include <vector>
#include <cstdint>
#include <functional>

#if defined(_WIN32) || defined(__APPLE__)

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/frame.h>
#include <libavutil/mem.h>
#include <libavutil/opt.h>
#include <libswresample/swresample.h>
#include <libavutil/log.h>
}

std::vector<std::vector<uint8_t>>
read_audio_file(const char *filename, std::function<void(int, int)> initialization_callback)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        obs_log(LOG_ERROR, "Could not open file: %s", filename);
        return {};
    }

    // Get file size
    file.seekg(0, std::ios::end);
    size_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Ensure file size is even (for 16-bit samples)
    file_size = (file_size / 2) * 2;

    // Assume stereo
    const int num_channels = 2;
    const int sample_rate = 8000;
    
    // Call initialization callback
    initialization_callback(sample_rate, num_channels);

    // Read the entire file into a temporary buffer
    std::vector<int16_t> temp_buffer(file_size / sizeof(int16_t));
    file.read(reinterpret_cast<char*>(temp_buffer.data()), file_size);

    if (file.fail() && !file.eof()) {
        obs_log(LOG_ERROR, "Failed to read from file: %s", std::strerror(errno));
        return {};
    }

    std::streamsize bytes_read = file.gcount();

    // Create output buffers for each channel
    std::vector<std::vector<uint8_t>> buffer(num_channels);
    size_t samples_per_channel = bytes_read / (sizeof(int16_t) * num_channels);
    
    for (int channel = 0; channel < num_channels; channel++) {
        buffer[channel].reserve(samples_per_channel * 2); // 2 bytes per sample
    }

    // Process samples
    for (size_t i = 0; i < bytes_read / sizeof(int16_t); i += num_channels) {
        for (int channel = 0; channel < num_channels; channel++) {
            int16_t sample = temp_buffer[i + channel];

            // Little-endian byte order
            buffer[channel].push_back(static_cast<uint8_t>(sample & 0xFF));
            buffer[channel].push_back(static_cast<uint8_t>((sample >> 8) & 0xFF));
        }
    }

    file.close();
    return buffer;
}

void write_audio_wav_file(const std::string &filename, const float *pcm32f_data,
			  const size_t frames)
{
	av_log_set_level(AV_LOG_QUIET);

	AVFormatContext *formatContext = nullptr;
	AVCodecContext *codecContext = nullptr;
	AVStream *stream = nullptr;
	AVFrame *frame = nullptr;
	AVPacket packet;
	int ret = 0;

	avformat_alloc_output_context2(&formatContext, nullptr, nullptr, filename.c_str());
	if (!formatContext) {
		obs_log(LOG_ERROR, "Failed to allocate output context");
		return;
	}

	const AVCodec *codec = avcodec_find_encoder(AV_CODEC_ID_PCM_F32LE);
	if (!codec) {
		obs_log(LOG_ERROR, "Failed to find encoder");
		return;
	}

	stream = avformat_new_stream(formatContext, codec);
	if (!stream) {
		obs_log(LOG_ERROR, "Failed to create new stream");
		return;
	}

	codecContext = avcodec_alloc_context3(codec);
	if (!codecContext) {
		obs_log(LOG_ERROR, "Failed to allocate codec context");
		return;
	}

	codecContext->sample_fmt = AV_SAMPLE_FMT_FLTP;
	codecContext->sample_rate = 16000;
	codecContext->channels = 1;
	codecContext->channel_layout = AV_CH_LAYOUT_MONO;
	codecContext->bit_rate = 64000;
	codecContext->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;

	if (avcodec_open2(codecContext, codec, nullptr) < 0) {
		obs_log(LOG_ERROR, "Failed to open codec");
		return;
	}

	if (avcodec_parameters_from_context(stream->codecpar, codecContext) < 0) {
		obs_log(LOG_ERROR, "Failed to copy codec parameters to stream");
		return;
	}

	if (avio_open(&formatContext->pb, filename.c_str(), AVIO_FLAG_WRITE) < 0) {
		obs_log(LOG_ERROR, "Failed to open file");
		return;
	}

	if (avformat_write_header(formatContext, nullptr) < 0) {
		obs_log(LOG_ERROR, "Failed to write header");
		return;
	}

	const int frame_size = 1024;
	const int frame_size_in_bytes = frame_size * sizeof(float);
	frame = av_frame_alloc();
	frame->nb_samples = frame_size;
	frame->format = codecContext->sample_fmt;
	frame->ch_layout = codecContext->ch_layout;

	ret = av_frame_get_buffer(frame, 0);
	if (ret < 0) {
		char errbuf[AV_ERROR_MAX_STRING_SIZE];
		av_make_error_string(errbuf, AV_ERROR_MAX_STRING_SIZE, ret);
		obs_log(LOG_ERROR, "Failed to allocate frame buffer: %s", errbuf);
		return;
	}

	for (size_t i = 0; i < frames; i += frame_size) {
		av_init_packet(&packet);
		packet.data = nullptr;
		packet.size = 0;

		for (int k = 0; k < codecContext->channels; k++) {
			if (i + frame_size < frames) {
				memcpy(frame->data[k], pcm32f_data + i, frame_size_in_bytes);
			} else {
				// zero pad the last frame
				memset(frame->data[k], 0, frame_size_in_bytes);
				memcpy(frame->data[k], pcm32f_data + i,
				       (frames - i) * sizeof(float));
			}
		}

		ret = avcodec_send_frame(codecContext, frame);
		if (ret < 0) {
			obs_log(LOG_ERROR, "Failed to send frame");
			break;
		}

		ret = avcodec_receive_packet(codecContext, &packet);
		if (ret < 0) {
			obs_log(LOG_ERROR, "Failed to receive packet");
			break;
		}

		av_packet_rescale_ts(&packet, codecContext->time_base, stream->time_base);
		packet.stream_index = stream->index;

		ret = av_interleaved_write_frame(formatContext, &packet);
		if (ret < 0) {
			obs_log(LOG_ERROR, "Failed to write frame");
			break;
		}

		av_packet_unref(&packet);
	}

	if (ret >= 0) {
		av_write_trailer(formatContext);
	}

	av_frame_free(&frame);
	avcodec_free_context(&codecContext);
	avformat_free_context(formatContext);

	if (ret < 0) {
		obs_log(LOG_ERROR, "Failed to write audio file %s", filename.c_str());
	}
}

#else

std::vector<std::vector<uint8_t>>
read_audio_file(const char *filename, std::function<void(int, int)> initialization_callback)
{
	obs_log(LOG_ERROR, "Reading audio files is not supported on this platform");
	return {};
}

void write_audio_wav_file(const std::string &filename, const float *pcm32f_data,
			  const size_t frames)
{
	obs_log(LOG_ERROR, "Writing audio files is not supported on this platform");
}

#endif
