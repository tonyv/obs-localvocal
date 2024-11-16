#include <boost/asio/strand.hpp>
#include <boost/asio.hpp>
//#include <boost/asio/ssl.hpp>
#include <string>
#include <memory>

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;
using tcp = boost::asio::ip::tcp;


class WebSocketClient : public std::enable_shared_from_this<WebSocketClient>
{
public:
    explicit WebSocketClient(net::io_context& ioc, ssl::context& ctx,
                             const std::string& host, const std::string& port,
                             const std::string& target);

    void run();
    void send_next_chunk(std::vector<int16_t> audio_chunk);
    void receive();
    void on_read(beast::error_code ec, std::size_t bytes_transferred);
    bool is_connected();
    void verify_connection();

    websocket::stream<beast::ssl_stream<beast::tcp_stream>>& ws() { return ws_; }
    beast::flat_buffer& buffer() { return buffer_; }

private:
    tcp::resolver resolver_;
    websocket::stream<beast::ssl_stream<beast::tcp_stream>> ws_;
    beast::flat_buffer buffer_;
    std::string host_;
    std::string port_;
    std::string target_;
    std::mutex write_mutex_;
    std::shared_ptr<std::vector<uint8_t>> current_write_buffer_;
    bool write_in_progress_{false};


    void on_resolve(beast::error_code ec, tcp::resolver::results_type results);
    void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep);
    void on_ssl_handshake(beast::error_code ec);
    void on_handshake(beast::error_code ec);
    std::vector<unsigned char> read_audio_chunk(std::ifstream& file, size_t chunk_size);
    //void send(const std::vector<unsigned char>& audioData);
    void on_write(beast::error_code ec, std::size_t bytes_transferred);
    
    void on_close(beast::error_code ec);
    void fail(beast::error_code ec, char const* what);

    bool connection_ready_ = false;
};