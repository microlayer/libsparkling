#include "OpenGLRenderer.hpp"

namespace spark {
    namespace renderer {
        /**
        *
        */
        OpenGLRenderer::OpenGLRenderer(spark::device::ISparkDevice* device, spark::renderer::shader::ISparkShader* shader) :
            AbstractSparkRenderer(device, shader)
        {

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
            glClearColor(0.1f, 0.3f, 0.2f, 1.0f);
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
        void OpenGLRenderer::draw2DBitmap(const spark::drawing::ISparkImage* image, int16_t x, int16_t y)
        {
            m_shader->setDrawMode(1);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glUniform1i(glGetUniformLocation(1, "utexture0"), 0);
            spark::drawing::ClippingRectangle clipRect(0, 0, image->getWidth(), image->getHeight());
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getImageAsStream());

            GLenum err = glGetError();
            if (glGetError() != err)
            {
                m_logger->error("Error loading texture into OpenGL with reason: %s code: %i", "Undefined", err);
            }

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            GLfloat clipStart = (GLfloat)(1.0 / image->getWidth()) * clipRect.m_x;
            GLfloat clipEnd = (GLfloat)(clipStart + (1.0 / image->getWidth())) * clipRect.m_width;

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
            m_shader->setDrawMode(0);
        }

        /**
        *
        */
        void OpenGLRenderer::draw2DBitmap(const spark::drawing::ISparkImage* image, int16_t x, int16_t y, const spark::drawing::ClippingRectangle clipRect)
        {

        }

        /**
        *
        */
        void OpenGLRenderer::drawTiledLayer(const spark::game::TiledLayer* tiledLayer, int16_t x, int16_t y)
        {
            m_shader->setDrawMode(1);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glUniform1i(glGetUniformLocation(1, "utexture0"), 0);
            const spark::drawing::ISparkImage* tilsetImage = tiledLayer->getTilesetImage();
            spark::drawing::ClippingRectangle clipRect(0, 0, tilsetImage->getWidth(), tilsetImage->getHeight());
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tilsetImage->getWidth(), tilsetImage->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tilsetImage->getImageAsStream());

            GLenum err = glGetError();
            if (glGetError() != err)
            {
                m_logger->error("Error loading texture into OpenGL with reason: %s code: %i", "Undefined", err);
            }

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            if (tiledLayer->getLayerType() == spark::game::TiledLayer::ELT_ORTHOGONAL)
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
                        vertices.push_back(x + (col * tileWidth));                  // vx0
                        vertices.push_back(y + (row * tileHeight) + tileHeight);    // vy0
                        vertices.push_back(0);                                      // vz0
                        vertices.push_back(x + (col * tileWidth) + tileWidth);      // vx1
                        vertices.push_back(y + (row * tileHeight) + tileHeight);    // vy1
                        vertices.push_back(0);                                      // vz1
                        vertices.push_back(x + (col * tileWidth));                  // vx2
                        vertices.push_back(y + (row * tileHeight));                 // vy2
                        vertices.push_back(0);                                      // vz2
                        vertices.push_back(x + (col * tileWidth) + tileWidth);      // vx3
                        vertices.push_back(y + (row * tileHeight));                 // vy3
                        vertices.push_back(0);                                      // vz3

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
                GLshort indicesBufferSize = 6 * layerCols * layerRows;
                for (int i = 0; i < indicesBufferSize; i++)
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
            m_shader->setDrawMode(1);

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glUniform1i(glGetUniformLocation(1, "utexture0"), 0);

            spark::font::ISparkFont* font = m_device->getSparkFontPool()->getFont();
            spark::uc8_t* fontMapImageData = font->getFontMap();
            uint16_t fontMapWidth = font->getBitmapFontInfo(16).m_textureWidth;
            uint16_t fontMapHeight = font->getBitmapFontInfo(16).m_textureHeight;

            glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, fontMapWidth, fontMapHeight, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, fontMapImageData);
            GLenum err = glGetError();
            if (glGetError() != err)
            {
                m_logger->error("Error loading texture into OpenGL with reason: %s code: %i", "Undefined", err);
            }

            spark::font::BitmapFontInfo bitmapFontInfo = font->getBitmapFontInfo(16);
            spark::font::BitmapGlyphInfo bitmapGlypInfo = bitmapFontInfo.m_bitmapGlyphs[65];

            spark::uc8_t charId = bitmapGlypInfo.m_charId;

            GLfloat texureCoords[] = {
                0.0, 0.0,
                1.0, 0.0,
                0.0, 1.0,
                1.0, 1.0
            };

            GLfloat vertices[] = {
               (GLfloat)x, fontMapHeight + (GLfloat)y, 0.0f,
               fontMapWidth + x, fontMapHeight + (GLfloat)y, 0.0f,
               (GLfloat)x, (GLfloat)y, 0.0f,
               fontMapWidth + (GLfloat)x, (GLfloat)y, 0.0f
            };

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, &vertices[0]);
            glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, &texureCoords[0]);

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(3);

            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

            glDisableVertexAttribArray(3);
            glDisableVertexAttribArray(0);

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
        void OpenGLRenderer::renderMesh(spark::mesh::ISparkMesh* mesh)
        {
            // void* pVertices = mesh->getVertices();
            // void* pIndices = mesh->getIndices();
            // void* pColors = mesh->getColors();
            // void* pNormals = mesh->getNormals();
            // void* pTextureCoords = mesh->getTextureCoords();*/

            std::vector<spark::drawing::Vertex3> vertices = mesh->getVertices();
            std::vector<uint16_t> indices = mesh->getIndices();
            std::vector<spark::drawing::Color> colors = mesh->getColors();
            std::vector<spark::math::Vector3f> normals = mesh->getNormals();
            std::vector<spark::math::Vector2f> textureCoords = mesh->getTextureCoords();

            // // Vertices: Cast the vector back
            // std::vector<drawing::Vertex3>* pVerticesArray = reinterpret_cast<std::vector<drawing::Vertex3>*>(pVertices);

            // // Colors:
            // uc8_t* pColorsArray = (uc8_t*)pColors;

            // // Faces:
            // uint16_t* pIndicesArray = (uint16_t*)pIndices;

            // // Normals:
            // real32* pNormalArray = (real32*)pNormals;

            // // Texture coords
            // real32* pTextureCoord = (real32*)pTextureCoords;


            // // Hint: Transfers each frame vertex data to the graphics hardware
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(drawing::Vertex3), &vertices[0]);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, &normals[0]);
            glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(drawing::Color), &colors[0]);
            glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, &textureCoords[0]);

            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            glEnableVertexAttribArray(3);

            glDrawElements(GL_TRIANGLES, mesh->getIndexCount(), GL_UNSIGNED_SHORT, &indices[0]);

            glDisableVertexAttribArray(3);
            glDisableVertexAttribArray(2);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(0);
        }
    } // end namespace renderer
} // end namespace spark