#include "FileSystem.hpp"

namespace spark {
    namespace file {
        /**
        *
        */
        FileSystem::FileSystem(spark::log::ISparkLogger* logger, std::string rootPath) : m_logger(logger), m_rootPath(rootPath)
        {

        }

        /**
        *
        */
        FileSystem::~FileSystem()
        {

        }

        /**
        *
        */
        spark::drawing::ISparkImage* FileSystem::loadBitmap(std::string fileName)
        {
            spark::drawing::Bitmap* bmp = NULL;
            std::string absolutePathFile = m_rootPath + fileName;

            std::vector<uc8_t> png;						// the png file
            std::vector<uc8_t> image;					// the raw pixels
            uint32_t width, height, fileSize, rawSize;	// width, height and size of the png

            //load and decode
            lodepng::load_file(png, absolutePathFile);
            int32_t error = lodepng::decode(image, width, height, png);

            std::string hash = mlstl::hash::MLHash::hashFNV1a(image);

            if (error == 0)
            {
                m_logger->info("Loading '%s' successful", absolutePathFile.c_str());
                fileSize = png.size();
                rawSize = image.size();
                bmp = new drawing::Bitmap(&image[0], width, height, spark::drawing::E_RGBA8, hash);
            }
            else
            {
                m_logger->info("Loading '%s' not successful with code %i", absolutePathFile.c_str(), error);
                fileSize = 0;
                rawSize = 0;
                bmp = NULL;
            }
            return bmp;
        }

        /**
        *
        */
        spark::game::ISparkTiledLayer* FileSystem::loadTiledLayer(std::string fileName)
        {
            spark::game::TiledLayer* tiledLayer = NULL;
            spark::drawing::ISparkImage* tilesetImage = NULL;

            tinyxml2::XMLDocument xmlDoc;
            if (xmlDoc.LoadFile((m_rootPath + fileName).c_str()) == tinyxml2::XML_SUCCESS)
            {
                m_logger->info("Loading '%s' successful - start analysing", fileName.c_str());

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

                std::string tilesetImageNameAbsolutePathFile = m_rootPath + std::string(tilesetImageName);
                tilesetImage = loadBitmap(tilesetImageName);

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
                m_logger->error("Tilset file %s could not be found", fileName.c_str());
            }
            return tiledLayer;
        }

        /**
        *
        */
        void FileSystem::appendText(std::string filename, std::string text)
        {

        }

    } // end namespace file
} // end namespace spark

