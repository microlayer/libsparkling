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
            if (m_rendererConfig != NULL) m_rendererConfig->release();
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
                m_window = new spark::device::window::GlfwWindow(m_logger, m_rendererEngineType, this);
            }

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
        void Win32Device::createShader()
        {
            m_shader = new spark::renderer::shader::OpenGLShaderProgram(m_logger, m_rendererEngineType);
        }

        /**
        * @Brief The last instance which is created by the bootstrap phase.
        */
        void Win32Device::createRenderer()
        {
            if (m_rendererEngineType == spark::renderer::E_RENDER_ENGINE::ERE_OGLFLES2)
            {
                m_rendererConfig = new spark::renderer::OGLConfig(m_window, m_logger);
                m_renderer = new spark::renderer::OpenGLFLES2Renderer(this, m_shader, m_texureFactory, m_vertexBufferFactory);
            }
#if SPARK_COMPILE_VULKAN == 0x1
            else
            {
                m_rendererConfig = new spark::renderer::VulkanConfig(m_window, m_logger);
                m_renderer = new spark::renderer::Vulkan13Renderer(this, m_shader, m_texureFactory);
            }
#endif
            m_renderer->onInit();
        }

        /**
        *
        */
        std::string Win32Device::getRootPath()
        {
            char path[MAX_PATH];
            GetModuleFileNameA(NULL, path, MAX_PATH);
            std::string fullPath(path);
            size_t pos = fullPath.find_last_of("\\/");
            std::string pathToExecutable = fullPath.substr(0, pos);
            std::filesystem::path resPath = std::filesystem::path(pathToExecutable + "..//..//..//..//res//");
            std::string relativeResPath = resPath.lexically_normal().string();
            m_logger->info("Root Path:  %s", relativeResPath.c_str());
            return relativeResPath;
        }

    } // end namespace device
} // end namespace spark
#endif