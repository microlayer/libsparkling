#ifndef __SPARK_MESH_ISPARKMESH_HPP_INCLUDED__
#define __SPARK_MESH_ISPARKMESH_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "math/Vector3.hpp"
#include "math/Vector2.hpp"
#include "drawing/Color.hpp"
#include "drawing/Vertex3.hpp"
#include <vector>

namespace spark {
    namespace mesh {

        /**
        *
        */
        class ISparkMesh : public virtual spark::SparkRefCount
        {

        public:
            /**
            *
            */
            virtual std::vector<drawing::Vertex3> getVertices() = 0;

            /**
            * Returns the count of vertices used by this mesh
            */
            virtual uint32_t getVertexCount() const = 0;

            /**
            *
            */
            virtual std::vector<uint16_t> getIndices() = 0;

            /**
            * Returns the count of indices used by this mesh
            */
            virtual uint32_t getIndexCount() const = 0;

            /**
            *
            */
            virtual std::vector<drawing::Color> getColors() = 0;

            /**
            * Returns the count of color components - (vertices*4)
            */
            virtual uint32_t getColorCount() const = 0;

            /**
            *
            */
            virtual std::vector<math::Vector3f> getNormals() = 0;

            /**
            * Returns the count of normals
            */
            virtual uint32_t getNormalsCount() const = 0;

            /**
            *
            */
            virtual std::vector<math::Vector2f> getTextureCoords() = 0;

            /**
            * Returns the count of texture coords
            */
            virtual uint32_t getTextureCoordsCount() const = 0;

            /**
            *  Returns the vertex with the specified index
            */
            virtual drawing::Vertex3 getVertex(uint32_t index) = 0;

            /**
            * Returns the color of the vertex with the specified index
            */
            virtual drawing::Color getColor(uint32_t index) = 0;

            /**
            * Returns the normal of the vertex with the specified index
            */
            virtual math::Vector3f& getNormal(uint32_t index) = 0;

            /**
            * Returns the texture coords of the vertex with the specified index
            */
            virtual math::Vector2f& getTextureCoords(uint32_t index) = 0;

            /**
            * Sets Color for this mesh
            */
            virtual void setColor(spark::drawing::Color color) = 0;
        };
    } // end namespace mesh
} // end namespace spark
#endif