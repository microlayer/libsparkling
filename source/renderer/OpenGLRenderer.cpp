#include "OpenGLRenderer.hpp"

namespace spark::renderer {
    /**
    *
    */
    OpenGLRenderer::OpenGLRenderer(spark::device::ISparkDevice* device,
        spark::renderer::shader::ISparkShader* shader,
        spark::renderer::ISparkTextureFactory* textureFactory,
        spark::renderer::ISparkVertexBufferFactory* vertexBufferFactory) :
        AbstractSparkRenderer(device, shader, textureFactory, vertexBufferFactory)
    {
        m_backgroundColor = spark::drawing::Color(48, 48, 48, 255);
    }

    /**
    *
    */
    OpenGLRenderer::~OpenGLRenderer()
    {

    }

    /**
    *
    */
    void OpenGLRenderer::onBeginScene()
    {
        glEnable(GL_SCISSOR_TEST);
        glClearColor(m_backgroundColor.m_redf, m_backgroundColor.m_greenf, m_backgroundColor.m_bluef, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearDepthf(1.0f);

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK); // GL_BACK GL_FRONT
    }

    /**
    *
    */
    void OpenGLRenderer::onEndScene()
    {
        glDisable(GL_SCISSOR_TEST);
    }

    /**
    *
    */
    void OpenGLRenderer::setOrthographicProjectionMatrix(spark::perspective::OrthographicProjection& orthographicProjection)
    {
        uint16_t screenWidth = m_device->getScreenResolution().m_width;
        uint16_t screenHeight = m_device->getScreenResolution().m_height;
        real32 orthoMatrix[16];
        spark::math::ProjectionMatrixf::createOrthofMatrix(0.0f, (real32)screenWidth, (real32)screenHeight, 0.0f, -1.0f, 1.0, orthoMatrix);

        memcpy(m_projectionViewMatrix.m_matrix, orthoMatrix, sizeof(orthoMatrix));
        if (orthographicProjection.getVirtualResolutionType() != perspective::VirtualResolution::E_NONE)
        {
            glViewport(orthographicProjection.getViewport().m_x, orthographicProjection.getViewport().m_y, orthographicProjection.getViewport().m_width, orthographicProjection.getViewport().m_height);
            glScissor(orthographicProjection.getViewport().m_x, orthographicProjection.getViewport().m_y, orthographicProjection.getViewport().m_width, orthographicProjection.getViewport().m_height);
            math::Matrix4f scaleMatrix;
            scaleMatrix.setScale(orthographicProjection.getViewportTransformationParameter().m_scaleWidth, orthographicProjection.getViewportTransformationParameter().m_scaleHeight, 1.0f);
            m_projectionViewMatrix = m_projectionViewMatrix * scaleMatrix;
        }
        else
        {
            glViewport(orthographicProjection.getViewport().m_x, orthographicProjection.getViewport().m_y, orthographicProjection.getViewport().m_width, orthographicProjection.getViewport().m_height);
        }
        m_shader->setProjectionViewMatrix(m_projectionViewMatrix.getPointer());
    }

    /**
    *
    */
    void OpenGLRenderer::setPerspectiveProjectionMatrix(spark::perspective::PerspectiveProjection& perspectiveProjection)
    {
        uint16_t screenWidth = m_device->getScreenResolution().m_width;
        uint16_t screenHeight = m_device->getScreenResolution().m_height;
        real32 perspectiveArray[16];
        spark::math::ProjectionMatrixf::createPerspectiveMatrix(perspectiveProjection.m_fovy, perspectiveProjection.m_aspect, perspectiveProjection.m_zNear, perspectiveProjection.m_zFar, perspectiveArray);
        spark::math::Matrix4f projectionMatrix;
        memcpy(projectionMatrix.m_matrix, perspectiveArray, sizeof(perspectiveArray));

        real32 lookAtArray[16];
        spark::math::ProjectionMatrixf::createLookAtMatrix(0, 0, 5, 0, 0, 0, 0, 1, 0, lookAtArray);
        spark::math::Matrix4f lookAtMatrix;
        memcpy(lookAtMatrix.m_matrix, lookAtArray, sizeof(lookAtArray));

        m_projectionViewMatrix = projectionMatrix * lookAtMatrix;

        glViewport(0, 0, screenWidth, screenHeight);
        glScissor(0, 0, screenWidth, screenHeight);
        m_shader->setProjectionViewMatrix(m_projectionViewMatrix.getPointer());
    }

    /**
    *
    */
    void OpenGLRenderer::setModelTransformation(math::Matrix4f& modelTransformation)
    {
        math::Matrix4f m = m_projectionViewMatrix * modelTransformation;
        m_shader->setProjectionViewMatrix(m.getPointer());
    }

    /**
    *
    */
    void OpenGLRenderer::drawBackground(const spark::drawing::Color& color)
    {
        m_backgroundColor = spark::drawing::Color(color.m_red, color.m_green, color.m_blue, color.m_alpha);
    }

    /**
    *
    */
    void OpenGLRenderer::draw2DPoint(int16_t x, int16_t y, spark::drawing::Color color)
    {

    }

    /**
    *
    */
    void OpenGLRenderer::draw2DLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, spark::drawing::Color color)
    {
        //std::vector<spark::drawing::Vertex3> vertices = {
        // {(real32)x1, (real32)y1, 0, {color.m_red, color.m_green, color.m_blue, 0}},
        // {(real32)x2, (real32)y2, 0, {color.m_red, color.m_green, color.m_blue, 0}}
        //};

        //spark::renderer::ISparkVertexBuffer* vertexBuffer = m_vertexBufferFactory->createOrUpdate("1", vertices);
        //vertexBuffer->draw();


        GLfloat vertices[] = {
           (GLfloat)x1, (GLfloat)y1,
           (GLfloat)x2, (GLfloat)y2
        };

        GLubyte lineColor[] = {
            color.m_red, color.m_green, color.m_blue, color.m_alpha,
            color.m_red, color.m_green, color.m_blue, color.m_alpha
        };

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, &vertices[0]);
        glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, &lineColor[0]);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(2);

        glDrawArrays(GL_LINES, 0, 2);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(2);
    }

    /**
    *
    */
    void OpenGLRenderer::draw2DCircle(int16_t centerX, int16_t centerY, int16_t radius)
    {

    }

    /**
    *
    */
    void OpenGLRenderer::draw2DRectangle(int16_t x1, int16_t y1, int16_t width, int16_t height)
    {

    }

    /**
    *
    */
    void OpenGLRenderer::draw2DBitmap(spark::drawing::ISparkImage* image, int16_t x, int16_t y)
    {
        spark::drawing::ClippingRectangle clipRect = { 0,0, (uint16_t)image->getWidth(), (uint16_t)image->getHeight() };
        draw2DBitmap(image, x, y, clipRect);
    }

    /**
    *
    */
    void OpenGLRenderer::draw2DBitmap(spark::drawing::ISparkImage* image, int16_t x, int16_t y, const spark::drawing::ClippingRectangle clipRect)
    {
        m_shader->setDrawMode(1);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        spark::renderer::ISparkTexture* texture = m_textureFactory->createOrUpdate(image->getHash(), image->getImageAsStream(), image->getWidth(), image->getHeight(), spark::drawing::E_RGBA8);
        texture->bind();
        image->setTexture(texture);

        GLfloat clipStart = (GLfloat)(1.0 / image->getWidth()) * clipRect.m_x;
        GLfloat clipEnd = (GLfloat)(clipStart + (1.0 / image->getWidth()) * clipRect.m_width);

        GLfloat texureCoords[] = {	// If clipping area is the full size of the image
            clipStart, 1.0,		    // 0.0, 1.0,
            clipEnd, 1.0,		    // 1.0, 1.0,
            clipStart, 0.0,		    // 0.0, 0.0,
            clipEnd, 0.0		    // 1.0, 0.0
        };

        real32 imageHeight = clipRect.m_height;	    // Use the clip height instead image->GetHeight()
        real32 imageWidth = clipRect.m_width;	    // Use the clip width instead image->GetWidth()

        GLfloat vertices[] = {
            (GLfloat)x, imageHeight + (GLfloat)y, 0.0f,
            imageWidth + x, imageHeight + (GLfloat)y, 0.0f,
            (GLfloat)x, (GLfloat)y, 0.0f,
            imageWidth + (GLfloat)x, (GLfloat)y, 0.0f
        };

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, &vertices[0]);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, &texureCoords[0]);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(3);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glDisableVertexAttribArray(3);
        glDisableVertexAttribArray(0);

        glDisable(GL_BLEND);
        m_shader->setDrawMode(0);
    }

    /**
    *
    */
    void OpenGLRenderer::drawTiledLayer(const spark::game::TiledLayer* tiledLayer, int16_t x, int16_t y)
    {
        m_shader->setDrawMode(1);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        spark::drawing::ISparkImage* tilsetImage = tiledLayer->getTilesetImage();

        spark::renderer::ISparkTexture* texture = m_textureFactory->createOrUpdate(tilsetImage->getHash(), tilsetImage->getImageAsStream(), tilsetImage->getWidth(), tilsetImage->getHeight(), spark::drawing::E_RGBA8);
        texture->bind();
        tilsetImage->setTexture(texture);

        if (tiledLayer->getLayerType() == spark::game::E_LAYER_TYPE::ELT_ORTHOGONAL)
        {
            uint16_t* gid = tiledLayer->getGIDData();
            uint16_t tilsetImageWidth = tiledLayer->getTilesetImageWidth();
            uint16_t tilsetImageHeight = tiledLayer->getTilesetImageHeight();
            uint16_t layerRows = tiledLayer->getLayerRows();
            uint16_t layerCols = tiledLayer->getLayerColumns();
            uint16_t tileWidth = tiledLayer->getTileWidth();
            uint16_t tileHeight = tiledLayer->getTileHeight();
            uint16_t tilesetImageRows = tiledLayer->getTilesetImageHeight() / tileHeight;
            uint16_t tilesetImageCols = tiledLayer->getTilesetImageWidth() / tileWidth;

            uint16_t gidIndex = 0;
            std::vector<GLfloat> vertices;
            std::vector<GLfloat> texureCoords;
            for (int row = 0; row < layerRows; row++)
            {
                for (int col = 0; col < layerCols; col++)
                {
                    vertices.push_back(GLfloat(x + (col * tileWidth)));                     // vx0
                    vertices.push_back(GLfloat(y + (row * tileHeight) + tileHeight));       // vy0
                    vertices.push_back(0);                                                  // vz0
                    vertices.push_back(GLfloat(x + (col * tileWidth) + tileWidth));         // vx1
                    vertices.push_back(GLfloat(y + (row * tileHeight) + tileHeight));       // vy1
                    vertices.push_back(0);                                                  // vz1
                    vertices.push_back(GLfloat(x + (col * tileWidth)));                     // vx2
                    vertices.push_back(GLfloat(y + (row * tileHeight)));                    // vy2
                    vertices.push_back(0);                                                  // vz2
                    vertices.push_back(GLfloat(x + (col * tileWidth) + tileWidth));         // vx3
                    vertices.push_back(GLfloat(y + (row * tileHeight)));                    // vy3
                    vertices.push_back(0);                                                  // vz3

                    real32 u = 1.0f / tilesetImageCols;
                    real32 v = 1.0f / tilesetImageRows;

                    uint16_t gid = tiledLayer->getGIDData()[gidIndex];
                    uint16_t gy = gid / tilesetImageCols;
                    uint16_t gx = gid % tilesetImageCols - 1;

                    texureCoords.push_back(gx * u);               // u0
                    texureCoords.push_back(gy * v + v);           // v0
                    texureCoords.push_back(gx * u + u);           // u1
                    texureCoords.push_back(gy * v + v);           // v1
                    texureCoords.push_back(gx * u);               // u2
                    texureCoords.push_back(gy * v);               // v2
                    texureCoords.push_back(gx * u + u);           // u3
                    texureCoords.push_back(gy * v);               // v4    

                    gidIndex++;
                }
            }

            std::vector<GLshort> indicesBuffer;
            GLshort rectangleCount = layerCols * layerRows;
            GLshort indicesBufferSize = 6 * rectangleCount;
            for (int i = 0; i < rectangleCount; i++)
            {
                indicesBuffer.push_back(0 + (i * 4));
                indicesBuffer.push_back(1 + (i * 4));
                indicesBuffer.push_back(2 + (i * 4));
                indicesBuffer.push_back(1 + (i * 4));
                indicesBuffer.push_back(3 + (i * 4));
                indicesBuffer.push_back(2 + (i * 4));
            }

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, &vertices[0]);
            glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, &texureCoords[0]);

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(3);

            glDrawElements(GL_TRIANGLES, indicesBufferSize, GL_UNSIGNED_SHORT, &indicesBuffer[0]);

            glDisableVertexAttribArray(3);
            glDisableVertexAttribArray(0);
        }
        else
        {
            m_logger->error("TiledLayer type is unknown");
        }

        glDisable(GL_BLEND);
        m_shader->setDrawMode(0);
    }

    /**
    *
    */
    void OpenGLRenderer::drawString(const spark::font::E_SYSTEM_FONT_TYPE fontType, const std::string text, spark::drawing::Color color, int16_t x, int16_t y)
    {
        m_shader->setDrawMode(2);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        spark::font::ISparkFont* font = m_device->getSparkFontPool()->getFont();
        spark::uc8_t* fontMapImageData = font->getFontMap();
        uint16_t fontMapWidth = font->getBitmapFontInfo(16).m_textureWidth;
        uint16_t fontMapHeight = font->getBitmapFontInfo(16).m_textureHeight;

        m_shader->setFontColor(color);

        spark::renderer::ISparkTexture* texture = m_textureFactory->createOrUpdate(font->getFontName(), fontMapImageData, fontMapWidth, fontMapHeight, spark::drawing::E_GRAY8);
        texture->bind();
        font->setTexture(texture);

        spark::font::BitmapFontInfo bitmapFontInfo = font->getBitmapFontInfo(16);
        spark::font::BitmapGlyphInfo bitmapGlypInfo = bitmapFontInfo.m_bitmapGlyphs[65];
        spark::uc8_t charId = bitmapGlypInfo.m_charId;

        int16_t advance = 0;
        const char* ch = text.c_str();
        std::vector<spark::drawing::Vertex3> vertices;
        for (uint16_t index = 0; ch[index] != '\0'; index++)
        {
            spark::font::BitmapGlyphInfo gi = font->getBitmapFontInfo(index).m_bitmapGlyphs[ch[index]];
            int16_t px = x + gi.m_xOffset + advance;
            int16_t py = y + (gi.m_height + gi.m_yOffset);
            advance += gi.m_xAdvance;

            spark::drawing::Vertex3 v0(px, py, 0.0f, spark::math::Vector2f(gi.m_uo, gi.m_vo));
            spark::drawing::Vertex3 v1(real32(px + gi.m_width), py, 0.0f, spark::math::Vector2f(gi.m_uo + gi.m_normalizedWidth, gi.m_vo));
            spark::drawing::Vertex3 v2(px, real32(py - gi.m_height), 0.0f, spark::math::Vector2f(gi.m_uo, gi.m_vo + gi.m_normalizedHeight));
            spark::drawing::Vertex3 v3(real32(px + gi.m_width), real32(py - gi.m_height), 0.0f, spark::math::Vector2f(gi.m_uo + gi.m_normalizedWidth, gi.m_vo + gi.m_normalizedHeight));
            vertices.push_back(v0); vertices.push_back(v1); vertices.push_back(v2); vertices.push_back(v3);
        }

        std::vector<GLshort> indicesBuffer;
        GLshort rectangleCount = (GLshort)text.size();
        GLshort indicesBufferSize = 6 * rectangleCount;
        for (int i = 0; i < rectangleCount; i++)
        {
            indicesBuffer.push_back(0 + (i * 4));
            indicesBuffer.push_back(1 + (i * 4));
            indicesBuffer.push_back(2 + (i * 4));
            indicesBuffer.push_back(1 + (i * 4));
            indicesBuffer.push_back(3 + (i * 4));
            indicesBuffer.push_back(2 + (i * 4));
        }

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(spark::drawing::Vertex3), &vertices[0].m_position);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(spark::drawing::Vertex3), &vertices[0].m_textureCoord);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(3);

        glDrawElements(GL_TRIANGLES, indicesBufferSize, GL_UNSIGNED_SHORT, &indicesBuffer[0]);

        glDisableVertexAttribArray(3);
        glDisableVertexAttribArray(0);

        glDisable(GL_BLEND);
        m_shader->setDrawMode(0);
    }

    /**
    *
    */
    void OpenGLRenderer::drawString(const std::string fontFamily, uint32_t size, const std::string text, spark::drawing::Color color, int16_t x, int16_t y)
    {

    }

    /**
    *
    */
    void OpenGLRenderer::renderMesh(spark::geometry::mesh::ISparkMesh* mesh, spark::material::ISparkMaterial* material)
    {
        spark::material::VertexLayout vertexLayout = material->getRequiredMeshVariant();

        spark::renderer::ISparkVertexBuffer* vertexBuffer = m_vertexBufferFactory->createOrUpdate(mesh->getGuid(), mesh, vertexLayout);
        mesh->setVertexBuffer(vertexBuffer);

        applyMaterial(material);
        vertexBuffer->drawTriangles();
    }

    /**
    *
    */
    void OpenGLRenderer::renderPointCloud(spark::geometry::pointcloud::ISparkPointCloud* pointCloud)
    {
        auto vertices = pointCloud->getPoints();
        spark::renderer::ISparkVertexBuffer* vertexBuffer = m_vertexBufferFactory->createOrUpdate(pointCloud->getGuid(), vertices);
        pointCloud->setVertexBuffer(vertexBuffer);
        
        applyMaterial(NULL);
        vertexBuffer->drawPoints();
    }

    /**
    *
    */
    void OpenGLRenderer::applyMaterial(spark::material::ISparkMaterial* material)
    {
        if (material != NULL)
        {
            if (material->getRenderMode() == spark::material::RenderMode::DebugVisualizationNormals)
            {
                m_shader->setDrawMode(3);
            }
            if (material->getRenderMode() == spark::material::RenderMode::DebugVisualizationBarycentric)
            {
                m_shader->setDrawMode(4);
            }
            if (material->getRenderMode() == spark::material::RenderMode::Wireframe)
            {
                m_shader->setDrawMode(5);
            }
        }
        else
        {
            m_shader->setDrawMode(0);
        }
    }

    /**
    *
    */
    void OpenGLRenderer::activateDepthTest(bool flag)
    {
        if (flag)
        {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }
    }
}