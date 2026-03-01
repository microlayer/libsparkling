#include "AssetManager.hpp"
#include <future>
#include <drawing/Bitmap.hpp>

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
    spark::drawing::ISparkImage* AssetManager::loadBitmap(const std::string& uri)
    {
        auto data = loadBinary(uri);

        spark::drawing::Bitmap* bmp = NULL;

        std::vector<uc8_t> image;					// the raw pixels
        uint32_t width, height, fileSize, rawSize;	// width, height and size of the png

        int32_t error = lodepng::decode(image, width, height, data);

        std::string hash = mlstl::hash::MLHash::hashFNV1a(image);

        if (error == 0)
        {
            m_logger->info("Loading '%s' successful", uri.c_str());
            fileSize = data.size();
            rawSize = image.size();
            bmp = new drawing::Bitmap(&image[0], width, height, spark::drawing::E_RGBA8, hash);
        }
        else
        {
            m_logger->info("Loading '%s' not successful with code %i", uri.c_str(), error);
            fileSize = 0;
            rawSize = 0;
            bmp = NULL;
        }
        return bmp;
    }

    /**
    *
    */
    spark::game::ISparkTiledLayer* AssetManager::loadTiledLayer(const std::string& uri)
    {
        auto data = loadBinary(uri);

        spark::game::TiledLayer* tiledLayer = NULL;
        spark::drawing::ISparkImage* tilesetImage = NULL;

        tinyxml2::XMLDocument xmlDoc;
        tinyxml2::XMLError result = xmlDoc.Parse(
            reinterpret_cast<const char*>(data.data()),
            data.size()
        );
        if (result == tinyxml2::XML_SUCCESS)
        {
            m_logger->info("Loading '%s' successful - start analysing", uri.c_str());

            tinyxml2::XMLElement* mapNode = xmlDoc.FirstChildElement("map");
            const char* version = mapNode->Attribute("tiledversion");

            const char* supportedTiledVersion = "1.11.0";

            if (strcmp(version, supportedTiledVersion) != 0)
            {
                m_logger->warn("Tilset must use version %s and current version is %s", supportedTiledVersion, version);
            }

            const char* tileWidth = mapNode->Attribute("tilewidth");
            const char* tileHeight = mapNode->Attribute("tileheight");
            const char* gridWidth = mapNode->Attribute("width");
            const char* gridHeight = mapNode->Attribute("height");

            tinyxml2::XMLElement* tilesetNode = mapNode->FirstChildElement("tileset");

            // Grap tileset image data
            tinyxml2::XMLElement* tilesetImageNode = tilesetNode->FirstChildElement("image");
            const char* tilesetImageName = tilesetImageNode->Attribute("source");
            const char* tilesetImageWidth = tilesetImageNode->Attribute("width");
            const char* tilesetImageHeight = tilesetImageNode->Attribute("height");

            // Grap layer data
            tinyxml2::XMLElement* layerNode = mapNode->FirstChildElement("layer");
            const char* layerId = layerNode->Attribute("id");
            const char* layerName = layerNode->Attribute("name");
            const char* layerColumns = layerNode->Attribute("width");
            const char* layerRows = layerNode->Attribute("height");
            tinyxml2::XMLElement* layerDataNode = layerNode->FirstChildElement("data");
            const char* layerNodeData = layerDataNode->GetText();

            if (uri.rfind("file://", 0) == 0)
            {
                std::string tilesetImageNameAbsolutePathFile = "file://" + std::string(tilesetImageName);
                tilesetImage = loadBitmap(tilesetImageNameAbsolutePathFile);
            }

            if (uri.rfind("http://", 0) == 0 || uri.rfind("https://", 0) == 0)
            {
                size_t pos = uri.find_last_of('/');

                if (pos != std::string::npos)
                {
                    tilesetImage = loadBitmap(uri.substr(0, pos + 1) + tilesetImageName);
                }
            }

            // Parse CSV               
            std::string str(layerNodeData);
            str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
            std::vector<uint16_t> numbers;
            std::istringstream sstream(str);
            int number;
            char comma;
            while (sstream >> number)
            {
                numbers.push_back(number);
                sstream >> comma;
            }
            uint16_t* data = &numbers[0];

            tiledLayer = new spark::game::TiledLayer(tilesetImage, atoi(layerColumns), atoi(layerRows), data, atoi(tileWidth), atoi(tileHeight), atoi(tilesetImageWidth), atoi(tilesetImageHeight), spark::game::E_LAYER_TYPE::ELT_ORTHOGONAL);
        }
        else
        {
            m_logger->error("Tilset file %s could not be found", uri.c_str());
        }
        return tiledLayer;
    }

    /**
    *
    */
    spark::geometry::mesh::ISparkMesh* AssetManager::loadMesh(const std::string& uri)
    {
        auto data = loadBinary(uri);
        spark::geometry::mesh::importer::WavefrontFileReader wavefrontImporter(data, uri);
        return wavefrontImporter.loadMesh();
    }

    /**
    *
    */
    spark::geometry::pointcloud::ISparkPointCloud* AssetManager::loadPointCloud(const std::string& uri)
    {
        auto data = loadBinary(uri);
        spark::geometry::pointcloud::importer::PlyFileReader plyImporter(data, uri);
        return plyImporter.loadPointCloud();
    }

    /**
    *
    */
    std::vector<uint8_t> AssetManager::loadBinary(const std::string& uri)
    {
        std::vector<uint8_t> data;

        if (uri.rfind("file://", 0) == 0)
        {
            std::string path = uri.substr(7);
            data = m_fileSystem->readBinary(path);
        }
        else if (uri.rfind("http://", 0) == 0 || uri.rfind("https://", 0) == 0)
        {
            m_httpClient->get(uri, [this, &data](std::vector<uc8_t> responseData)
                {
                    data = std::move(responseData);
                    m_logger->info("Received data from HTTP request, size: %i bytes", data.size());
                });
        }
        else
        {
            std::cerr << "Unbekanntes URI-Schema: " << uri << "\n";
        }
        return data;
    }
}
