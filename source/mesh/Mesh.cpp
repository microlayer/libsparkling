#include "Mesh.hpp"

namespace spark {
    namespace mesh {
        /**
        *
        */
        Mesh::Mesh(void) :
            m_vertexBuffer(NULL)
        {
            if (m_guid.empty())
            {
                m_guid = spark::mlstl::guid::MLGuid::createGuid();
            }
        }

        /**
        *
        */
        Mesh::~Mesh(void)
        {
            m_vertexBuffer->release();
        }

        /**
        *
        */
        std::vector<drawing::Vertex3> Mesh::getVertices()
        {
            return m_vertices;
        }

        /**
        *
        */
        uint32_t Mesh::getVertexCount() const
        {
            return m_vertices.size();
        }

        /**
        *
        */
        std::vector<uint16_t> Mesh::getIndices()
        {
            return m_indices;
        }

        /**
        *
        */
        uint32_t Mesh::getIndexCount() const
        {
            return m_indices.size();
        }

        /**
        *
        */
        std::vector<drawing::Color> Mesh::getColors()
        {
            return m_colors;
        }

        /**
        *
        */
        uint32_t Mesh::getColorCount() const
        {
            return m_colors.size();
        }

        /**
        *
        */
        std::vector<math::Vector3f> Mesh::getNormals()
        {
            return m_normals;
        }

        /**
        *
        */
        uint32_t Mesh::getNormalsCount() const
        {
            return m_normals.size();
        }

        /**
        *
        */
        std::vector<math::Vector2f> Mesh::getTextureCoords()
        {
            return m_textureCoords;
        }

        /**
        *
        */
        uint32_t Mesh::getTextureCoordsCount() const
        {
            return m_textureCoords.size();
        }

        /**
        *
        */
        drawing::Vertex3 Mesh::getVertex(uint32_t index)
        {
            return m_vertices[index];
        }

        /**
        *
        */
        drawing::Color Mesh::getColor(uint32_t index)
        {
            return m_colors[index];
        }

        /**
        *
        */
        math::Vector3f& Mesh::getNormal(uint32_t index)
        {
            return m_normals[index];
        }

        /**
        *
        */
        math::Vector2f& Mesh::getTextureCoords(uint32_t index)
        {
            return m_textureCoords[index];
        }

        /**
        * Adds a vertex to the mesh - this is the default way to feed the mesh with vertices.
        */
        void Mesh::addVertex(drawing::Vertex3 vertex)
        {
            m_vertices.push_back(vertex);
            m_colors.push_back(vertex.m_color);
            m_normals.push_back(vertex.m_normal);
            m_textureCoords.push_back(vertex.m_textureCoord);
        }

        /**
        * Adds in index to the index list
        */
        void Mesh::addIndex(uint32_t index)
        {
            m_indices.push_back(index);
        }

        /**
        * Sets the normal vector of a vertex
        */
        void Mesh::setNormal(uint32_t index, math::Vector3f v)
        {
            if (index < m_normals.size())
            {
                m_normals[index] = v;
            }
        }

        /**
        *
        */
        void Mesh::setColor(spark::drawing::Color color)
        {
            for (uint32_t i = 0; i < m_colors.size(); i++)
            {
                m_colors[i] = color;
            }
        }

        /**
        *
        */
        std::string Mesh::getGuid() const
        {
            return m_guid;
        }

        /**
        *
        */
        void Mesh::setVertexBuffer(spark::renderer::ISparkVertexBuffer* vertexBuffer)
        {
            m_vertexBuffer = vertexBuffer;
        }
    } // end namespace mesh
} // end namespace spark