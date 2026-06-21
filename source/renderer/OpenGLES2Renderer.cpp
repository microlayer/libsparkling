#include "OpenGLES2Renderer.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_ANDROID || \
    SPARK_PLATFORM == SPARK_PLATFORM_WEBGL

namespace spark::renderer {
    /**
    *
    */
    OpenGLES2Renderer::OpenGLES2Renderer(spark::device::ISparkDevice* device,
        spark::renderer::shader::ISparkShader* shader,
        spark::renderer::ISparkTextureFactory* textureFactory,
        spark::renderer::ISparkVertexBufferFactory* vertexBufferFactory,
        spark::renderer::lightbuffer::ISparkLightBuffer* lightBuffer) :
        OpenGLRenderer(device, shader, textureFactory, vertexBufferFactory, lightBuffer)
    {

    }

    /**
    *
    */
    OpenGLES2Renderer::~OpenGLES2Renderer(void)
    {

    }

    /**
    *
    */
    void OpenGLES2Renderer::onInit()
    {
        m_device->getLogger()->info("Initializing render pipeline");
        m_shader->applyShader("Default");
        spark::perspective::OrthographicProjection orthographicProjection(m_device->getScreenResolution().m_width, m_device->getScreenResolution().m_height);
        setOrthographicProjectionMatrix(orthographicProjection);
    }
}
#endif