#ifndef __SPARK_GEOMETRY_MESH_GENERATOR_MESHGENERATOR_HPP_INCLUDED__
#define __SPARK_GEOMETRY_MESH_GENERATOR_MESHGENERATOR_HPP_INCLUDED__

#include "geometry/mesh/Mesh.hpp"
#include "ISparkMesh.hpp"

namespace spark::geometry::mesh::generator {
    /**
    *
    */
    class MeshGenerator : public SparkRefCount
    {
    public:
        MeshGenerator(void);
        virtual ~MeshGenerator(void);

    public:
        static spark::geometry::mesh::ISparkMesh* createPyramidMesh();
        static spark::geometry::mesh::ISparkMesh* createQuadMesh();
        static spark::geometry::mesh::ISparkMesh* createPlaneMesh();
        static spark::geometry::mesh::ISparkMesh* createSphereMesh(uint32_t recursionLevel = 0);
    };
}
#endif
