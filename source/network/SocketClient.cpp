#include "SocketClient.hpp"

namespace spark::network {
    /**
    *
    */
    SocketClient::SocketClient()
    {

    }

    /**
    *
    */
    SocketClient::~SocketClient()
    {
    }

    /**
    *
    */
    bool SocketClient::connect(const std::string& url)
    {
#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
        EmscriptenWebSocketCreateAttributes attr = { url.c_str(), NULL, EM_TRUE };
        m_ws = emscripten_websocket_new(&attr);
        emscripten_websocket_set_onopen_callback(m_ws, this, onOpen);
        emscripten_websocket_set_onmessage_callback(m_ws, this, onMessage);
        emscripten_websocket_set_onclose_callback(m_ws, this, onClose);
#endif
        return true;
    }

    /**
    *
    */
    void SocketClient::send(const std::string& message)
    {
#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
        if (m_ws > 0) emscripten_websocket_send_utf8_text(m_ws, message.c_str());
#endif
    }

    /**
    *
    */
    void SocketClient::close()
    {
#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
        if (m_ws > 0)
        {
            emscripten_websocket_close(m_ws, 1000, "Closed");
            emscripten_websocket_delete(m_ws);
            m_ws = 0;
        }
#endif
    }

#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
    /**
    *
    */
    EM_BOOL SocketClient::onOpen(int eventType, const EmscriptenWebSocketOpenEvent* websocketEvent, void* userData)
    {
        return true;
    }

    /**
    *
    */
    EM_BOOL SocketClient::onMessage(int eventType, const EmscriptenWebSocketMessageEvent* websocketEvent, void* userData)
    {
        return true;
    }

    /**
    *
    */
    EM_BOOL SocketClient::onClose(int eventType, const EmscriptenWebSocketCloseEvent* websocketEvent, void* userData)
    {
        return true;
    }
#endif
}