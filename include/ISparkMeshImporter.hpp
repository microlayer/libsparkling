#ifndef __SPARK_GEOMETRY_MESH_IMPORTER_ISPARKMESHIMPORTER_HPP_INCLUDED__
#define __SPARK_GEOMETRY_MESH_IMPORTER_ISPARKMESHIMPORTER_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkMesh.hpp"

namespace spark::geometry::mesh::importer {
    /**
    *
    */
    class ISparkMeshImporter : public virtual spark::SparkRefCount
    {
    public:
        virtual spark::geometry::mesh::ISparkMesh* loadMesh() = 0;
    };
}
#endif