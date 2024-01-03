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
        void VulkanRenderer::setOrthographicProjection(spark::perspective::OrthographicProjection& orthographicProjection)
        {

        }

        /**
        *
        */
        void VulkanRenderer::setPerspectiveProjection(spark::perspective::PerspectiveProjection& perspectiveProjection)
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
