#ifndef __SPARK_RENDERER_ISPARKVERTEXBUFFERFACTORY_HPP_INCLUDED__
#define __SPARK_RENDERER_ISPARKVERTEXBUFFERFACTORY_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkVertexBuffer.hpp"
#include "ISparkMesh.hpp"
#include <string>
#include <vector>

namespace spark {
    namespace renderer {
        /**
        *
        */
        class ISparkVertexBufferFactory : public virtual spark::SparkRefCount
        {
        public:
            virtual spark::renderer::ISparkVertexBuffer* createOrUpdate(std::string id, std::vector<spark::drawing::Vertex3>& vertices) = 0;
            virtual spark::renderer::ISparkVertexBuffer* createOrUpdate(std::string id, spark::mesh::ISparkMesh* mesh) = 0;
        };
    } // end namespace renderer
} // end namespace spark
#endif