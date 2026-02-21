#ifndef __SPARK_RENDERER_OPENGLFLES2RENDERER_HPP_INCLUDED__
#define __SPARK_RENDERER_OPENGLFLES2RENDERER_HPP_INCLUDED__
#include "spark/SparkSetup.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS  || \
    SPARK_PLATFORM == SPARK_PLATFORM_LINUX    || \
    SPARK_PLATFORM == SPARK_PLATFORM_APPLE
#include "OpenGLRenderer.hpp"
#include "ISparkTextureFactory.hpp"
#include "ISparkVertexBufferFactory.hpp"

namespace spark::renderer {
    /**
    *
    */
    class OpenGLFLES2Renderer : public spark::renderer::OpenGLRenderer
    {
    public:
        OpenGLFLES2Renderer(spark::device::ISparkDevice* device,
            spark::renderer::shader::ISparkShader* shader,
            spark::renderer::ISparkTextureFactory* textureFactory,
            spark::renderer::ISparkVertexBufferFactory* vertexBufferFactory);
        virtual ~OpenGLFLES2Renderer(void);

    public: // ISparkRenderer
        // Lifecycle
        void onInit();
    };
}
#endif
#endif