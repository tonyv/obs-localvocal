#include <util/base.h>
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio.hpp>

#include "aws-transcribe.h"
#include "plugin-support.h"
#include "whisper-utils/resample-utils.h"
#include "transcription-utils.h"
#include "presigned-url.h"
#include "eventstream.h"
#include "websocket-client.h"

#include <nlohmann/json.hpp>
#include <queue>
#include <mutex>
#include <future>
#include <thread>
#include <random>
#include <string>
#include <iostream>

using json = nlohmann::json;
using tcp = boost::asio::ip::tcp;
namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;



class TranscriptionHandler::Impl {
public:
	using MessageCallback = TranscriptionHandler::MessageCallback;

	explicit Impl(transcription_filter_data *gf_, MessageCallback callback)
		: gf(gf_),
		  messageCallback(callback),
		  running(false)
	{
		//auto& ws = webSocketClient->ws();
		//auto& buffer = webSocketClient->buffer();

		access_key = std::getenv("AWS_ACCESS_KEY_ID") ? std::getenv("AWS_ACCESS_KEY_ID") : "";
		secret_key = std::getenv("AWS_SECRET_ACCESS_KEY") ? std::getenv("AWS_SECRET_ACCESS_KEY") : "";

		session_token = std::getenv("AWS_SESSION_TOKEN") ? std::getenv("AWS_SESSION_TOKEN") : "";
		region = std::getenv("AWS_DEFAULT_REGION") ? std::getenv("AWS_DEFAULT_REGION") : "us-west-2";
		AWSTranscribePresignedURL transcribe_url_generator(access_key, secret_key, session_token, region);

		// Generate signed url to connect to
		request_url = transcribe_url_generator.get_request_url(
			sampleRate, languageCode, mediaEncoding, numberOfChannels, channelIdentification);

		parseUrl();
		sslSetup();

		//webSocketClient = new WebSocketClient(ioc, ctx, host, port, target);
		webSocketClient = std::make_shared<WebSocketClient>(ioc, ctx, host, port, target);
		// Start io_context in a separate thread
        wsThread = std::thread([this]() {
            std::cout << "IO context thread starting" << std::endl;
            try {
				webSocketClient->run();
                ioc.run();
                std::cout << "IO context finished running" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "IO context error: " << e.what() << std::endl;
            }
        });

        // Wait for connection to be established
        std::this_thread::sleep_for(std::chrono::seconds(2));
		//webSocketClient->run();
		//ioc.run();
		
	}


	void start_reading()
    {
        // Asynchronously read messages
		auto& ws = webSocketClient->ws();
		//boost::beast::flat_buffer& buffer = webSocketClient->buffer();
		boost::beast::flat_buffer buffer;
		webSocketClient->receive();
    }

	void start()
	{
		std::cout << "Starting Transcribe" << std::endl;
		if (!running) {
			running = true;

			// Start WebSocket connection in its own thread
			std::cout << "Starting websocket connection thread" << std::endl;
            //wsThread = std::thread([this]() {
				//std::cout << "Starting websocket connection" << std::endl;
				//ioc.run();
            //});

			processingThread =
				std::async(std::launch::async, [this]() { processAudioQueue(); });

		}
	}

	void stop()
	{
		std::cout << "Stopping thread" << std::endl;
		if (running) {
			running = false;
			if (processingThread.valid())
				processingThread.wait();
		}
	}

private:
	transcription_filter_data *gf;
	MessageCallback messageCallback;
	std::queue<std::vector<int16_t>> audioQueue;
	std::mutex mutex;
	std::atomic<bool> running;
	std::future<void> processingThread;
	const int sampleRate = 8000;
	const int numberOfChannels = 2;
	const bool channelIdentification = true;
	const int bytesPerSample = 2;
	const std::string languageCode = "en-US";
	const std::string mediaEncoding = "pcm";
	std::string access_key;
	std::string secret_key;
	std::string session_token;
	std::string region;
	std::string request_url;
	std::string host;
	std::string port;
	std::string target;
	net::io_context ioc;
	ssl::context ctx{ssl::context::tlsv12_client};
	std::shared_ptr<WebSocketClient> webSocketClient;
	std::thread wsThread;
	

	void parseUrl() {
        //std::string host, port, target;
        std::string::size_type protocol_end = request_url.find("://");
        if (protocol_end != std::string::npos) {
            std::string::size_type host_start = protocol_end + 3;
            std::string::size_type host_end = request_url.find(':', host_start);
            if (host_end != std::string::npos) {
                host = request_url.substr(host_start, host_end - host_start);
                std::string::size_type port_end = request_url.find('/', host_end);
                port = request_url.substr(host_end + 1, port_end - host_end - 1);
                target = request_url.substr(port_end);
            } else {
                host_end = request_url.find('/', host_start);
                host = request_url.substr(host_start, host_end - host_start);
                port = "443"; // Default HTTPS port
                target = request_url.substr(host_end);
            }
        } else {
            throw std::runtime_error("Invalid URL format");
        }


	}

	void sslSetup() {

		load_certificate_from_file(ctx, "starfield_root_cert.cer");

        ctx.set_verify_mode(ssl::verify_peer);
        ctx.set_verify_callback([](bool preverified, ssl::verify_context& ctx) {
            if (!preverified) {
                X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
                char subject_name[256];
                X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
                std::cout << "Verification failed for: " << subject_name << std::endl;
            }
            return preverified;
        });
        ctx.set_default_verify_paths();
	}

	void handleIncomingMessage(const std::vector<uint8_t>& message)
	{
		try {
			//json j = json::parse(message);
			//auto& ws = webSocketClient->ws();
			//auto& buffer = webSocketClient->buffer();

			// TODO: handle incoming message from AWS Transcribe
			//webSocketClient
			// 
			// messageCallback(type, text, start_timestamp, end_timestamp);
		} catch (json::parse_error &e) {
			obs_log(LOG_ERROR, "Failed to parse JSON message: %s", e.what());
		} catch (json::type_error &e) {
			obs_log(LOG_ERROR, "Failed to parse JSON message: %s", e.what());
		}
	}

	void processAudioQueue()
	{
		while (running) {

			if (!webSocketClient || !webSocketClient->is_connected()) {
				std::cerr << "WebSocket not connected, waiting..." << std::endl;
				std::this_thread::sleep_for(std::chrono::seconds(1));
				continue;
			}
			// get data from buffer and resample to 16kHz
			uint64_t start_timestamp_offset_ns = 0;
			uint64_t end_timestamp_offset_ns = 0;

			const int ret = get_data_from_buf_and_resample(
				gf, start_timestamp_offset_ns, end_timestamp_offset_ns);
			if (ret != 0) {
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				continue;
			}
			std::cout << "Buffer size: " << gf->resampled_buffer.size << std::endl;

			std::vector<float> audio_input;
			audio_input.resize(gf->resampled_buffer.size / sizeof(float));
			circlebuf_pop_front(&gf->resampled_buffer, audio_input.data(),
					    audio_input.size() * sizeof(float));

			/*
			std::vector<int16_t> pcmData(audio_input.size());
			for (size_t i = 0; i < audio_input.size(); ++i) {
				pcmData[i] = static_cast<int16_t>(audio_input[i] * 32767.0f);
			}
			*/
			std::vector<int16_t> pcmData(audio_input.begin(), audio_input.end());

			if (!pcmData.empty()) {
				// TODO: prepare data to send to AWS Transcribe
				sendAudioData(pcmData);
				start_reading();
			} else {
				std::cout << "Awaiting PCM data" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}

			if (!gf->cleared_last_sub) {
				// check if we should clear the current sub depending on the minimum subtitle duration
				uint64_t now = now_ms();
				if ((now - gf->last_sub_render_time) > gf->max_sub_duration) {
					// clear the current sub, call the callback with an empty string
					obs_log(gf->log_level,
						"Clearing current subtitle. now: %lu ms, last: %lu ms",
						now, gf->last_sub_render_time);
					clear_current_caption(gf);
				}
			}
		}
	}


	std::vector<int16_t> encodePcmToByteBuffer(const std::vector<int16_t>& pcmData) {
		std::vector<int16_t> byteBuffer(pcmData.size() * sizeof(int16_t));

		for (size_t i = 0; i < pcmData.size(); ++i) {
			uint16_t value = static_cast<uint16_t>(pcmData[i]);
			byteBuffer[i * 2] = static_cast<uint8_t>(value & 0xFF);
			byteBuffer[i * 2 + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
		}

		return byteBuffer;
	}

	void load_certificate_from_file(ssl::context& ctx, const std::string& filename)
	{
		std::ifstream cert_file(filename);
		if (!cert_file.is_open()) {
			throw std::runtime_error("Failed to open certificate file");
		}

		std::stringstream cert_stream;
		cert_stream << cert_file.rdbuf();
		std::string cert = cert_stream.str();

		ctx.add_certificate_authority(
			boost::asio::buffer(cert.data(), cert.size())
		);
	}

	std::vector<int16_t> audioBuffer;

	void sendAudioData(const std::vector<int16_t> &audioData)
	{
		std::lock_guard<std::mutex> lock(mutex);
		webSocketClient->verify_connection();

		if (!webSocketClient) {
       		std::cerr << "WebSocket client is null!" << std::endl;
			return;
		}
		webSocketClient->verify_connection();

		audioBuffer.insert(audioBuffer.end(), audioData.begin(), audioData.end());
		// TODO send audio data to AWS Transcribe

		webSocketClient->send_next_chunk(audioBuffer);
		audioBuffer.clear();
	}
};

TranscriptionHandler::TranscriptionHandler(transcription_filter_data *gf_, MessageCallback callback)
	: pimpl(std::make_unique<Impl>(std::move(gf_), std::move(callback)))
{
}

TranscriptionHandler::~TranscriptionHandler() = default;

TranscriptionHandler::TranscriptionHandler(TranscriptionHandler &&) noexcept = default;
TranscriptionHandler &TranscriptionHandler::operator=(TranscriptionHandler &&) noexcept = default;

void TranscriptionHandler::start()
{
	pimpl->start();
}
void TranscriptionHandler::stop()
{
	pimpl->stop();
}
