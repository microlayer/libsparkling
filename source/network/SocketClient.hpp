#ifndef __SPARK_NETWORK_SOCKETCLIENT_HPP_INCLUDED__
#define __SPARK_NETWORK_SOCKETCLIENT_HPP_INCLUDED__

#include "spark/SparkSetup.hpp"
#include <spark/SparkTypes.hpp>
#include <functional>
#include <string>
#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
#include <emscripten/fetch.h>
#endif
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS
#endif

namespace spark::network {
    /**
    *
    */
    class SocketClient {
    public:
        using MessageCallback = std::function<void(const std::string&)>;
        using EventCallback = std::function<void()>;

    public:
        SocketClient();
        ~SocketClient();

    public:
        bool connect(const std::string& url);
        void send(const std::string& message);
        void close();

    private:
        MessageCallback onMessage;
        EventCallback onOpen;
        EventCallback onClose;

#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
        EMSCRIPTEN_WEBSOCKET_T m_ws
#endif
    };
}
#endif