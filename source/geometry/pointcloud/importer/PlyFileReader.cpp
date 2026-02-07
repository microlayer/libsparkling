#include "PlyFileReader.hpp"

namespace spark::geometry::pointcloud::importer {
    /**
    *
    */
    PlyFileReader::PlyFileReader(std::string rootPath) :
        m_rootPath(rootPath)
    {

    }

    /**
    *
    */
    PlyFileReader::~PlyFileReader()
    {

    }

    /**
    *
    */
    spark::geometry::pointcloud::ISparkPointCloud* PlyFileReader::loadPointCloud(std::string fileName)
    {
        spark::log::ISparkLogger* logger = log::LogManager::getLogger();
        timer::Timer timer;

        spark::geometry::pointcloud::PointCloud* pointCloud = new spark::geometry::pointcloud::PointCloud();

        timer.start();
        std::ifstream ifs((m_rootPath.append(fileName.c_str())).c_str(), std::ifstream::in);

        std::string line, key;
        int vertexCount = 0;
        int faceCount = 0;
        bool headerEnded = false;

        while (ifs.good() && !ifs.eof() && std::getline(ifs, line))
        {
            std::stringstream sbuffer(line);
            std::string key;
            sbuffer >> key;

            if (key == "element")
            {
                std::string type;
                sbuffer >> type;

                if (type == "vertex")
                {
                    sbuffer >> vertexCount;
                }
                else if (type == "face")
                {
                    sbuffer >> faceCount;
                }
            }

            if (key == "end_header")
            {
                headerEnded = true;
                break;
            }
        }

        // [1] Read ply file
        math::Vector3f minPos(FLT_MAX, FLT_MAX, FLT_MAX);
        math::Vector3f maxPos(-FLT_MAX, -FLT_MAX, -FLT_MAX);
        std::vector<math::Vector3f> positions;
        std::vector<uint16_t> intensities;
        math::Vector3f position;
        for (int i = 0; i < vertexCount; i++)
        {
            std::getline(ifs, line);
            std::stringstream sbuffer(line);


            uint16_t intensity;
            sbuffer >> position.m_x >> position.m_y >> position.m_z;
            sbuffer >> intensity;

            positions.push_back(position);
            intensities.push_back(intensity);

            // Build Bounding Box
            minPos.m_x = std::min(minPos.m_x, position.m_x);
            minPos.m_y = std::min(minPos.m_y, position.m_y);
            minPos.m_z = std::min(minPos.m_z, position.m_z);

            maxPos.m_x = std::max(maxPos.m_x, position.m_x);
            maxPos.m_y = std::max(maxPos.m_y, position.m_y);
            maxPos.m_z = std::max(maxPos.m_z, position.m_z);
        }

        timer.stop();
        logger->info("Loading Polygon File Format (ply) '%s' file in %f sec.", fileName.c_str(), timer.getElapsedTime());


        // [2] Post processing point data
        timer.start();

        // Calculate Center
        math::Vector3f center;
        center.m_x = (minPos.m_x + maxPos.m_x) * 0.5f;
        center.m_y = (minPos.m_y + maxPos.m_y) * 0.5f;
        center.m_z = (minPos.m_z + maxPos.m_z) * 0.5f;

        for (int i = 0; i < vertexCount; i++)
        {
            math::Vector3f position = positions[i];

            // Cennter to origin
            position.m_x -= center.m_x;
            position.m_y -= center.m_y;
            position.m_z -= center.m_z;

            // Calculate color
            uint16_t intensity = intensities[i];
            spark::drawing::Color color = IntensityToTurboColor(intensity);
            //spark::drawing::Color color = HeightToViridisColor(positions[i].m_z, minPos.m_z, maxPos.m_z);

            // Add Vertex
            spark::drawing::Vertex3 vertex;
            vertex.m_x = position.m_x;
            vertex.m_y = position.m_y;
            vertex.m_z = position.m_z;
            vertex.m_color = color;

            pointCloud->addVertex(vertex);
        }

        timer.stop();
        logger->info("Postprocessing done using turbo color map");
        logger->info("Postprocessing Polygon File Format (ply) '%s' point cloud done in in %f sec. (Point count: %i)", fileName.c_str(), timer.getElapsedTime(), vertexCount);

        return pointCloud;
    }

    /**
    *
    */
    spark::drawing::Color PlyFileReader::IntensityToTurboColor(uint16_t intensity)
    {
        constexpr float maxIntensity = 65535.0f;
        float t = static_cast<float>(intensity) / maxIntensity;

        // Clamp to [0,1]
        t = std::min(1.0f, std::max(0.0f, t));

        // Turbo-color map
        real32 r = std::min(1.0f, std::max(0.0f, 1.5f - 4.0f * std::abs(t - 0.5f)));
        real32 g = std::min(1.0f, std::max(0.0f, 1.5f - 4.0f * std::abs(t - 0.25f)));
        real32 b = std::min(1.0f, std::max(0.0f, 1.5f - 4.0f * std::abs(t - 0.75f)));

        spark::drawing::Color color(
            static_cast<uint8_t>(r * 255),
            static_cast<uint8_t>(g * 255),
            static_cast<uint8_t>(b * 255), 255
        );

        return color;
    }

    /**
    *
    */
    spark::drawing::Color PlyFileReader::HeightToViridisColor(float z, float minZ, float maxZ)
    {
        float t = (z - minZ) / (maxZ - minZ);
        // Clamp to [0,1]
        t = std::clamp(t, 0.0f, 1.0f);

        // Contrast
        t = std::pow(t, 3.0f);

        // Viridis Polynomial Approximation
        real32 r = 0.280268f + t * (0.23364f + t * (-1.20677f + t * (2.00036f - 0.91287f * t)));
        real32 g = 0.165368f + t * (1.07931f + t * (-1.57269f + t * (1.99214f - 0.80914f * t)));
        real32 b = 0.476546f + t * (1.48319f + t * (-3.13680f + t * (3.19544f - 1.12774f * t)));

        r = std::min(1.0f, std::max(0.0f, r));
        g = std::min(1.0f, std::max(0.0f, g));
        b = std::min(1.0f, std::max(0.0f, b));

        return spark::drawing::Color(
            static_cast<uint8_t>(r * 255.0f),
            static_cast<uint8_t>(g * 255.0f),
            static_cast<uint8_t>(b * 255.0f),
            255
        );
    }
}