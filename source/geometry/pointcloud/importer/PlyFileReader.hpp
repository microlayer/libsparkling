#ifndef __SPARK_GEOMETRY_POINTCLOUD_IMPORTER_PLYFILEREADER_HPP_INCLUDED__
#define __SPARK_GEOMETRY_POINTCLOUD_IMPORTER_PLYFILEREADER_HPP_INCLUDED__

#include "ISparkPointCloudImporter.hpp"
#include "ISparkPointCloud.hpp"
#include "../PointCloud.hpp"
#include "log/LogManager.hpp"
#include "ISparkLogger.hpp"
#include "timer/Timer.hpp"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cfloat>

#undef min
#undef max

namespace spark::geometry::pointcloud::importer {
    /**
    *
    */
    class PlyFileReader : public ISparkPointCloudImporter
    {
    public:
        PlyFileReader(std::string rootPath);
        ~PlyFileReader();
    public: // ISparkPointCloudImporter
        spark::geometry::pointcloud::ISparkPointCloud* loadPointCloud(std::string fileName);

    private:
        spark::drawing::Color IntensityToTurboColor(uint16_t intensity);
        spark::drawing::Color HeightToViridisColor(float z, float minZ, float maxZ);

    private:
        std::string m_rootPath;
    };
}
#endif
