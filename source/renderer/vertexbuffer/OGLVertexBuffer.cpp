#include "OGLVertexBuffer.hpp"

namespace spark {
    namespace renderer {
        namespace vertexbuffer {
            /**
            *
            */
            OGLVertexBuffer::OGLVertexBuffer(spark::log::ISparkLogger* logger, std::vector<spark::drawing::Vertex3>& vertices)
            {
                // Create VAO
                glGenVertexArrays(1, &m_vao);
                glBindVertexArray(m_vao);

                // Create VBO for vertices
                glGenBuffers(1, &m_vbo);
                glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4, nullptr, GL_DYNAMIC_DRAW); //
            }

            /**
            *
            */
            OGLVertexBuffer::~OGLVertexBuffer()
            {

            }

            /**
            *
            */
            void OGLVertexBuffer::bind()
            {

            }
        }
    }
}