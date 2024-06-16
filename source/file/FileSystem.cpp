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
            //uint32_t width, height, fileSize, rawSize;	// width, height and size of the png

            //load and decode
            //lodepng::load_file(png, absolutePathFile);
            //int32_t error = lodepng::decode(image, width, height, png);            

            //if (error == 0)
            //{
            //    m_logger->info("Loading '%s' successful", fileName.c_str());
            //    fileSize = png.size();
            //    rawSize = image.size();
            //    bmp = new drawing::Bitmap(&image[0], width, height, spark::drawing::E_RGBA8);
            //}
            //else
            //{
            //    m_logger->info("Loading '%s' not successful with code %i", fileName.c_str(), error);
            //    fileSize = 0;
            //    rawSize = 0;
            //    bmp = NULL;
            //}
            return bmp;
        }

        /**
        *
        */
        void FileSystem::appendText(std::string filename, std::string text)
        {

        }

    } // end namespace file
} // end namespace spark

