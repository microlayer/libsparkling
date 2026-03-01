#ifndef __SPARK_NETWORK_HTTPCLIENT_HPP_INCLUDED__
#define __SPARK_NETWORK_HTTPCLIENT_HPP_INCLUDED__

#include <string>
#include <cstring>
#include <functional>
#include <regex>
#include "ISparkHttpClient.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
#include <emscripten/fetch.h>
#endif
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS
#include <thread>
#endif

namespace spark::network {
    /**
    *
    */
    struct RequestContext {
        std::function<void(std::string)> onSuccess;
        std::function<void(std::string)> onError;
    };

    /**
    *
    */
    class HttpClient : public ISparkHttpClient {
    public:
        HttpClient();
        ~HttpClient();

    public:
        void get(const std::string& url, std::function<void(std::vector<uc8_t>)> callback);
        void post(const std::string& url, const std::string& jsonBody, std::function<void(std::vector<uc8_t>)> callback);
        void put(const std::string& url, const std::string& jsonBody, std::function<void(std::vector<uc8_t>)> callback);
        void del(const std::string& url, std::function<void(std::vector<uc8_t>)> callback);

    private:
        static void onSuccess(std::string result);
        static void onError(std::string error);

    private:
        std::string extractHostname(const std::string& url);
        std::string extractPath(const std::string& url);
        std::string buildHttpGetRequest(const std::string& host, const std::string& path);
    };
}
#endif