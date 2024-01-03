#include "AndroidDevice.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_ANDROID
namespace spark {
    namespace device {
        /**
        *
        */
        AndroidDevice::AndroidDevice(spark::renderer::E_RENDER_ENGINE rendererType, android_app* pApplication) :
            AbstractSparkDevice(rendererType)
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
