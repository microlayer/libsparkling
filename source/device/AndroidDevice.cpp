#include "AndroidDevice.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_ANDROID
namespace spark {
    namespace device {
        /**
        *
        */
        AndroidDevice::AndroidDevice(spark::renderer::E_RENDER_ENGINE rendererType, android_app* pApplication) :
            AbstractSparkDevice(rendererType),
            m_androidApplication(pApplication)
        {

        }

        /**
        *
        */
        AndroidDevice::~AndroidDevice()
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
        void AndroidDevice::createLogger()
        {

        }

        /**
        *
        */
        void AndroidDevice::createFileSystem()
        {
            m_fileSystem = new spark::file::FileSystem(m_logger, getRootPath());
        }

        /**
        *
        */
        void AndroidDevice::createSparkWindow()
        {
            if (m_rendererEngineType == spark::renderer::ERE_OGLFLES2 ||
                m_rendererEngineType == spark::renderer::ERE_VULKAN13)
            {
                m_window = new spark::device::window::AndroidEGLWindow(m_logger, m_rendererEngineType, m_androidApplication);
            }
            
            // Initialize
            if (!m_window->init())
            {
                exit(EXIT_FAILURE);
            }

            if (!m_window->createWindow(this->getScreenResolution().m_width, this->getScreenResolution().m_height))
            {
                m_window->terminate();
                exit(EXIT_FAILURE);
            }
            m_window->setWindowTitle("Microlayer - Sparkling");
        }

        /**
        *
        */
        void AndroidDevice::createShader()
        {
            m_shader = new spark::renderer::shader::OpenGLShaderProgram();
        }

        /**
        *
        */
        void AndroidDevice::createRenderer()
        {
            m_renderer = new spark::renderer::OpenGLES2Renderer(this, m_shader);
            m_renderer->onInit();
        }

        /**
        *
        */
        std::string AndroidDevice::getRootPath()
        {
            return "/";
        }
    } // end namespace device
} // end namespace spark
#endif
