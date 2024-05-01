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
            spark::mesh::ISparkMesh* createPyramidMesh();
            spark::mesh::ISparkMesh* createQuadMesh();
            spark::mesh::ISparkMesh* createSphereMesh(uint32_t recursionLevel = 0);
            spark::mesh::ISparkMesh* createPlaneMesh();
        };
    } // end namespace mesh
} // end namespace spark
#endif
