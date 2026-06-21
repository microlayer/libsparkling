#include "Vulkan13Renderer.hpp"
#if SPARK_COMPILE_VULKAN == 0x1

namespace spark::renderer {
    /**
    *
    */
    Vulkan13Renderer::Vulkan13Renderer(spark::device::ISparkDevice* device,
        spark::renderer::shader::ISparkShader* shader,
        spark::renderer::ISparkTextureFactory* textureFactory,
        spark::renderer::ISparkVertexBufferFactory* vertexBufferFactory,
        spark::renderer::lightbuffer::ISparkLightBuffer* lightBuffer) :
        VulkanRenderer(device, shader, textureFactory, vertexBufferFactory, lightBuffer)
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
}
#endif