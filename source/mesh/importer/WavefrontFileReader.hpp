#ifndef __SPARK_MESH_IMPORTER_WAVEFRONTFILEREADER_HPP_INCLUDED__
#define __SPARK_MESH_IMPORTER_WAVEFRONTFILEREADER_HPP_INCLUDED__

#include "ISparkMesh.hpp"
#include "ISparkMeshImporter.hpp"
#include "mesh/Mesh.hpp"
#include "ISparkTimer.hpp"
#include "timer/Timer.hpp"
#include "log/LogManager.hpp"
#include "ISparkLogger.hpp"
#include <sstream>
#include <fstream>

namespace spark {
    namespace mesh {
        namespace importer {
            /**
            *
            */
            struct IndexTriple
            {
                IndexTriple(uint32_t vertexIndex, uint32_t uvIndex, uint32_t normalIndex) :
                    m_vertexIndex(vertexIndex), m_uvIndex(uvIndex), m_normalIndex(normalIndex)
                {
                }

                uint32_t m_vertexIndex;
                uint32_t m_uvIndex;
                uint32_t m_normalIndex;
            };

            /**
            *
            */
            struct VertexData
            {
                uint32_t m_vertexIndex;
                uint32_t m_uvIndex;
                uint32_t m_normalIndex;
                bool m_contains;
            };

            /**
            *
            */
            class WavefrontFileReader : public ISparkMeshImporter
            {
            public:
                WavefrontFileReader(std::string rootPath);
                virtual ~WavefrontFileReader(void);

            public: // ISparkMeshImporter
                spark::mesh::ISparkMesh* loadMesh(std::string fileName);

            private:
                std::string m_rootPath;
                uint32_t m_polygonCount;
            };
        } // end namespace importer
    } // end namespace mesh
} // end namespace spark
#endif

