#ifndef __SPARK_RENDERER_VULKANRENDERER_HPP_INCLUDED__
#define __SPARK_RENDERER_VULKANRENDERER_HPP_INCLUDED__
#include "spark/SparkSetup.hpp"
#include "ISparkTextureFactory.hpp"
#if SPARK_COMPILE_VULKAN == 0x1
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS  || \
    SPARK_PLATFORM == SPARK_PLATFORM_LINUX
#include "AbstractSparkRenderer.hpp"

namespace spark::renderer {
    /**
    *
    */
    class VulkanRenderer : public spark::renderer::AbstractSparkRenderer
    {
    public:
        VulkanRenderer(spark::device::ISparkDevice* device,
            spark::renderer::shader::ISparkShader* shader,
            spark::renderer::ISparkTextureFactory* textureFactory);
        virtual ~VulkanRenderer(void);

    public: // AbstractSparkRenderer
        void onBeginScene();
        void onEndScene();

    public: // ISparkRenderer
        // Perspective
        void setOrthographicProjectionMatrix(spark::perspective::OrthographicProjection& orthographicProjection);
        void setPerspectiveProjectionMatrix(spark::perspective::PerspectiveProjection& perspectiveProjection);
        void setModelTransformation(math::Matrix4f& modelTransformation);

        // Common
        void drawBackground(const spark::drawing::Color& color);

        // 2D 
        void draw2DPoint(int16_t x, int16_t y, spark::drawing::Color color);
        void draw2DLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, spark::drawing::Color color);
        void draw2DCircle(int16_t centerX, int16_t centerY, int16_t radius);
        void draw2DRectangle(int16_t x1, int16_t y1, int16_t width, int16_t height);
        void draw2DBitmap(spark::drawing::ISparkImage* image, int16_t x, int16_t y);
        void draw2DBitmap(spark::drawing::ISparkImage* image, int16_t x, int16_t y, const spark::drawing::ClippingRectangle clipRect);
        void drawTiledLayer(const spark::game::TiledLayer* tiledLayer, int16_t x, int16_t y);
        void drawString(const spark::font::E_SYSTEM_FONT_TYPE fontType, const std::string text, spark::drawing::Color color, int16_t x, int16_t y);
        void drawString(const std::string fontFamily, uint32_t size, const std::string text, spark::drawing::Color color, int16_t x, int16_t y);

        // 3D
        void renderMesh(spark::geometry::mesh::ISparkMesh* mesh, spark::material::ISparkMaterial* material);
        void renderPointCloud(spark::geometry::pointcloud::ISparkPointCloud* pointCloud);

        // Material
        void applyMaterial(spark::material::ISparkMaterial* material);

        // Depth-Test
        void activateDepthTest(bool flag);
    };
}
#endif
#endif
#endif