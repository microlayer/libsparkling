#include "AbstractSparkRenderer.hpp"

namespace spark {
    namespace renderer {
        /**
        *
        */
        AbstractSparkRenderer::AbstractSparkRenderer(spark::device::ISparkDevice* device,
            spark::renderer::shader::ISparkShader* shader,
            spark::renderer::ISparkTextureFactory* textureFactory,
            spark::renderer::ISparkVertexBufferFactory* vertexBufferFactory) :
            m_device(device),
            m_shader(shader),
            m_textureFactory(textureFactory),
            m_vertexBufferFactory(vertexBufferFactory),
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
        void AbstractSparkRenderer::setLightDirection(real32 x, real32 y, real32 z)
        {
            m_shader->setLightDirection(x, y, z);
        }

        /**
        *
        */
        spark::material::ISparkMaterial* AbstractSparkRenderer::createMaterial(spark::material::RenderMode renderMode)
        {
            return new spark::material::Material(renderMode);
        }
    } // end namespace renderer
} // end namespace spark