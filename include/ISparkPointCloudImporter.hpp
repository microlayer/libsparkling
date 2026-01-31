#ifndef __SPARK_GEOMETRY_POINTCLOUD_IMPORTER_IPARKPOINTCLOUDIMPORTER_HPP_INCLUDED__
#define __SPARK_GEOMETRY_POINTCLOUD_IMPORTER_IPARKPOINTCLOUDIMPORTER_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkPointCloud.hpp"

namespace spark::geometry::pointcloud::importer {
    /**
    *
    */
    class ISparkPointCloudImporter : public virtual spark::SparkRefCount
    {
    public:
        virtual spark::geometry::pointcloud::ISparkPointCloud* loadPointCloud(std::string fileName) = 0;
    };
}
#endif