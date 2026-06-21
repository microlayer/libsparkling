#include "AbstractSparkRenderer.hpp"

namespace spark {
    namespace renderer {
        /**
        *
        */
        AbstractSparkRenderer::AbstractSparkRenderer(spark::device::ISparkDevice* device,
            spark::renderer::shader::ISparkShader* shader,
            spark::renderer::ISparkTextureFactory* textureFactory,
            spark::renderer::ISparkVertexBufferFactory* vertexBufferFactory,
            spark::renderer::lightbuffer::ISparkLightBuffer* lightBuffer) :
            m_device(device),
            m_shader(shader),
            m_textureFactory(textureFactory),
            m_vertexBufferFactory(vertexBufferFactory),
            m_lightBuffer(lightBuffer),
            m_logger(device->getLogger())
        {

        }

        /**
        *
        */
        AbstractSparkRenderer::~AbstractSparkRenderer()
        {

        }

        /**
        *
        */
        void AbstractSparkRenderer::beginScene()
        {
            onBeginScene();
        }

        /**
        *
        */
        void AbstractSparkRenderer::endScene()
        {
            onEndScene();
            m_device->flush();
        }

        /**
        *
        */
        void AbstractSparkRenderer::setDrawMode(uint32_t drawMode)
        {
            m_shader->setDrawMode(drawMode);
        }

        /**
        *
        */
        void AbstractSparkRenderer::uploadLights(
            std::vector<renderer::lightbuffer::GPUDirectionalLight> gpuDirectionalLights,
            std::vector<renderer::lightbuffer::GPUPointLight> gpuPointLights)
        {
            m_lightBuffer->uploadLights(m_shader, gpuDirectionalLights, gpuPointLights);
        }

        /**
        *
        */
        spark::material::ISparkMaterial* AbstractSparkRenderer::createMaterial(spark::material::RenderMode renderMode)
        {
            return new spark::material::Material(renderMode);
        }

        /**
        *
        */
        spark::scene::camera::ISparkPerspectiveCamera* AbstractSparkRenderer::createPerspectiveCamera()
        {
            return new spark::scene::camera::PerspectiveCamera(m_device->getScreenResolution().m_ratio);
        }
    } // end namespace renderer
} // end namespace spark