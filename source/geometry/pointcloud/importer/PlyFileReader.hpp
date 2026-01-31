#ifndef __SPARK_GEOMETRY_POINTCLOUD_IMPORTER_PLYFILEREADER_HPP_INCLUDED__
#define __SPARK_GEOMETRY_POINTCLOUD_IMPORTER_PLYFILEREADER_HPP_INCLUDED__

#include "ISparkPointCloudImporter.hpp"
#include <sstream>
#include <ISparkPointCloud.hpp>

namespace spark::geometry::pointcloud::importer {
    /**
    *
    */
    class PlyFileReader : public ISparkPointCloudImporter
    {
    public:
        PlyFileReader();
        ~PlyFileReader();
    public: // ISparkPointCloudImporter
        spark::geometry::pointcloud::ISparkPointCloud* loadPointCloud(std::string fileName);
    };
}
#endif
