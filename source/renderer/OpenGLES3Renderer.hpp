#ifndef __SPARK_RENDERER_OPENGLES2RENDERER_HPP_INCLUDED__
#define __SPARK_RENDERER_OPENGLES2RENDERER_HPP_INCLUDED__
#include "spark/SparkSetup.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_ANDROID || \
    SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
#include "OpenGLRenderer.hpp"
#include "ISparkTextureFactory.hpp"
#include "ISparkLightBuffer.hpp"

namespace spark::renderer {
    /**
    *
    */
    class OpenGLES3Renderer : public spark::renderer::OpenGLRenderer
    {
    public:
        OpenGLES3Renderer(spark::device::ISparkDevice* device,
            spark::renderer::shader::ISparkShader* shader,
            spark::renderer::ISparkTextureFactory* textureFactory,
            spark::renderer::ISparkVertexBufferFactory* vertexBufferFactory,
            spark::renderer::lightbuffer::ISparkLightBuffer* lightBuffer);
        virtual ~OpenGLES3Renderer(void);

    public: // ISparkRenderer
        // Lifecycle
        void onInit();
    };
}
#endif
#endif