#ifndef __SPARK_ASSET_ASSETMANAGER_HPP_INCLUDED__
#define __SPARK_ASSET_ASSETMANAGER_HPP_INCLUDED__

#include "ISparkAssetManager.hpp"
#include "ISparkLogger.hpp"
#include "ISparkFileSystem.hpp"
#include "ISparkHttpClient.hpp"

namespace spark::asset {
    /**
    *
    */
    class AssetManager : public spark::asset::ISparkAssetManager
    {
    public:
        AssetManager(
            spark::file::ISparkFileSystem* fileSystem,
            spark::network::ISparkHttpClient* httpClient,
            spark::log::ISparkLogger* logger);
        virtual ~AssetManager(void);

    public: // ISparkAssetManager
        spark::drawing::ISparkImage* loadBitmap(const std::string& fileName);
        spark::game::ISparkTiledLayer* loadTiledLayer(const std::string& fileName);
        spark::geometry::mesh::ISparkMesh* loadMesh(const std::string& fileName);
        spark::geometry::pointcloud::ISparkPointCloud* loadPointCloud(const std::string& fileName);
    private:
        spark::log::ISparkLogger* m_logger;
        spark::file::ISparkFileSystem* m_fileSystem;
        spark::network::ISparkHttpClient* m_httpClient;
    };
}
#endif