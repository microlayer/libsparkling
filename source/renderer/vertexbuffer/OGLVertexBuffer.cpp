#include "OGLVertexBuffer.hpp"

namespace spark {
    namespace renderer {
        namespace vertexbuffer {
            /**
            *
            */
            OGLVertexBuffer::OGLVertexBuffer(spark::log::ISparkLogger* logger, std::vector<spark::drawing::Vertex3>& vertices) :
                m_bufferSizeVertices(0),
                m_bufferSizeColor(0)
            {
                for (auto& vertex : vertices) {
                    m_verticesData.push_back(vertex.m_x);
                    m_verticesData.push_back(vertex.m_y);
                    m_verticesData.push_back(vertex.m_z);
                    m_colorData.push_back(vertex.m_color.m_red);
                    m_colorData.push_back(vertex.m_color.m_green);
                    m_colorData.push_back(vertex.m_color.m_blue);
                    m_colorData.push_back(vertex.m_color.m_alpha);
                }

                m_bufferSizeVertices = m_verticesData.size() * 4;
                m_bufferSizeColor = m_colorData.size() * 1;

                allocateBuffer();
                uploadBuffer();
            }

            /**
            *
            */
            OGLVertexBuffer::OGLVertexBuffer(spark::log::ISparkLogger* logger, spark::mesh::ISparkMesh* mesh) :
                m_mesh(mesh),
                m_bufferSizeVertices(0),
                m_bufferSizeColor(0)
            {
                for (auto& vertex : mesh->getVertices()) {
                    m_verticesData.push_back(vertex.m_x);
                    m_verticesData.push_back(vertex.m_y);
                    m_verticesData.push_back(vertex.m_z);
                    m_colorData.push_back(vertex.m_color.m_red);
                    m_colorData.push_back(vertex.m_color.m_green);
                    m_colorData.push_back(vertex.m_color.m_blue);
                    m_colorData.push_back(vertex.m_color.m_alpha);
                }

                m_bufferSizeVertices = mesh->getVertices().size() * 3 * sizeof(real32);         // 24*3* 4 bytes=96
                m_bufferSizeColor = mesh->getColors().size() * 4 * sizeof(uc8_t);               // 24*3* 1 byte=24
                m_bufferSizeIndices = m_mesh->getIndices().size() * sizeof(uint16_t);           // 36*1* 2 bytes=72

                allocateBuffer();
                uploadBuffer();
            }

            /**
            *
            */
            OGLVertexBuffer::~OGLVertexBuffer()
            {
                glDeleteBuffers(1, &m_vbo);
                glDeleteBuffers(1, &m_cbo);
                glDeleteBuffers(1, &m_ibo);
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

                //Create VBO for vertices
                glGenBuffers(1, &m_vbo);
                glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                glBufferData(GL_ARRAY_BUFFER, m_bufferSizeVertices, NULL, GL_DYNAMIC_DRAW); // Allocate but not upload on GPU yet
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
                glEnableVertexAttribArray(0);

                // Create VBO for colors
                glGenBuffers(1, &m_cbo);
                glBindBuffer(GL_ARRAY_BUFFER, m_cbo);
                glBufferData(GL_ARRAY_BUFFER, m_bufferSizeColor, NULL, GL_DYNAMIC_DRAW); // Allocate but not upload on GPU yet
                glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)0);
                glEnableVertexAttribArray(2);

                // Create VBO for indices
                glGenBuffers(1, &m_ibo);
            }

            /**
            *
            */
            void OGLVertexBuffer::uploadBuffer()
            {
                glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_bufferSizeVertices, &m_verticesData[0]);
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                glBindBuffer(GL_ARRAY_BUFFER, m_cbo);
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_bufferSizeColor, &m_colorData[0]);
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_bufferSizeIndices, &m_mesh->getIndices()[0], GL_STATIC_DRAW);
            }

            /**
            *
            */
            void OGLVertexBuffer::draw()
            {
                glBindVertexArray(m_vao); // The VAO stores all attribute pointer configurations,        
                glDrawArrays(GL_LINES, 0, 2);
                glBindVertexArray(0);
            }

            /**
            *
            */
            void OGLVertexBuffer::drawTrinagles()
            {
                glBindVertexArray(m_vao); // The VAO stores all attribute pointer configurations                
                glDrawElements(GL_TRIANGLES, m_mesh->getIndices().size(), GL_UNSIGNED_SHORT, NULL);
                glBindVertexArray(0);
            }
        }
    }
}