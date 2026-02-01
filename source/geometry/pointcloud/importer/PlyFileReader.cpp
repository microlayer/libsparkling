#include "PlyFileReader.hpp"

namespace spark::geometry::pointcloud::importer {
    /**
    *
    */
    PlyFileReader::PlyFileReader(std::string rootPath)
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
        spark::geometry::pointcloud::PointCloud* pointCloud = new spark::geometry::pointcloud::PointCloud();
        pointCloud->addVertex(spark::drawing::Vertex3(1.0, 1.0, 0.0, spark::drawing::Color(255, 0, 0, 128)));
        return pointCloud;
    }
}