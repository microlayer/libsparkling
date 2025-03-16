#include "OGLVertexBuffer.hpp"

namespace spark {
    namespace renderer {
        namespace vertexbuffer {
            /**
            *
            */
            OGLVertexBuffer::OGLVertexBuffer(spark::log::ISparkLogger* logger, std::vector<spark::drawing::Vertex3>& vertices) :
                m_vertices(vertices)
            {
                allocateBuffer();
                uploadBuffer();
            }

            OGLVertexBuffer::~OGLVertexBuffer()
            {
                glDeleteBuffers(1, &m_vbo);
                glDeleteBuffers(1, &m_cbo);
                glDeleteVertexArrays(1, &m_vao);
            }

            /**
            *
            */
            void OGLVertexBuffer::allocateBuffer()
            {
                // Create VAO
                glGenVertexArrays(1, &m_vao);
                glBindVertexArray(m_vao);

                // Create VBO for vertices
                glGenBuffers(1, &m_vbo);
                glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4, nullptr, GL_DYNAMIC_DRAW); // Allocate but not upload yet
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
                glEnableVertexAttribArray(0);

                // Create VBO for colors
                glGenBuffers(1, &m_cbo);
                glBindBuffer(GL_ARRAY_BUFFER, m_cbo);
                glBufferData(GL_ARRAY_BUFFER, sizeof(GLubyte) * 8, nullptr, GL_DYNAMIC_DRAW); // Allocate but not upload yet
                glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)0);
                glEnableVertexAttribArray(2);
            }

            /**
            *
            */
            void OGLVertexBuffer::uploadBuffer()
            {
                glBindVertexArray(m_vao);
                glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(spark::drawing::Vertex3), &m_vertices[0]);
                glBindBuffer(GL_ARRAY_BUFFER, m_cbo);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(spark::drawing::Vertex3), &m_vertices[0].m_color);
            }

            /**
            *
            */
            void OGLVertexBuffer::draw()
            {
                glBindVertexArray(m_vao); // The VAO stores all attribute pointer configurations,
                glDrawArrays(GL_LINES, 0, 2);
            }
        }
    }
}