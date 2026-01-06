#ifndef __SPARK_DEVICE_ANDROIDDEVICE_HPP_INCLUDED__
#define __SPARK_DEVICE_ANDROIDDEVICE_HPP_INCLUDED__

#include "spark/SparkSetup.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_ANDROID
#include "Sparkling.hpp"
#include "AbstractSparkDevice.hpp"
#include "renderer/OpenGLES2Renderer.hpp"
#include "window/AndroidEGLWindow.hpp"
#include "renderer/shader/OpenGLShaderProgram.hpp"

namespace spark {
    namespace device {
        /**
        *
        */
        class AndroidDevice : public AbstractSparkDevice
        {
        public:
            AndroidDevice(spark::renderer::E_RENDER_ENGINE rendererType, uint32_t screenWidth, uint32_t screenHeight, android_app* pApplication);
            virtual ~AndroidDevice();

        public: // AbstractSparkDevice
            void createLogger();
            void createFileSystem();
            void createSparkWindow();
            void createShader();
            void createRenderer();

        public: // ISparkDevice
            std::string getRootPath();

        private:
            void copyAssetToExternalStorage();

        private:
            android_app* m_androidApplication;
            std::string m_rootPath;
        };
    } // end namespace device
} // end namespace spark
#endif
#endif