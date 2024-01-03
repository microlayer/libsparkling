#ifndef __SPARK_RENDERER_OPENGLFLES2RENDERER_HPP_INCLUDED__
#define __SPARK_RENDERER_OPENGLFLES2RENDERER_HPP_INCLUDED__
#include "spark/SparkSetup.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS  || \
    SPARK_PLATFORM == SPARK_PLATFORM_LINUX    || \
    SPARK_PLATFORM == SPARK_PLATFORM_APPLE
#include "OpenGLRenderer.hpp"

namespace spark {
    namespace renderer {
        /**
        *
        */
        class OpenGLFLES2Renderer : public spark::renderer::OpenGLRenderer
        {
        public:
            OpenGLFLES2Renderer(spark::device::ISparkDevice* device, spark::renderer::shader::ISparkShader* shader);
            virtual ~OpenGLFLES2Renderer(void);

        public: // ISparkRenderer
            // Lifecycle
            void onInit();
        };
    } // end namespace renderer
} // end namespace spark
#endif
#endif