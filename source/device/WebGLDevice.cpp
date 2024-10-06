#include "WebGLDevice.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL

namespace spark {
    namespace device {
        /**
        *
        */
        WebGLDevice::WebGLDevice(spark::renderer::E_RENDER_ENGINE rendererType) :
            AbstractSparkDevice(rendererType)
        {
            AbstractSparkDevice::construct();
        }

        /**
        *
        */
        WebGLDevice::~WebGLDevice()
        {
            m_logger->release();
            m_fileSystem->release();
            m_window->release();
            m_shader->release();
            m_renderer->release();
        }

        /**
        *
        */
        void WebGLDevice::createLogger()
        {
            m_logger = new spark::log::DefaultLogger();
            if (m_logger != NULL)
            {
                spark::log::LogManager::setLogger(m_logger);
            }
            m_logger->info("Logger successful created for WebGL device");
        }

        /**
        *
        */
        void WebGLDevice::createFileSystem()
        {
            m_fileSystem = new spark::file::FileSystem(m_logger, getRootPath());
        }

        /**
        *
        */
        void WebGLDevice::createSparkWindow()
        {
            m_window = new spark::device::window::GlfwWindow(m_logger, m_rendererEngineType);
            // Initialize
            if (!m_window->init())
            {
                exit(EXIT_FAILURE);
            }

            if (!m_window->createWindow())
            {
                m_window->terminate();
                exit(EXIT_FAILURE);
            }
            m_window->setWindowTitle("Microlayer - Sparkling");
        }

        /**
        *
        */
        void WebGLDevice::createShader()
        {
            m_shader = new spark::renderer::shader::OpenGLShaderProgram(m_logger, m_rendererEngineType);
        }

        /**
        *
        */
        void WebGLDevice::createRenderer()
        {
            m_renderer = new spark::renderer::OpenGLES2Renderer(this, m_shader);
            m_renderer->onInit();
        }

        /**
        *
        */
        std::string WebGLDevice::getRootPath()
        {
            return "/";
        }
    } // end namespace device
} // end namespace spark
#endif
