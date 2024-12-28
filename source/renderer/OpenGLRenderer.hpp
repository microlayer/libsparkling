#ifndef __SPARK_RENDERER_OPENGLRENDERER_HPP_INCLUDED__
#define __SPARK_RENDERER_OPENGLRENDERER_HPP_INCLUDED__
#include "spark/SparkSetup.hpp"
#include "AbstractSparkRenderer.hpp"
#include "ISparkShader.hpp"
#include "drawing/ClippingRectangle.hpp"
#include "math/Matrix4.hpp"
#include "math/ProjectionMatrix.hpp"
#include "fonts/FontPool.hpp"
#include "ISparkTextureFactory.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS || \
    SPARK_PLATFORM == SPARK_PLATFORM_LINUX   || \
    SPARK_PLATFORM == SPARK_PLATFORM_APPLE
#include <GL/glew.h>
#endif
#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL || \
    SPARK_PLATFORM == SPARK_PLATFORM_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif
#include "stdlib.h"

namespace spark {
    namespace renderer {
        /**
        *
        */
        class OpenGLRenderer : public spark::renderer::AbstractSparkRenderer
        {
        public:
            OpenGLRenderer(spark::device::ISparkDevice* device,
                spark::renderer::shader::ISparkShader* shader,
                spark::renderer::ISparkTextureFactory* textureFactory);
            virtual ~OpenGLRenderer(void);

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
            void draw2DBitmap(const spark::drawing::ISparkImage* image, int16_t x, int16_t y);
            void draw2DBitmap(const spark::drawing::ISparkImage* image, int16_t x, int16_t y, const spark::drawing::ClippingRectangle clipRect);
            void drawTiledLayer(const spark::game::TiledLayer* tiledLayer, int16_t x, int16_t y);
            void drawString(const spark::font::E_SYSTEM_FONT_TYPE fontType, const std::string text, spark::drawing::Color color, int16_t x, int16_t y);
            void drawString(const std::string fontFamily, uint32_t size, const std::string text, spark::drawing::Color color, int16_t x, int16_t y);

            // 3D
            void renderMesh(spark::mesh::ISparkMesh* mesh);

        private:
            math::Matrix4f m_projectionViewMatrix;
            spark::drawing::Color m_backgroundColor;
        };
    } // end namespace renderer
} // end namespace spark
#endif
