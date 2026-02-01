#include "OGLVertexBuffer.hpp"

namespace spark::renderer::vertexbuffer {
    /**
    *
    */
    OGLVertexBuffer::OGLVertexBuffer(spark::log::ISparkLogger* logger, std::vector<spark::drawing::Vertex3>& vertices) :
        m_bufferSizeVertices(0),
        m_bufferSizeColor(0)
    {
        for (auto& vertex : vertices)
        {
            m_verticesData.push_back(vertex.m_x);
            m_verticesData.push_back(vertex.m_y);
            m_verticesData.push_back(vertex.m_z);
            m_normalData.push_back(vertex.m_normal.m_x);
            m_normalData.push_back(vertex.m_normal.m_y);
            m_normalData.push_back(vertex.m_normal.m_z);
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
    OGLVertexBuffer::OGLVertexBuffer(spark::log::ISparkLogger* logger, spark::geometry::mesh::ISparkMesh* mesh, spark::material::VertexLayout vertexLayout) :
        m_mesh(mesh),
        m_bufferSizeVertices(0),
        m_bufferSizeNormals(0),
        m_bufferSizeColor(0),
        m_bufferSizeBarycentric(0),
        m_vertexLayout(vertexLayout)
    {
        if (m_vertexLayout == spark::material::VertexLayout::Indexed)
        {
            buildIndexedGPULayout();
        }
        else
        {
            buildNonIndexedGPULayout();
        }

        allocateBuffer();
        uploadBuffer();
    }

    /**
    *
    */
    void OGLVertexBuffer::buildIndexedGPULayout()
    {
        for (auto& vertex : m_mesh->getVertices()) {
            m_verticesData.push_back(vertex.m_x);
            m_verticesData.push_back(vertex.m_y);
            m_verticesData.push_back(vertex.m_z);
            m_normalData.push_back(vertex.m_normal.m_x);
            m_normalData.push_back(vertex.m_normal.m_y);
            m_normalData.push_back(vertex.m_normal.m_z);
            m_colorData.push_back(vertex.m_color.m_red);
            m_colorData.push_back(vertex.m_color.m_green);
            m_colorData.push_back(vertex.m_color.m_blue);
            m_colorData.push_back(vertex.m_color.m_alpha);
        }

        m_bufferSizeVertices = m_mesh->getVertices().size() * 3 * sizeof(real32);           // Vertex Count * 3 * 4 bytes=96
        m_bufferSizeNormals = m_mesh->getNormals().size() * 3 * sizeof(real32);             // Vertex Count * 3 * 4 bytes=96
        m_bufferSizeColor = m_mesh->getColors().size() * 4 * sizeof(uc8_t);                 // Vertex Count * 3 * 1 byte=24               
        m_bufferSizeIndices = m_mesh->getIndices().size() * sizeof(uint16_t);               // Vertex Count * 1 * 2 bytes=72
    }

    /**
    *
    */
    void OGLVertexBuffer::buildNonIndexedGPULayout()
    {
        for (size_t i = 0; i < m_mesh->getIndices().size(); i += 3)
        {
            uint16_t i0 = m_mesh->getIndices()[i + 0];
            uint16_t i1 = m_mesh->getIndices()[i + 1];
            uint16_t i2 = m_mesh->getIndices()[i + 2];

            // Vertex 0
            m_verticesData.push_back(m_mesh->getVertex(i0).m_x);
            m_verticesData.push_back(m_mesh->getVertex(i0).m_y);
            m_verticesData.push_back(m_mesh->getVertex(i0).m_z);

            m_normalData.push_back(m_mesh->getVertex(i0).m_normal.m_x);
            m_normalData.push_back(m_mesh->getVertex(i0).m_normal.m_y);
            m_normalData.push_back(m_mesh->getVertex(i0).m_normal.m_z);

            m_colorData.push_back(m_mesh->getVertex(i0).m_color.m_red);
            m_colorData.push_back(m_mesh->getVertex(i0).m_color.m_green);
            m_colorData.push_back(m_mesh->getVertex(i0).m_color.m_blue);
            m_colorData.push_back(m_mesh->getVertex(i0).m_color.m_alpha);

            m_barycentricData.push_back(1.0f);
            m_barycentricData.push_back(0.0f);
            m_barycentricData.push_back(0.0f);

            // Vertex 1
            m_verticesData.push_back(m_mesh->getVertex(i1).m_x);
            m_verticesData.push_back(m_mesh->getVertex(i1).m_y);
            m_verticesData.push_back(m_mesh->getVertex(i1).m_z);

            m_normalData.push_back(m_mesh->getVertex(i1).m_normal.m_x);
            m_normalData.push_back(m_mesh->getVertex(i1).m_normal.m_y);
            m_normalData.push_back(m_mesh->getVertex(i1).m_normal.m_z);

            m_colorData.push_back(m_mesh->getVertex(i1).m_color.m_red);
            m_colorData.push_back(m_mesh->getVertex(i1).m_color.m_green);
            m_colorData.push_back(m_mesh->getVertex(i1).m_color.m_blue);
            m_colorData.push_back(m_mesh->getVertex(i1).m_color.m_alpha);

            m_barycentricData.push_back(0.0f);
            m_barycentricData.push_back(1.0f);
            m_barycentricData.push_back(0.0f);

            // Vertex 2
            m_verticesData.push_back(m_mesh->getVertex(i2).m_x);
            m_verticesData.push_back(m_mesh->getVertex(i2).m_y);
            m_verticesData.push_back(m_mesh->getVertex(i2).m_z);

            m_normalData.push_back(m_mesh->getVertex(i2).m_normal.m_x);
            m_normalData.push_back(m_mesh->getVertex(i2).m_normal.m_y);
            m_normalData.push_back(m_mesh->getVertex(i2).m_normal.m_z);

            m_colorData.push_back(m_mesh->getVertex(i2).m_color.m_red);
            m_colorData.push_back(m_mesh->getVertex(i2).m_color.m_green);
            m_colorData.push_back(m_mesh->getVertex(i2).m_color.m_blue);
            m_colorData.push_back(m_mesh->getVertex(i2).m_color.m_alpha);

            m_barycentricData.push_back(0.0f);
            m_barycentricData.push_back(0.0f);
            m_barycentricData.push_back(1.0f);
        }

        m_bufferSizeVertices = m_verticesData.size() * sizeof(real32);
        m_bufferSizeNormals = m_normalData.size() * sizeof(real32);
        m_bufferSizeColor = m_colorData.size() * sizeof(uc8_t);
        m_bufferSizeBarycentric = m_barycentricData.size() * sizeof(real32);
        m_verticesCount = m_verticesData.size() / 3;
    }

    /**
    *
    */
    OGLVertexBuffer::~OGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_nbo);
        glDeleteBuffers(1, &m_cbo);
        glDeleteBuffers(1, &m_bbo);
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

        // Create VBO for normal
        glGenBuffers(1, &m_nbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
        glBufferData(GL_ARRAY_BUFFER, m_bufferSizeNormals, NULL, GL_DYNAMIC_DRAW); // Allocate but not upload on GPU yet
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(1);

        // Create VBO for colors
        glGenBuffers(1, &m_cbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_cbo);
        glBufferData(GL_ARRAY_BUFFER, m_bufferSizeColor, NULL, GL_DYNAMIC_DRAW); // Allocate but not upload on GPU yet
        glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)0);
        glEnableVertexAttribArray(2);

        // Create VBO for barycentric
        if (!m_barycentricData.empty())
        {
            glGenBuffers(1, &m_bbo);
            glBindBuffer(GL_ARRAY_BUFFER, m_bbo);
            glBufferData(GL_ARRAY_BUFFER, m_bufferSizeBarycentric, NULL, GL_DYNAMIC_DRAW); // Allocate but not upload on GPU yet
            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(4);
        }

        // Create VBO for indices
        glGenBuffers(1, &m_ibo);
    }

    /**
    *
    */
    void OGLVertexBuffer::uploadBuffer()
    {
        if (!m_verticesData.empty())
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, m_bufferSizeVertices, &m_verticesData[0]);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        if (!m_normalData.empty())
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, m_bufferSizeNormals, &m_normalData[0]);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

        }

        if (!m_colorData.empty())
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_cbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, m_bufferSizeColor, &m_colorData[0]);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        if (!m_barycentricData.empty())
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_bbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, m_bufferSizeBarycentric, &m_barycentricData[0]);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        if (m_bufferSizeIndices > 0)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_bufferSizeIndices, &m_mesh->getIndices()[0], GL_STATIC_DRAW);
        }
    }

    /**
    *
    */
    void OGLVertexBuffer::drawPoints()
    {
        glBindVertexArray(m_vao); // The VAO stores all attribute pointer configurations,        
        glDrawArrays(GL_POINTS, 0, 0);
        glBindVertexArray(0);
    }

    /**
    *
    */
    void OGLVertexBuffer::drawLines()
    {
        glBindVertexArray(m_vao); // The VAO stores all attribute pointer configurations,        
        glDrawArrays(GL_LINES, 0, 2);
        glBindVertexArray(0);
    }

    /**
    *
    */
    void OGLVertexBuffer::drawTriangles()
    {
        glBindVertexArray(m_vao); // The VAO stores all attribute pointer configurations                
        if (m_vertexLayout == spark::material::VertexLayout::Indexed)
        {
            glDrawElements(GL_TRIANGLES, m_mesh->getIndices().size(), GL_UNSIGNED_SHORT, NULL);
        }
        else
        {
            glDrawArrays(GL_TRIANGLES, 0, m_verticesCount);
        }
        glBindVertexArray(0);
    }
}
