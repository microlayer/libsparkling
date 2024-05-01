#include "MeshGenerator.hpp"

namespace spark {
    namespace mesh {

        /**
        *
        */
        MeshGenerator::MeshGenerator(void)
        {
        }

        /**
        *
        */
        MeshGenerator::~MeshGenerator(void)
        {
        }

        /**
        * Creates a pyramid mesh with 12 vertices 12 normals and 12 indices
        */
        spark::mesh::ISparkMesh* MeshGenerator::createPyramidMesh()
        {
            // [1] Cut into the middle of the pyramid width and height of the pyramid is 2:
            //	  /|\
			//	 / | \
			//  /  |2 \
			// /ß  |  ß\
			// ----------
            //  1  |   1
            //
            // ß = atan(2/1) = 63,4° 
            //
            // [2] Calculating the normal angle ßN
            // ßN = 180°-90°-63,4° = 26,6°
            // 
            // [3] Calculating the normal vector for the angle ßN
            // X respectively Z	= Math.cos(angle) = 0.89 
            // Y				= Math.sin(angle) = 0.45
            // 
            // [4] Result: 4 different normals
            // Front: (0, sin, cos)
            // Right: (cos, sin, 0)
            // Back:  (0, sin, -cos)
            // Left:  (-cos, sin, 0)


            real32 cos = 0.89f;
            real32 sin = 0.45f;

            spark::mesh::Mesh* m = new spark::mesh::Mesh();

            // Front
            m->addVertex(spark::drawing::Vertex3(0.0f, 1.0f, 0.0f, spark::drawing::Color(255, 0, 0, 255), math::Vector3f(0, sin, cos), math::Vector2f(0.5f, 0.0f)));
            m->addVertex(spark::drawing::Vertex3(-1.0f, -1.0f, 1.0f, spark::drawing::Color(0, 255, 0, 255), math::Vector3f(0, sin, cos), math::Vector2f(0.0f, 1.0f)));
            m->addVertex(spark::drawing::Vertex3(1.0f, -1.0f, 1.0f, spark::drawing::Color(0, 0, 255, 255), math::Vector3f(0, sin, cos), math::Vector2f(1.0f, 1.0f)));

            // Right
            m->addVertex(spark::drawing::Vertex3(0.0f, 1.0f, 0.0f, spark::drawing::Color(255, 0, 0, 255), math::Vector3f(cos, sin, 0), math::Vector2f(0.5f, 0.0f)));
            m->addVertex(spark::drawing::Vertex3(1.0f, -1.0f, 1.0f, spark::drawing::Color(0, 0, 255, 255), math::Vector3f(cos, sin, 0), math::Vector2f(0.0f, 1.0f)));
            m->addVertex(spark::drawing::Vertex3(1.0f, -1.0f, -1.0f, spark::drawing::Color(0, 0, 255, 255), math::Vector3f(cos, sin, 0), math::Vector2f(1.0f, 1.0f)));

            // Back
            m->addVertex(spark::drawing::Vertex3(0.0f, 1.0f, 0.0f, spark::drawing::Color(255, 0, 0, 255), math::Vector3f(0, sin, -cos), math::Vector2f(0.5f, 0.0f)));
            m->addVertex(spark::drawing::Vertex3(1.0f, -1.0f, -1.0f, spark::drawing::Color(0, 255, 0, 255), math::Vector3f(0, sin, -cos), math::Vector2f(0.0f, 1.0f)));
            m->addVertex(spark::drawing::Vertex3(-1.0f, -1.0f, -1.0f, spark::drawing::Color(0, 0, 255, 255), math::Vector3f(0, sin, -cos), math::Vector2f(1.0f, 1.0f)));

            // Left
            m->addVertex(spark::drawing::Vertex3(0.0f, 1.0f, 0.0f, spark::drawing::Color(255, 0, 0, 255), math::Vector3f(-cos, sin, 0), math::Vector2f(0.5f, 0.0f)));
            m->addVertex(spark::drawing::Vertex3(-1.0f, -1.0f, 1.0f, spark::drawing::Color(0, 255, 0, 255), math::Vector3f(-cos, sin, 0), math::Vector2f(0.0f, 1.0f)));
            m->addVertex(spark::drawing::Vertex3(-1.0f, -1.0f, -1.0f, spark::drawing::Color(0, 0, 255, 255), math::Vector3f(-cos, sin, 0), math::Vector2f(1.0f, 1.0f)));

            uint16_t pyramidVertexFaces[] = {
                0, 1, 2,	// Defines Front Face
                3, 4, 5,	// Defines Right Face
                6, 7, 8,	// Defines Back Face
                9, 11, 10   // Defines Left Face
            };

            for (uint16_t i = 0; i < 12; i++)
            {
                m->addIndex(pyramidVertexFaces[i]);
            }
            return m;
        }

        /**
        *  Creates a cube mesh with 24 vertices 24 normals and 36 indices
        */
        spark::mesh::ISparkMesh* MeshGenerator::createQuadMesh()
        {
            //    v6----- v5
            //   /|      /|
            //  v1------v0|
            //  | |     | |
            //  | |v7---|-|v4
            //  |/      |/
            //  v2------v3

            spark::mesh::Mesh* m = new spark::mesh::Mesh();

            m->addVertex(spark::drawing::Vertex3(1, 1, 1, spark::drawing::Color(0, 0, 255, 255), math::Vector3f(0, 0, 1), math::Vector2f(1.0f, 0.0f)));			//v0
            m->addVertex(spark::drawing::Vertex3(-1, 1, 1, spark::drawing::Color(0, 255, 0, 255), math::Vector3f(0, 0, 1), math::Vector2f(0.0f, 0.0f)));			//v1
            m->addVertex(spark::drawing::Vertex3(-1, -1, 1, spark::drawing::Color(0, 255, 255, 255), math::Vector3f(0, 0, 1), math::Vector2f(0.0f, 1.0f)));		//v2
            m->addVertex(spark::drawing::Vertex3(1, -1, 1, spark::drawing::Color(255, 0, 0, 255), math::Vector3f(0, 0, 1), math::Vector2f(1.0f, 1.0f)));			//v3

            m->addVertex(spark::drawing::Vertex3(1, 1, 1, spark::drawing::Color(255, 0, 255, 255), math::Vector3f(1, 0, 0), math::Vector2f(1.0f, 0.0f)));		//v0
            m->addVertex(spark::drawing::Vertex3(1, -1, 1, spark::drawing::Color(255, 255, 0, 255), math::Vector3f(1, 0, 0), math::Vector2f(0.0f, 0.0f)));		//v3
            m->addVertex(spark::drawing::Vertex3(1, -1, -1, spark::drawing::Color(255, 255, 255, 255), math::Vector3f(1, 0, 0), math::Vector2f(0.0f, 1.0f)));	//v4
            m->addVertex(spark::drawing::Vertex3(1, 1, -1, spark::drawing::Color(0, 0, 0, 255), math::Vector3f(1, 0, 0), math::Vector2f(1.0f, 1.0f)));			//v5

            m->addVertex(spark::drawing::Vertex3(1, 1, 1, spark::drawing::Color(255, 0, 255, 255), math::Vector3f(0, 1, 0), math::Vector2f(1.0f, 0.0f)));		//v0
            m->addVertex(spark::drawing::Vertex3(1, 1, -1, spark::drawing::Color(255, 255, 0, 255), math::Vector3f(0, 1, 0), math::Vector2f(0.0f, 0.0f)));		//v5
            m->addVertex(spark::drawing::Vertex3(-1, 1, -1, spark::drawing::Color(255, 255, 255, 255), math::Vector3f(0, 1, 0), math::Vector2f(0.0f, 1.0f)));	//v6
            m->addVertex(spark::drawing::Vertex3(-1, 1, 1, spark::drawing::Color(0, 0, 0, 255), math::Vector3f(0, 1, 0), math::Vector2f(1.0f, 1.0f)));			//v1


            m->addVertex(spark::drawing::Vertex3(-1, 1, 1, spark::drawing::Color(0, 0, 255, 255), math::Vector3f(-1, 0, 0), math::Vector2f(1.0f, 0.0f)));		//v1
            m->addVertex(spark::drawing::Vertex3(-1, 1, -1, spark::drawing::Color(0, 255, 0, 255), math::Vector3f(-1, 0, 0), math::Vector2f(0.0f, 0.0f)));		//v6
            m->addVertex(spark::drawing::Vertex3(-1, -1, -1, spark::drawing::Color(0, 255, 255, 255), math::Vector3f(-1, 0, 0), math::Vector2f(0.0f, 1.0f)));	//v7
            m->addVertex(spark::drawing::Vertex3(-1, -1, 1, spark::drawing::Color(255, 0, 0, 255), math::Vector3f(-1, 0, 0), math::Vector2f(1.0f, 1.0f)));		//v2

            m->addVertex(spark::drawing::Vertex3(-1, -1, -1, spark::drawing::Color(255, 0, 255, 255), math::Vector3f(0, -1, 0), math::Vector2f(1.0f, 0.0f)));	//v7
            m->addVertex(spark::drawing::Vertex3(1, -1, -1, spark::drawing::Color(255, 255, 0, 255), math::Vector3f(0, -1, 0), math::Vector2f(0.0f, 0.0f)));		//v4
            m->addVertex(spark::drawing::Vertex3(1, -1, 1, spark::drawing::Color(255, 255, 255, 255), math::Vector3f(0, -1, 0), math::Vector2f(0.0f, 1.0f)));	//v3
            m->addVertex(spark::drawing::Vertex3(-1, -1, 1, spark::drawing::Color(0, 0, 0, 255), math::Vector3f(0, -1, 0), math::Vector2f(1.0f, 1.0f)));			//v2

            m->addVertex(spark::drawing::Vertex3(1, -1, -1, spark::drawing::Color(255, 0, 255, 255), math::Vector3f(0, 0, -1), math::Vector2f(1.0f, 0.0f)));		//v4
            m->addVertex(spark::drawing::Vertex3(-1, -1, -1, spark::drawing::Color(255, 255, 0, 255), math::Vector3f(0, 0, -1), math::Vector2f(0.0f, 0.0f)));	//v7
            m->addVertex(spark::drawing::Vertex3(-1, 1, -1, spark::drawing::Color(255, 255, 255, 255), math::Vector3f(0, 0, -1), math::Vector2f(0.0f, 1.0f)));	//v6
            m->addVertex(spark::drawing::Vertex3(1, 1, -1, spark::drawing::Color(0, 0, 0, 255), math::Vector3f(0, 0, -1), math::Vector2f(1.0f, 1.0f)));			//v5

            uint16_t quadVertexFaces[] =
            {
                0, 1, 2,	2, 3, 0,		// front
                4, 5, 6,	6, 7, 4,		// right
                8, 9,10,	10,11, 8,		// top
                12,13,14,	14,15,12,		// left
                16,17,18,	18,19,16,		// bottom
                20,21,22,	22,23,20		// back
            };

            for (uint16_t i = 0; i < 36; i++)
            {
                m->addIndex(quadVertexFaces[i]);
            }
            return m;
        }

        /**
        * Creates a sphere mesh. vertices normals and indices depends on the specified recursion level
        */
        spark::mesh::ISparkMesh* MeshGenerator::createSphereMesh(uint32_t recursionLevel)
        {
            return NULL;
        }

        /**
        * Creates a plane mesh with 4 vertices 4 normals and 6 indices
        */
        spark::mesh::ISparkMesh* MeshGenerator::createPlaneMesh()
        {
            spark::mesh::Mesh* m = new spark::mesh::Mesh();

            m->addVertex(spark::drawing::Vertex3(-1.0f, 0.0f, -1.0f, spark::drawing::Color(255, 0, 0, 255), math::Vector3f(0.0f, -1.0f, 0.0f), math::Vector2f(0.0f, 0.0f)));
            m->addVertex(spark::drawing::Vertex3(1.0f, 0.0f, -1.0f, spark::drawing::Color(0, 255, 0, 255), math::Vector3f(0.0f, -1.0f, 0.0f), math::Vector2f(1.0f, 0.0f)));
            m->addVertex(spark::drawing::Vertex3(-1.0f, 0.0f, 1.0f, spark::drawing::Color(0, 0, 255, 255), math::Vector3f(0.0f, -1.0f, 0.0f), math::Vector2f(0.0f, 1.0f)));
            m->addVertex(spark::drawing::Vertex3(1.0f, 0.0f, 1.0f, spark::drawing::Color(0, 255, 0, 255), math::Vector3f(0.0f, -1.0f, 0.0f), math::Vector2f(1.0f, 1.0f)));

            uint16_t planeVertexFaces[] = {
                2, 3, 1,  // 
                2, 1, 0,  // 
            };

            for (uint16_t i = 0; i < 6; i++)
            {
                m->addIndex(planeVertexFaces[i]);
            }
            return m;
        }

    } // end namespace mesh
} // end namespace spark