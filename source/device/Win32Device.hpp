#ifndef __SPARK_DEVICE_WIN32DEVICE_HPP_INCLUDED__
#define __SPARK_DEVICE_WIN32DEVICE_HPP_INCLUDED__

#include "spark/SparkSetup.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS
#include <Windows.h>
#include <GL/glew.h>
#include "AbstractSparkDevice.hpp"
#include "renderer/OpenGLFLES2Renderer.hpp"
#include "renderer/Vulkan13Renderer.hpp"
#include "renderer/shader/OpenGLShaderProgram.hpp"

namespace spark {
    namespace device {
        /**
        *
        */
        class Win32Device : public AbstractSparkDevice
        {
        public:
            Win32Device(spark::renderer::E_RENDER_ENGINE rendererType);
            virtual ~Win32Device(void);

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

