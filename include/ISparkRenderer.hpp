#ifndef __SPARK_RENDERER_ISPARKRENDERER_HPP_INCLUDED__
#define __SPARK_RENDERER_ISPARKRENDERER_HPP_INCLUDED__

#include <fstream>
#include <iostream>
#include "perspective/OrthographicProjection.hpp"
#include "perspective/PerspectiveProjection.hpp"
#include "drawing/Color.hpp"
#include "mesh/Mesh.hpp"
#include "renderer/common/ERenderEngine.hpp"
#include "SparkRefCount.hpp"
#include "ISparkImage.hpp"
#include "math/Matrix4.hpp"

namespace spark {
    namespace game {
        class TiledLayer;
    }
}

namespace spark {
    namespace renderer {

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
            virtual void draw2DBitmap(const spark::drawing::ISparkImage* image, int16_t x, int16_t y) = 0;
            //virtual void draw2DBitmap(const spark::drawing::ISparkImage* image, int16_t x, int16_t y, const spark::drawing::ClippingRectangle clipRect) = 0;
            //virtual void draw2DBitmap(/*const*/ spark::renderer::ISparkTexture* texture, int16_t x, int16_t y) = 0;
            //virtual void draw2DBitmap(/*const*/ spark::renderer::ISparkTexture* texture, int16_t x, int16_t y, const spark::drawing::ClippingRectangle clipRect) = 0;
            //virtual void draw2DCircle() = 0;
            virtual void drawTiledLayer(const spark::game::TiledLayer* tiledLayer, int16_t x, int16_t y) = 0;
            //virtual void drawString(const spark::font::E_SYSTEM_FONT_TYPE fontType, const std::string text, spark::drawing::Color color, int16_t x, int16_t y) = 0;
            //virtual void drawString(const std::string fontFamily, uint32_t size, const std::string text, spark::drawing::Color color, int16_t x, int16_t y) = 0;

            // 3D support
            virtual void renderMesh(spark::mesh::ISparkMesh* mesh) = 0;
        };
    } // end namespace renderer
} // end namespace spark
#endif
