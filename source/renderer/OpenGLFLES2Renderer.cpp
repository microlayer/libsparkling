#include "OpenGLFLES2Renderer.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS  || \
    SPARK_PLATFORM == SPARK_PLATFORM_LINUX

namespace spark {
    namespace renderer {
        /**
        *
        */
        OpenGLFLES2Renderer::OpenGLFLES2Renderer(spark::device::ISparkDevice* device, spark::renderer::shader::ISparkShader* shader) :
            OpenGLRenderer(device, shader)
        {
            uint32_t ret = glewInit();
        }

        /**
        *
        */
        OpenGLFLES2Renderer::~OpenGLFLES2Renderer(void)
        {

        }

        /**
        *
        */
        void OpenGLFLES2Renderer::onInit()
        {
            m_device->getLogger()->info("Initializing render pipeline");
            m_shader->applyShader("Default");
            spark::perspective::OrthographicProjection orthographicProjection(m_device->getScreenResolution().m_width, m_device->getScreenResolution().m_height);
            setOrthographicProjectionMatrix(orthographicProjection);
        }
    } // end namespace renderer
} // end namespace spark
#endif