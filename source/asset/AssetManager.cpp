#include "AssetManager.hpp"

namespace spark::asset {
    /**
    *
    */
    AssetManager::AssetManager(
        spark::file::ISparkFileSystem* fileSystem,
        spark::network::ISparkHttpClient* httpClient,
        spark::log::ISparkLogger* logger) :
        m_fileSystem(fileSystem),
        m_httpClient(httpClient),
        m_logger(logger)
    {
    }

    /**
    *
    */
    AssetManager::~AssetManager(void)
    {
    }

    /**
    *
    */
    spark::drawing::ISparkImage* AssetManager::loadBitmap(const std::string& fileName)
    {

        return NULL;
    }

    /**
    *
    */
    spark::game::ISparkTiledLayer* AssetManager::loadTiledLayer(const std::string& fileName)
    {
        return NULL;
    }

    /**
    *
    */
    spark::geometry::mesh::ISparkMesh* AssetManager::loadMesh(const std::string& fileName)
    {
        return NULL;
    }

    /**
    *
    */
    spark::geometry::pointcloud::ISparkPointCloud* AssetManager::loadPointCloud(const std::string& fileName)
    {
        // Keep: device->getFileSystem() ; FileSystem ist technical infarstructure component.
        // Add:  device->getAssetManager() ; AssetManager is a higher level component, which uses the FileSystem to load assets. It can also use the network to load assets from HTTP or other sources. The AssetManager can also cache loaded assets to improve performance and reduce memory usage.

        // auto data = loadBinary(fileName);

        //std::vector<uint8_t> data;
        //uri.starts_with("file://")
        //if (isFile(uri))
        //{
        //    data = m_fileSystem->readBinary(fileName);
        //}
        //else if (isHttp(uri))
        //{
        //    auto response = m_httpClient->get(uri);

        //    if (!response || response->statusCode() != 200)
        //        return nullptr;

        //    data = response->body();
        //}

        //return m_plyLoader->load(data);
        return  NULL;
    }
}
