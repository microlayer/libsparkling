#include "WavefrontFileReader.hpp"

namespace spark::geometry::mesh::importer {

    /**
    *
    */
    WavefrontFileReader::WavefrontFileReader(std::vector<uint8_t> data, std::string fileName) :
        m_data(data),
        m_fileName(fileName),
        m_polygonCount(0)
    {
    }

    /**
    *
    */
    WavefrontFileReader::~WavefrontFileReader(void)
    {
    }

    /**
    * '#'  comments can be ignored
    * 'v'  vertices positions
    * 'vt' vertices texcoords
    * 'vn' vertices normals
    * 'f'  faces, 3 values that contain 3 values which are separated by / and <space>
    */
    spark::geometry::mesh::ISparkMesh* WavefrontFileReader::loadMesh()
    {
        spark::log::ISparkLogger* logger = log::LogManager::getLogger();

        timer::Timer timer;

        mesh::Mesh* mesh = new mesh::Mesh();

        std::vector<math::Vector3f>	positions;
        std::vector<math::Vector2f> textureCoords;
        std::vector<math::Vector3f> normals;

        std::vector<IndexTriple> indexTriples;

        // [1] Reading the obj file and parsing data
        timer.start();

        // Copy bytes into std::string
        std::string content(m_data.begin(), m_data.end());
        std::istringstream iss(content);

        std::string line, key;

        while (std::getline(iss, line))
        {
            std::stringstream sbuffer(line);
            sbuffer >> key;

            if (key == "v")
            {
                math::Vector3f position;
                sbuffer >> position.m_x >> position.m_y >> position.m_z;
                positions.push_back(position);
            }

            if (key == "vt")
            {
                math::Vector2f uv;
                sbuffer >> uv.m_x >> uv.m_y;
                textureCoords.push_back(uv);
            }

            if (key == "vn")
            {
                math::Vector3f normal;
                sbuffer >> normal.m_x >> normal.m_y >> normal.m_z;
                normals.push_back(normal);
            }

            // Parse faces the following patterns can occure:
            // a.) v
            // b.) v/vt
            // c.) v//vn
            // d.) v/vt/vn
            if (key == "f")
            {
                uint32_t a, b, c;
                uint32_t faceNodeCount = 0;	// holds the count of nodes the polygon consists of - usually 3
                while (!sbuffer.eof())
                {
                    a = b = c = 0;
                    sbuffer >> a; a--;

                    if (sbuffer.get() == '/')
                    {
                        if (sbuffer.peek() != '/')
                        {
                            sbuffer >> b;
                            b--;
                        }
                        if (sbuffer.get() == '/')
                        {
                            sbuffer >> c;
                            c--;
                        }
                    }
                    faceNodeCount++;
                    indexTriples.push_back(IndexTriple(a, b, c));
                    mesh->addIndex(a);
                }
                m_polygonCount++;
            }
        }
        timer.stop();
        logger->info("Loading wavefront '%s' file in %f sec.", m_fileName.c_str(), timer.getElapsedTime());


        // [2] Post processing mesh data
        timer.start();
        std::vector<VertexData> vertexDataList;
        vertexDataList.resize(positions.size());	// create a vector with the same size as vector positions

        for (uint32_t i = 0; i < indexTriples.size(); i++)
        {
            uint32_t vertexIndex = indexTriples[i].m_vertexIndex;
            uint32_t normalIndex = indexTriples[i].m_normalIndex;
            uint32_t uvIndex = indexTriples[i].m_uvIndex;

            VertexData vd = vertexDataList[vertexIndex];

            if (!vd.m_contains)
            {
                vd.m_vertexIndex = vertexIndex;
                vd.m_normalIndex = normalIndex;
                vd.m_uvIndex = uvIndex;
                vd.m_contains = true;

                vertexDataList[vertexIndex] = vd;
            }
        }

        for (uint32_t i = 0; i < vertexDataList.size(); i++)
        {
            VertexData vd = vertexDataList[i];

            auto uv = textureCoords.empty()
                ? math::Vector2f{ 0.0f, 0.0f }
            : textureCoords[vd.m_uvIndex];

            auto n = normals.empty()
                ? math::Vector3f{ 0.0f, 0.0f, 0.0f }
            : normals[vd.m_normalIndex];

            mesh->addVertex(drawing::Vertex3(positions[i].m_x, positions[i].m_y, positions[i].m_z, drawing::Color(128, 128, 128, 255), n, uv));
        }

        timer.stop();
        logger->info("Postprocessing wavefront '%s' mesh done in in %f sec. (Polygon count: %i)", m_fileName.c_str(), timer.getElapsedTime(), m_polygonCount);

        return mesh;
    }
}
