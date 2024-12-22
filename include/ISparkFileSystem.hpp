#ifndef __SPARK_FILE_ISPARKFILESYSTEM_HPP_INCLUDED__
#define __SPARK_FILE_ISPARKFILESYSTEM_HPP_INCLUDED__

#include "ISparkImage.hpp"
#include "game/TiledLayer.hpp"

namespace spark {
    namespace file {

        class ISparkFileSystem : public virtual spark::SparkRefCount
        {
        public:
            virtual spark::drawing::ISparkImage* loadBitmap(std::string fileName) = 0;
            virtual spark::game::TiledLayer* loadTiledLayer(std::string fileName) = 0;
            //virtual spark::mesh::ISparkMesh* loadMesh(std::string fileName) = 0;             
            //virtual spark::font::ISparkFont* loadBitmapFont(std::string fileName) = 0;
            virtual void appendText(std::string filename, std::string text) = 0;
        };
    } // end namespace file
} // end namespace spark
#endif