#ifndef __SPARK_DEVICE_ANDROIDDEVICE_HPP_INCLUDED__
#define __SPARK_DEVICE_ANDROIDDEVICE_HPP_INCLUDED__

#include "spark/SparkSetup.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_ANDROID
#include "Sparkling.hpp"
#include "AbstractSparkDevice.hpp"
#include "renderer/OpenGLES2Renderer.hpp"
#include "renderer/shader/OpenGLShaderProgram.hpp"

namespace spark {
    namespace device {
        /**
        *
        */
        class AndroidDevice : public AbstractSparkDevice
        {
        public:
            AndroidDevice(spark::renderer::E_RENDER_ENGINE rendererType, android_app* pApplication);
            virtual ~AndroidDevice();

        public: // AbstractSparkDevice
            void createLogger();
            void createFileSystem();
            void createSparkWindow();
            void createShader();
            void createRenderer();

        public: // ISparkDevice
            std::string getRootPath();
        };
    } // end namespace device
} // end namespace spark
#endif
#endif