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
            glClearColor(0.5f, 0.5f, 0, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearDepthf(1.0f);
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
        void OpenGLRenderer::setOrthographicProjection(spark::perspective::OrthographicProjection& orthographicProjection)
        {
            uint16_t screenWidth = m_device->getScreenResolution().m_width;
            uint16_t screenHeight = m_device->getScreenResolution().m_height;
            real32 orthoMatrix[16];
            spark::math::ProjectionMatrixf::createOrthofMatrix(0.0f, (real32)screenWidth, (real32)screenHeight, 0.0f, -1.0f, 1.0, orthoMatrix);
            spark::math::Matrix4f projectionViewMatrix;
            memcpy(projectionViewMatrix.m_matrix, orthoMatrix, sizeof(orthoMatrix));
            if (orthographicProjection.getVirtualResolutionType() != perspective::VirtualResolution::E_NONE)
            {
                glViewport(orthographicProjection.getViewport().m_x, orthographicProjection.getViewport().m_y, orthographicProjection.getViewport().m_width, orthographicProjection.getViewport().m_height);
                glScissor(orthographicProjection.getViewport().m_x, orthographicProjection.getViewport().m_y, orthographicProjection.getViewport().m_width, orthographicProjection.getViewport().m_height);
                math::Matrix4f m;
                m.setScale(orthographicProjection.getViewportTransformationParameter().m_scaleWidth, orthographicProjection.getViewportTransformationParameter().m_scaleHeight, 1.0f);
                projectionViewMatrix = projectionViewMatrix * m;
            }
            else
            {
                glViewport(orthographicProjection.getViewport().m_x, orthographicProjection.getViewport().m_y, orthographicProjection.getViewport().m_width, orthographicProjection.getViewport().m_height);
            }
            m_shader->setProjectionViewMatrix(projectionViewMatrix.getPointer());
        }

        /**
        *
        */
        void OpenGLRenderer::setPerspectiveProjection(spark::perspective::PerspectiveProjection& perspectiveProjection)
        {
            real32 perspectiveMatrix[16];
            spark::math::ProjectionMatrixf::createPerspectiveMatrix(perspectiveProjection.m_fovy, perspectiveProjection.m_aspect, perspectiveProjection.m_zNear, perspectiveProjection.m_zFar, perspectiveMatrix);
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
        void OpenGLRenderer::draw2DBitmap(const spark::drawing::ISparkImage* image, int16_t x, int16_t y)
        {
            //GLuint textureID;
            //glBindTexture(GL_TEXTURE_2D, textureID);

            //spark::drawing::ClippingRectangle clipRect(0, 0, image->getWidth(), image->getHeight());
            //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->getImageAsStream());

            //GLenum err = glGetError();
            //if (glGetError() != err)
            //{
            //    m_logger->error("Error loading texture into OpenGL with reason: %s code: %i", "Undefined", err);
            //}

            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            //real32 clipStart = (1.0 / image->getWidth()) * clipRect.m_x;
            //real32 clipEnd = clipStart + (1.0 / image->getWidth()) * clipRect.m_width;

            //GLfloat texureCoords[] = {	// If clipping area is the full size of the image
            //    clipStart, 1.0,		    // 0.0, 1.0,
            //    clipEnd, 1.0,		    // 1.0, 1.0,
            //    clipStart, 0.0,		    // 0.0, 0.0,
            //    clipEnd, 0.0		    // 1.0, 0.0
            //};

            //real32 imageHeight = clipRect.m_height;	    // Use the clip height instead image->GetHeight()
            //real32 imageWidth = clipRect.m_width;	    // Use the clip width instead image->GetWidth()

            //GLfloat vertices[] = {
            //    0.0f + x, -imageHeight + -y, 0.0f,
            //    imageWidth + x, -imageHeight + -y, 0.0f,
            //    0.0f + x, 0.0f + -y, 0.0f,
            //    imageWidth + x, 0.0f + -y, 0.0f
            //};

            //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, &vertices[0]);
            //glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, &texureCoords[0]);

            //glEnableVertexAttribArray(0);
            //glEnableVertexAttribArray(3);

            //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

            //glDisableVertexAttribArray(3);
            //glDisableVertexAttribArray(0);
        }

        /**
        *
        */
        void OpenGLRenderer::renderMesh(spark::mesh::ISparkMesh* mesh)
        {

        }
    } // end namespace renderer
} // end namespace spark