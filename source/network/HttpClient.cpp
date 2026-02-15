#include "HttpClient.hpp"
#include <winsock2.h>
#include <ws2tcpip.h>

namespace spark::network {
    /**
    *
    */
    HttpClient::HttpClient()
    {
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS       
#endif
    }

    /**
    *
    */
    HttpClient::~HttpClient()
    {
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS       
#endif
    }

    /**
    *
    */
    void HttpClient::get(const std::string& url, std::function<void(std::vector<uc8_t>)> callback)
    {
#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
        emscripten_fetch_attr_t attr;
        emscripten_fetch_attr_init(&attr);

        strcpy(attr.requestMethod, "GET");

        auto* ctx = new RequestContext{ onSuccess, onError };
        attr.userData = ctx;

        attr.onsuccess = [](emscripten_fetch_t* fetch) {
            auto* ctx = static_cast<RequestContext*>(fetch->userData);

            std::string body(fetch->data, fetch->numBytes);
            ctx->onSuccess(body);

            emscripten_fetch_close(fetch);
            delete ctx;
            };

        attr.onerror = [](emscripten_fetch_t* fetch) {
            auto* ctx = static_cast<RequestContext*>(fetch->userData);

            ctx->onError("HTTP error: " + std::to_string(fetch->status));

            emscripten_fetch_close(fetch);
            delete ctx;
            };

        emscripten_fetch(&attr, url.c_str());
#endif

#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS
        std::thread([url, callback]() mutable {

            std::vector<uc8_t> result = {};

            WSADATA wsaData;
            int wsaStatus = WSAStartup(MAKEWORD(2, 2), &wsaData);

            const char* hostname = "hellosalut.stefanbohacek.com";
            const char* port = "80";
            struct addrinfo hints, * res;

            memset(&hints, 0, sizeof(hints));
            hints.ai_family = AF_UNSPEC;        // IPv4 oder IPv6
            hints.ai_socktype = SOCK_STREAM;    // TCP

            int status = getaddrinfo(hostname, port, &hints, &res);

            int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
            connect(sock, res->ai_addr, res->ai_addrlen);

            const char* request =
                "GET /?lang=de HTTP/1.1\r\n"
                "Host: hellosalut.stefanbohacek.com\r\n"
                "Connection: close\r\n\r\n";

            send(sock, request, strlen(request), 0);

            char buffer[1024];
            int bytes;
            while ((bytes = recv(sock, buffer, sizeof(buffer), 0)) > 0)
            {
                result.insert(result.end(), buffer, buffer + bytes);
            }

            callback(std::move(result));

            }).detach();

        WSACleanup();
#endif
    }

    /**
    *
    */
    void HttpClient::post(const std::string& url, const std::string& jsonBody, std::function<void(std::vector<uc8_t>)> callback)
    {
#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
        emscripten_fetch_attr_t attr;
        emscripten_fetch_attr_init(&attr);

        strcpy(attr.requestMethod, "POST");

        attr.requestHeaders = new const char* [3];
        attr.requestHeaders[0] = "Content-Type";
        attr.requestHeaders[1] = "application/json"
#endif
    }

    /**
    *
    */
    void HttpClient::put(const std::string& url, const std::string& jsonBody, std::function<void(std::vector<uc8_t>)> callback)
    {

    }

    /**
    *
    */
    void HttpClient::del(const std::string& url, std::function<void(std::vector<uc8_t>)> callback)
    {

    }
}
