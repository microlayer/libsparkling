#ifndef __SPARK_GEOMETRY_POINTCLOUD_IMPORTER_PLYFILEREADER_HPP_INCLUDED__
#define __SPARK_GEOMETRY_POINTCLOUD_IMPORTER_PLYFILEREADER_HPP_INCLUDED__

#include <sstream>
#include "ISparkPointCloudImporter.hpp"
#include "ISparkPointCloud.hpp"
#include "../PointCloud.hpp"

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
    };
}
#endif
