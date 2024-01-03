#include "AbstractSparkRenderer.hpp"

namespace spark {
    namespace renderer {
        /**
        *
        */
        AbstractSparkRenderer::AbstractSparkRenderer(spark::device::ISparkDevice* device, spark::renderer::shader::ISparkShader* shader) :
            m_device(device),
            m_shader(shader),
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
    } // end namespace renderer
} // end namespace spark