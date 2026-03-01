#ifndef __SPARK_GEOMETRY_POINTCLOUD_IMPORTER_PLYFILEREADER_HPP_INCLUDED__
#define __SPARK_GEOMETRY_POINTCLOUD_IMPORTER_PLYFILEREADER_HPP_INCLUDED__

#include "ISparkPointCloudImporter.hpp"
#include "ISparkPointCloud.hpp"
#include "../PointCloud.hpp"
#include "log/LogManager.hpp"
#include "ISparkLogger.hpp"
#include "timer/Timer.hpp"
#include <string>
#include <sstream>

#undef min
#undef max

namespace spark::geometry::pointcloud::importer {
    /**
    *
    */
    class PlyFileReader : public ISparkPointCloudImporter
    {
    public:
        PlyFileReader(std::vector<uint8_t> data, std::string fileName);
        ~PlyFileReader();

    public: // ISparkPointCloudImporter
        spark::geometry::pointcloud::ISparkPointCloud* loadPointCloud();

    private:
        spark::drawing::Color IntensityToTurboColor(uint16_t intensity);
        spark::drawing::Color HeightToViridisColor(float z, float minZ, float maxZ);

    private:
        std::string m_fileName;
        std::vector<uint8_t> m_data;
    };
}
#endif
