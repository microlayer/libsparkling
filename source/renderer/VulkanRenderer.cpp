#include "VulkanRenderer.hpp"
#if SPARK_COMPILE_VULKAN == 0x1

namespace spark::renderer {
    /**
    *
    */
    VulkanRenderer::VulkanRenderer(spark::device::ISparkDevice* device,
        spark::renderer::shader::ISparkShader* shader,
        spark::renderer::ISparkTextureFactory* textureFactory) :
        AbstractSparkRenderer(device, shader, textureFactory, NULL)
    {

    }

    /**
    *
    */
    VulkanRenderer::~VulkanRenderer()
    {

    }

    /**
    *
    */
    void VulkanRenderer::onBeginScene()
    {

    }

    /**
    *
    */
    void VulkanRenderer::onEndScene()
    {

    }

    /**
    *
    */
    void VulkanRenderer::setOrthographicProjectionMatrix(spark::perspective::OrthographicProjection& orthographicProjection)
    {

    }

    /**
    *
    */
    void VulkanRenderer::setPerspectiveProjectionMatrix(spark::perspective::PerspectiveProjection& perspectiveProjection)
    {
    }

    /**
    *
    */
    void VulkanRenderer::setModelTransformation(math::Matrix4f& modelTransformation)
    {
    }

    /**
    *
    */
    void VulkanRenderer::drawBackground(const spark::drawing::Color& color)
    {

    }

    /**
    *
    */
    void VulkanRenderer::draw2DPoint(int16_t x, int16_t y, spark::drawing::Color color)
    {

    }

    /**
    *
    */
    void VulkanRenderer::draw2DLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, spark::drawing::Color color)
    {
        //// Begin recording the command buffer
        //VkCommandBufferBeginInfo beginInfo = {};
        //beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        //beginInfo.flags = 0; // Optional
        //beginInfo.pInheritanceInfo = nullptr; // Optional

        //vkBeginCommandBuffer(commandBuffer, &beginInfo);


        //vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);


        //VkDeviceSize offset = 0;
        //vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vertexBuffer, &offset);

        //// Draw the vertices
        //vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
        //

        //// End recording the command buffer
        //vkEndCommandBuffer(commandBuffer);
    }

    /**
    *
    */
    void VulkanRenderer::draw2DCircle(int16_t centerX, int16_t centerY, int16_t radius)
    {

    }

    /**
    *
    */
    void VulkanRenderer::draw2DRectangle(int16_t x1, int16_t y1, int16_t width, int16_t height)
    {

    }

    /**
    *
    */
    void VulkanRenderer::draw2DBitmap(spark::drawing::ISparkImage* image, int16_t x, int16_t y)
    {
        spark::drawing::ClippingRectangle clipRect = { 0,0, (uint16_t)image->getWidth(), (uint16_t)image->getHeight() };
        draw2DBitmap(image, x, y, clipRect);
    }

    /**
    *
    */
    void VulkanRenderer::draw2DBitmap(spark::drawing::ISparkImage* image, int16_t x, int16_t y, const spark::drawing::ClippingRectangle clipRect)
    {
        //vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSet, 0, nullptr);
        //vkCmdDraw(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
    }

    /**
    *
    */
    void VulkanRenderer::drawTiledLayer(const spark::game::TiledLayer* tiledLayer, int16_t x, int16_t y)
    {

    }

    /**
    *
    */
    void VulkanRenderer::drawString(const spark::font::E_SYSTEM_FONT_TYPE fontType, const std::string text, spark::drawing::Color color, int16_t x, int16_t y)
    {

    }

    /**
    *
    */
    void VulkanRenderer::drawString(const std::string fontFamily, uint32_t size, const std::string text, spark::drawing::Color color, int16_t x, int16_t y)
    {

    }

    /**
    *
    */
    void VulkanRenderer::renderMesh(spark::geometry::mesh::ISparkMesh* mesh, spark::material::ISparkMaterial* material)
    {

    }

    /**
    *
    */
    void VulkanRenderer::applyMaterial(spark::material::ISparkMaterial* material)
    {

    }

    /**
    *
    */
    void VulkanRenderer::activateDepthTest(bool flag)
    {

    }
}
#endif
