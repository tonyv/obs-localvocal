#pragma once
#include <string>
#include <vector>
class AWSTranscribePresignedURL {
public:
    AWSTranscribePresignedURL(const std::string& access_key, const std::string& secret_key,
                              const std::string& session_token, const std::string& region = "us-west-2");
    std::string get_request_url(int sample_rate,
                                const std::string& language_code,
                                const std::string& media_encoding,
                                int number_of_channels = 1,
                                bool enable_channel_identification = false);

private:
    std::string access_key_;
    std::string secret_key_;
    std::string session_token_;
    std::string method_;
    std::string service_;
    std::string region_;
    std::string endpoint_;
    std::string host_;
    std::string amz_date_;
    std::string datestamp_;
    std::string canonical_uri_;
    std::string canonical_headers_;
    std::string signed_headers_;
    std::string algorithm_;
    std::string credential_scope_;
    std::string canonical_querystring_;
    std::string payload_hash_;
    std::string canonical_request_;
    std::string string_to_sign_;
    std::string signature_;
    std::string request_url_;
    void create_canonical_querystring(int sample_rate,
                                      const std::string& language_code,
                                      const std::string& media_encoding,
                                      int number_of_channels,
                                      bool enable_channel_identification);
    void create_canonical_request();
    void create_string_to_sign();
    void create_signature();
    void create_url();
    //void debug_print(const std::string& stage, const std::string& value);

    //static std::string hmac_sha256(const std::string& data, const std::string& key, bool raw = false);
    static std::string hmacSha256(const std::string &key, const std::string &data, bool isHexKey);
    static std::string sha256(const std::string &data);
    static std::string CreateCanonicalQueryString(
        const std::string& dateTimeString,
        const std::string& credentialScope,
        const std::string& languageCode,
        const std::string& mediaEncoding,
        const std::string& sampleRate,
        const std::string& accessKey
    );
    static std::string UrlEncode(const std::string& value);
    static std::string getCurrentTimestamp();
    static std::string getCurrentDate();
    static std::string to_hex(const std::vector<unsigned char>& data);
};