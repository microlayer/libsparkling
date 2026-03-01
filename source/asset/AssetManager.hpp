#ifndef __SPARK_ASSET_ASSETMANAGER_HPP_INCLUDED__
#define __SPARK_ASSET_ASSETMANAGER_HPP_INCLUDED__

#include "ISparkAssetManager.hpp"
#include "ISparkLogger.hpp"
#include "ISparkFileSystem.hpp"
#include "ISparkHttpClient.hpp"
#include "geometry/pointcloud/importer/PlyFileReader.hpp"
#include "geometry/mesh/importer/WavefrontFileReader.hpp"
#include "mlstl/MLHash.hpp"
#include "../../lib/lodepng/lodepng.h"
#include "../../lib/tinyxml2/tinyxml2.h"

namespace spark::asset {
    /**
    * @brief AssetManager is a higher level component, which uses the FileSystem to load assets.
    * It can also use the network to load assets from HTTP or other sources.
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
        spark::drawing::ISparkImage* loadBitmap(const std::string& uri);
        spark::game::ISparkTiledLayer* loadTiledLayer(const std::string& uri);
        spark::geometry::mesh::ISparkMesh* loadMesh(const std::string& uri);
        spark::geometry::pointcloud::ISparkPointCloud* loadPointCloud(const std::string& uri);

    private:
        std::vector<uint8_t> loadBinary(const std::string& uri);

    private:
        spark::log::ISparkLogger* m_logger;
        spark::file::ISparkFileSystem* m_fileSystem;
        spark::network::ISparkHttpClient* m_httpClient;
    };
}
#endif