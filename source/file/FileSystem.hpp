#ifndef __SPARK_FILE_FILESYSTEM_HPP_INCLUDED__
#define __SPARK_FILE_FILESYSTEM_HPP_INCLUDED__

#include "log/LogManager.hpp"
#include "ISparkFileSystem.hpp"
#include <vector>
#include <sstream>
#include "drawing/Bitmap.hpp"
#include "game/TiledLayer.hpp"
#include "ISparkImage.hpp"
#include "mlstl/MLHash.hpp"
#include "../../lib/lodepng/lodepng.h"
#include "../../lib/tinyxml2/tinyxml2.h"

namespace spark {
    namespace file {

        class FileSystem : public file::ISparkFileSystem
        {
        public:
            FileSystem(spark::log::ISparkLogger* logger, std::string rootPath);
            virtual ~FileSystem(void);

        public: // ISparkFileSystem
            spark::drawing::ISparkImage* loadBitmap(std::string fileName);
            spark::game::TiledLayer* loadTiledLayer(std::string fileName);
            //spark::mesh::ISparkMesh* loadMesh(std::string fileName); 			
            //spark::font::ISparkFont* loadBitmapFont(std::string fileName);
            void appendText(std::string filename, std::string text);

        private:
            spark::log::ISparkLogger* m_logger;
            std::string m_rootPath;
        };
    } // end namespace file
} // end namespace spark
#endif
