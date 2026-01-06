#ifndef __SPARK_DEVICE_WEBGLDEVICE_HPP_INCLUDED__
#define __SPARK_DEVICE_WEBGLDEVICE_HPP_INCLUDED__

#include "spark/SparkSetup.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
#include "AbstractSparkDevice.hpp"
#include "renderer/OpenGLES2Renderer.hpp"
#include "renderer/shader/OpenGLShaderProgram.hpp"

namespace spark {
    namespace device {
        /**
        *
        */
        class WebGLDevice : public AbstractSparkDevice
        {
        public:
            WebGLDevice(spark::renderer::E_RENDER_ENGINE rendererType, uint32_t screenWidth, uint32_t screenHeight);
            virtual ~WebGLDevice();

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