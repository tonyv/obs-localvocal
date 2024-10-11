#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio.hpp>
#include <iostream>

#include "websocket-client.h"
#include "eventstream.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;
using tcp = boost::asio::ip::tcp;

WebSocketClient::WebSocketClient(net::io_context& ioc, ssl::context& ctx,
                                 const std::string& host, const std::string& port,
                                 const std::string& target)
    : resolver_(net::make_strand(ioc))
    , ws_(net::make_strand(ioc), ctx)
    , host_(host)
    , port_(port)
    , target_(target)
{
    // Initialize the WebSocketClient object here
    // For example:
    // - Set any default options or configurations for the WebSocket stream
    // - Prepare the SSL context (if using SSL)
    // - Initialize any other member variables
}

void WebSocketClient::run()
{
    resolver_.async_resolve(
        host_,
        port_,
        beast::bind_front_handler(
            &WebSocketClient::on_resolve,
            shared_from_this()));
}

void WebSocketClient::on_resolve(beast::error_code ec, tcp::resolver::results_type results)
{
    if(ec)
        return fail(ec, "resolve");
    if(!SSL_set_tlsext_host_name(ws_.next_layer().native_handle(), host_.c_str()))
        return fail(beast::error_code(static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()), "set SNI Hostname");
    beast::get_lowest_layer(ws_).async_connect(
        results,
        beast::bind_front_handler(
            &WebSocketClient::on_connect,
            shared_from_this()));
}

void WebSocketClient::on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep)
{
    if(ec)
        return fail(ec, "connect");
    ws_.next_layer().async_handshake(
        ssl::stream_base::client,
        beast::bind_front_handler(
            &WebSocketClient::on_ssl_handshake,
            shared_from_this()));
}

void WebSocketClient::on_ssl_handshake(beast::error_code ec)
{
    if(ec)
        return fail(ec, "ssl_handshake");
    //std::cout << "SSL Handshake successful" << std::endl;
    beast::get_lowest_layer(ws_).expires_never();
    ws_.set_option(websocket::stream_base::timeout::suggested(beast::role_type::client));
    ws_.set_option(websocket::stream_base::decorator(
        [](websocket::request_type& req)
        {
            req.set(http::field::user_agent,
                std::string(BOOST_BEAST_VERSION_STRING) +
                    " websocket-client-async");
            req.set(http::field::connection, "Upgrade");
            req.set(http::field::upgrade, "websocket");
            //req.set(http::field::origin, "ec2-44-203-201-70.compute-1.amazonaws.com");
            req.set(http::field::origin, "localhost");
            req.set(http::field::sec_websocket_version, "13");



        }));
    ws_.async_handshake(host_, target_,
        beast::bind_front_handler(
            &WebSocketClient::on_handshake,
            shared_from_this()));
}

void WebSocketClient::on_handshake(beast::error_code ec)
{
    if(ec)
        return fail(ec, "handshake");
    std::cout << "WebSocket connection established" << std::endl;
    //send();
    //receive();
}

void WebSocketClient::send_next_chunk(std::vector<int16_t> audio_chunk)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    //std::vector<unsigned char> audio_chunk = read_audio_chunk(wav_file, chunk_size);

    //if (!audio_chunk.empty()) {
    std::vector<uint8_t> audio_event = create_audio_event(audio_chunk);

    ws_.binary(true);
    ws_.async_write(
        net::buffer(audio_event),
        beast::bind_front_handler(
            &WebSocketClient::on_write,
            shared_from_this()));
    //} else {
    //    std::cout << "Audio chunk is empty" << std::endl;
    //}
}

void WebSocketClient::on_write(beast::error_code ec, std::size_t bytes_transferred)
{
    if (ec) {
        return fail(ec, "write");
    }

    send_next_chunk();
}

void WebSocketClient::receive()
{
    ws_.async_read(
        buffer_,
        beast::bind_front_handler(
            &WebSocketClient::on_read,
            shared_from_this()));
}

void WebSocketClient::on_read(beast::error_code ec, std::size_t bytes_transferred)
{
    if(ec)
        return fail(ec, "read");

    std::vector<uint8_t> message_bytes(boost::asio::buffers_begin(buffer_.data()),
                                        boost::asio::buffers_end(buffer_.data()));
    // Decode the event
    auto [header, payload] = decode_event(message_bytes);
    if (header[":message-type"] == "event") {
        //std::cout << "Results: " << payload["Transcript"] << std::endl;
        if (!payload["Transcript"]["Results"].empty()) {
            std::cout << "Transcript: " << payload["Transcript"]["Results"][0]["Alternatives"][0]["Transcript"] << std::endl;
        }
    } else if (header[":message-type"] == "exception") {
        std::cerr << "Exception: " << payload["Message"] << std::endl;
    }
    buffer_.consume(buffer_.size());
    receive();
}

void WebSocketClient::on_close(beast::error_code ec)
{
    if(ec)
        return fail(ec, "close");
    std::cout << "WebSocket connection closed" << std::endl;
}

void WebSocketClient::fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}
