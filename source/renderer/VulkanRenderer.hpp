#ifndef __SPARK_RENDERER_VULKANRENDERER_HPP_INCLUDED__
#define __SPARK_RENDERER_VULKANRENDERER_HPP_INCLUDED__
#include "spark/SparkSetup.hpp"
#if SPARK_COMPILE_VULKAN == 0x1
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS  || \
    SPARK_PLATFORM == SPARK_PLATFORM_LINUX
#include "AbstractSparkRenderer.hpp"

namespace spark {
    namespace renderer {
        /**
        *
        */
        class VulkanRenderer : public spark::renderer::AbstractSparkRenderer
        {
        public:
            VulkanRenderer(spark::device::ISparkDevice* device, spark::renderer::shader::ISparkShader* shader);
            virtual ~VulkanRenderer(void);

        public: // AbstractSparkRenderer
            void onBeginScene();
            void onEndScene();

        public: // ISparkRenderer
            // Perspective
            void setOrthographicProjection(spark::perspective::OrthographicProjection& orthographicProjection);
            void setPerspectiveProjection(spark::perspective::PerspectiveProjection& perspectiveProjection);

            // Common
            void drawBackground(const spark::drawing::Color& color);

            // 2D 
            void draw2DPoint(int16_t x, int16_t y, spark::drawing::Color color);
            void draw2DLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, spark::drawing::Color color);
            void draw2DBitmap(const spark::drawing::ISparkImage* image, int16_t x, int16_t y);

            // 3D
            void renderMesh(spark::mesh::ISparkMesh* mesh);
        };
    } // end namespace renderer
} // end namespace spark
#endif
#endif
#endif
