#ifndef __SPARK_ASSET_ISPARKASSETMANAGER_HPP_INCLUDED__
#define __SPARK_ASSET_ISPARKASSETMANAGER_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkImage.hpp"
#include "game/TiledLayer.hpp"
#include "ISparkPointCloud.hpp"

namespace spark::asset {
    /**
    *
    */
    class ISparkAssetManager : public virtual spark::SparkRefCount
    {
    public:
        virtual spark::drawing::ISparkImage* loadBitmap(const std::string& fileName) = 0;
        virtual spark::game::ISparkTiledLayer* loadTiledLayer(const std::string& fileName) = 0;
        virtual spark::geometry::mesh::ISparkMesh* loadMesh(const std::string& fileName) = 0;
        virtual spark::geometry::pointcloud::ISparkPointCloud* loadPointCloud(const std::string& fileName) = 0;
    };
}
#endif