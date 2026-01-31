#ifndef __SPARK_RENDERER_ISPARKRENDERER_HPP_INCLUDED__
#define __SPARK_RENDERER_ISPARKRENDERER_HPP_INCLUDED__

#include <fstream>
#include <iostream>
#include "perspective/OrthographicProjection.hpp"
#include "perspective/PerspectiveProjection.hpp"
#include "drawing/Color.hpp"
#include "drawing/ClippingRectangle.hpp"
#include "geometry/mesh/Mesh.hpp"
#include "renderer/common/ERenderEngine.hpp"
#include "SparkRefCount.hpp"
#include "ISparkImage.hpp"
#include "ISparkFont.hpp"
#include "math/Matrix4.hpp"
#include <ISparkMaterial.hpp>

namespace spark {
    namespace game {
        class TiledLayer;
    }
}

namespace spark::renderer {
    /**
    *
    */
    class ISparkRenderer : public virtual spark::SparkRefCount
    {
    public:

        virtual void onInit() = 0;

        virtual void beginScene() = 0;
        virtual void endScene() = 0;

        virtual void setOrthographicProjectionMatrix(spark::perspective::OrthographicProjection& orthographicProjection) = 0;
        virtual void setPerspectiveProjectionMatrix(spark::perspective::PerspectiveProjection& perspectiveProjection) = 0;
        virtual void setModelTransformation(math::Matrix4f& modelTransformation) = 0;

        virtual void drawBackground(const spark::drawing::Color& color) = 0;

        // 2D support            
        virtual void draw2DPoint(int16_t x, int16_t y, spark::drawing::Color color) = 0;
        virtual void draw2DLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, spark::drawing::Color color) = 0;
        virtual void draw2DCircle(int16_t centerX, int16_t centerY, int16_t radius) = 0;
        virtual void draw2DRectangle(int16_t x1, int16_t y1, int16_t width, int16_t height) = 0;
        virtual void draw2DBitmap(spark::drawing::ISparkImage* image, int16_t x, int16_t y) = 0;
        virtual void draw2DBitmap(spark::drawing::ISparkImage* image, int16_t x, int16_t y, const spark::drawing::ClippingRectangle clipRect) = 0;
        virtual void drawTiledLayer(const spark::game::TiledLayer* tiledLayer, int16_t x, int16_t y) = 0;
        virtual void drawString(const spark::font::E_SYSTEM_FONT_TYPE fontType, const std::string text, spark::drawing::Color color, int16_t x, int16_t y) = 0;
        virtual void drawString(const std::string fontFamily, uint32_t size, const std::string text, spark::drawing::Color color, int16_t x, int16_t y) = 0;

        // 3D support
        virtual void renderMesh(spark::geometry::mesh::ISparkMesh* mesh, spark::material::ISparkMaterial* material) = 0;

        // Material
        virtual void applyMaterial(spark::material::ISparkMaterial* material) = 0;

        // Shader
        virtual void setDrawMode(uint32_t drawMode) = 0;
        virtual void setLightDirection(real32 x, real32 y, real32 z) = 0;

        // Depth-Test
        virtual void activateDepthTest(bool flag) = 0;

        // Factory
        virtual spark::material::ISparkMaterial* createMaterial(spark::material::RenderMode renderMode) = 0;
    };
}
#endif
