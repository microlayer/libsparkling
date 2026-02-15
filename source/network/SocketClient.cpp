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
        emscripten_websocket_set_onopen_callback(m_ws, this, staticOnOpen);
        emscripten_websocket_set_onmessage_callback(m_ws, this, staticOnMessage);
        emscripten_websocket_set_onclose_callback(m_ws, this, staticOnClose);
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
}