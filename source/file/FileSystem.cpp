#include "FileSystem.hpp"
#include "game/TiledLayer.hpp"

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

            if (error == 0)
            {
                m_logger->info("Loading '%s' successful", fileName.c_str());
                fileSize = png.size();
                rawSize = image.size();
                bmp = new drawing::Bitmap(&image[0], width, height, spark::drawing::E_RGBA8);
            }
            else
            {
                m_logger->info("Loading '%s' not successful with code %i", fileName.c_str(), error);
                fileSize = 0;
                rawSize = 0;
                bmp = NULL;
            }
            return bmp;
        }

        /**
        *
        */
        spark::game::TiledLayer* FileSystem::loadTiledLayer(std::string fileName)
        {
            spark::drawing::ISparkImage* tilesetImage = NULL;

            std::string absolutePathFile = m_rootPath + fileName;
            tinyxml2::XMLDocument xmlDoc;
            if (xmlDoc.LoadFile(absolutePathFile.c_str()) == tinyxml2::XML_SUCCESS)
            {
                m_logger->info("Loading '%s' successful", fileName.c_str());

                tinyxml2::XMLElement* mapNode = xmlDoc.FirstChildElement("map");
                const char* version = mapNode->Attribute("version");

                tinyxml2::XMLElement* tilesetNode = mapNode->FirstChildElement("tileset");
                const char* name = tilesetNode->Attribute("name");

                tinyxml2::XMLElement* tilesetImageNode = tilesetNode->FirstChildElement("image");
                const char* tilesetImageName = tilesetImageNode->Attribute("source");
                const char* tilesetImageWidth = tilesetImageNode->Attribute("width");
                const char* tilesetImageHeight = tilesetImageNode->Attribute("height");

                std::string tilesetImageNameAbsolutePathFile = m_rootPath + std::string(tilesetImageName);

                tilesetImage = loadBitmap(tilesetImageName);
            }

            uc8_t* data = NULL;
            spark::game::TiledLayer* tiledLayer = NULL;
            tiledLayer = new spark::game::TiledLayer(tilesetImage, 4, 4, NULL, 32, 32, 256, 256, spark::game::TiledLayer::ELT_ORTHOGONAL);
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

