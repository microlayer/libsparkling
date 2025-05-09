#ifndef __SPARK_MESH_MESH_HPP_INCLUDED__
#define __SPARK_MESH_MESH_HPP_INCLUDED__

#include "ISparkMesh.hpp"
#include "ISparkVertexBuffer.hpp"
#include "drawing/Vertex3.hpp"
#include "math/Vector3.hpp"
#include "mlstl/MLGuid.hpp"
#include <vector>
#include <string>

namespace spark {
    namespace mesh {
        /**
        *
        */
        class Mesh : public ISparkMesh
        {
        public:
            Mesh(void);
            virtual ~Mesh(void);

        public: // ISparkMesh
            std::vector<drawing::Vertex3> getVertices();
            uint32_t getVertexCount() const;

            std::vector<uint16_t> getIndices();
            uint32_t getIndexCount() const;

            std::vector<drawing::Color> getColors();
            uint32_t getColorCount() const;

            std::vector<math::Vector3f> getNormals();
            uint32_t getNormalsCount() const;

            std::vector<math::Vector2f> getTextureCoords();
            uint32_t getTextureCoordsCount() const;

            drawing::Vertex3 getVertex(uint32_t index);
            drawing::Color getColor(uint32_t index);
            math::Vector3f& getNormal(uint32_t index);
            math::Vector2f& getTextureCoords(uint32_t index);

            void setColor(spark::drawing::Color color);

            void setVertexBuffer(spark::renderer::ISparkVertexBuffer* vertexBuffer);

            std::string getGuid() const;

        public:
            void addVertex(drawing::Vertex3 vertex);
            void addIndex(uint32_t index);
            void setNormal(uint32_t index, math::Vector3f v);

        private:
            std::vector<drawing::Vertex3> m_vertices;
            std::vector<uint16_t> m_indices;
            std::vector<drawing::Color> m_colors;
            std::vector<math::Vector3f> m_normals;
            std::vector<math::Vector2f> m_textureCoords;

        private:
            std::string m_guid;

        private:
            spark::renderer::ISparkVertexBuffer* m_vertexBuffer;
        };
    } // end namespace mesh
} // end namespace spark
#endif