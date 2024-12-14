#include "Vulkan13Renderer.hpp"
#if SPARK_COMPILE_VULKAN == 0x1

namespace spark {
    namespace renderer {
        /**
        *
        */
        Vulkan13Renderer::Vulkan13Renderer(spark::device::ISparkDevice* device,
            spark::renderer::shader::ISparkShader* shader,
            spark::renderer::ISparkTextureFactory* textureFactory) :
            VulkanRenderer(device, shader)
        {
            m_logger = device->getLogger();
        }

        /**
        *
        */
        Vulkan13Renderer::~Vulkan13Renderer()
        {

        }

        /**
        *
        */
        void Vulkan13Renderer::onInit()
        {

        }
    } // end namespace renderer
} // end namespace spark
#endif