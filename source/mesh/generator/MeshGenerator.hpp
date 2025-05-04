#ifndef __SPARK_MESH_MESHGENERATOR_HPP_INCLUDED__
#define __SPARK_MESH_MESHGENERATOR_HPP_INCLUDED__

#include "mesh/Mesh.hpp"
#include "ISparkMesh.hpp"

namespace spark {
    namespace mesh {

        class MeshGenerator : public SparkRefCount
        {
        public:
            MeshGenerator(void);
            virtual ~MeshGenerator(void);

        public:
            static spark::mesh::ISparkMesh* createPyramidMesh();
            static spark::mesh::ISparkMesh* createQuadMesh();
            static spark::mesh::ISparkMesh* createPlaneMesh();
            static spark::mesh::ISparkMesh* createSphereMesh(uint32_t recursionLevel = 0);
        };
    } // end namespace mesh
} // end namespace spark
#endif
