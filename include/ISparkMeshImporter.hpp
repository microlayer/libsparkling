#ifndef __SPARK_MESH_IMPORTER_ISPARKMESHIMPORTER_HPP_INCLUDED__
#define __SPARK_MESH_IMPORTER_ISPARKMESHIMPORTER_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkMesh.hpp"

namespace spark {
    namespace mesh {
        namespace importer {
            /**
            *
            */
            class ISparkMeshImporter : public virtual spark::SparkRefCount
            {
            public:
                virtual spark::mesh::ISparkMesh* loadMesh(std::string fileName) = 0;
            };
        }
    }
}
#endif