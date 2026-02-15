#ifndef __SPARK_NETWORK_SOCKETCLIENT_HPP_INCLUDED__
#define __SPARK_NETWORK_SOCKETCLIENT_HPP_INCLUDED__

#include "spark/SparkSetup.hpp"
#include <spark/SparkTypes.hpp>
#include <functional>
#include <string>
#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
#include <emscripten/websocket.h>
#define EMSCRIPTEN_WEBSOCKET_T int
#endif
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS
#endif

namespace spark::network {
    /**
    *
    */
    class SocketClient {
    public:


    public:
        SocketClient();
        ~SocketClient();

    public:
        bool connect(const std::string& url);
        void send(const std::string& message);
        void close();

    private:


#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
        static EM_BOOL onOpen(int eventType, const EmscriptenWebSocketOpenEvent* websocketEvent, void* userData);
        static EM_BOOL onMessage(int eventType, const EmscriptenWebSocketMessageEvent* websocketEvent, void* userData);
        static EM_BOOL onClose(int eventType, const EmscriptenWebSocketCloseEvent* websocketEvent, void* userData);
        EMSCRIPTEN_WEBSOCKET_T m_ws;
#endif
    };
}
#endif