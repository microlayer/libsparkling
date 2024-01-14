#include "spark/SparkSetup.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS
#include "device/Win32Device.hpp"

namespace spark {
    namespace device {
        /**
        *
        */
        Win32Device::Win32Device(spark::renderer::E_RENDER_ENGINE rendererType) :
            AbstractSparkDevice(rendererType)
        {
            AbstractSparkDevice::construct();
        }

        /**
        *
        */
        Win32Device::~Win32Device(void)
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
        void Win32Device::createLogger()
        {
            m_logger = new spark::log::DefaultLogger();
            if (m_logger != NULL)
            {
                spark::log::LogManager::setLogger(m_logger);
            }
            m_logger->info("Logger successful created for Win32 device");
        }

        /**
        *
        */
        void Win32Device::createFileSystem()
        {
            m_fileSystem = new spark::file::FileSystem(m_logger, getRootPath());
        }

        /**
        *
        */
        void Win32Device::createSparkWindow()
        {
            if (m_rendererEngineType == spark::renderer::ERE_OGLFLES2 ||
                m_rendererEngineType == spark::renderer::ERE_VULKAN13)
            {
                m_window = new spark::device::window::GlfwWindow(m_logger, m_rendererEngineType);
            }
            else if (m_rendererEngineType == spark::renderer::ERE_D3D11FL93)
            {
                //m_window = new spark::device::window::WCWin32D3D11(this);
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
        void Win32Device::createShader()
        {
            m_shader = new spark::renderer::shader::OpenGLShaderProgram();
        }

        /**
        * @Brief The last instance which is created by the bootstrap phase.
        */
        void Win32Device::createRenderer()
        {
            if (m_rendererEngineType == spark::renderer::E_RENDER_ENGINE::ERE_OGLFLES2)
            {
                m_renderer = new spark::renderer::OpenGLFLES2Renderer(this, m_shader);
            }
#if SPARK_COMPILE_VULKAN == 0x1
            else
            {
                m_renderer = new spark::renderer::Vulkan13Renderer(this, m_shader, m_window);
            }
#endif
            m_renderer->onInit();
        }

        /**
        *
        */
        std::string Win32Device::getRootPath()
        {

            std::string rootPath = "c:\\home\\microlayer\\";
            m_logger->info("Root Path:  %s", rootPath.c_str());
            return rootPath;
            //char buffer[512];
            //GetModuleFileName(NULL, buffer, 512);
            //std::string::size_type pos = std::string(buffer).find_last_of("\\/");
            //return std::string(buffer).substr(0, pos);
        }

    } // end namespace device
} // end namespace spark
#endif