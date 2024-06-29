#include "VulkanRenderer.hpp"
#if SPARK_COMPILE_VULKAN == 0x1
namespace spark {
    namespace renderer {
        /**
        *
        */
        VulkanRenderer::VulkanRenderer(spark::device::ISparkDevice* device, spark::renderer::shader::ISparkShader* shader) :
            AbstractSparkRenderer(device, shader)
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
        void VulkanRenderer::draw2DBitmap(const spark::drawing::ISparkImage* image, int16_t x, int16_t y)
        {

        }

        /**
        *
        */
        void VulkanRenderer::renderMesh(spark::mesh::ISparkMesh* mesh)
        {

        }
    }
}
#endif
