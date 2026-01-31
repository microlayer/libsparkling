#ifndef __SPARK_FILE_ISPARKFILESYSTEM_HPP_INCLUDED__
#define __SPARK_FILE_ISPARKFILESYSTEM_HPP_INCLUDED__

#include "ISparkImage.hpp"
#include "game/TiledLayer.hpp"

namespace spark::file {
    /**
    *
    */
    class ISparkFileSystem : public virtual spark::SparkRefCount
    {
    public:
        virtual spark::drawing::ISparkImage* loadBitmap(const std::string& fileName) = 0;
        virtual spark::game::ISparkTiledLayer* loadTiledLayer(const std::string& fileName) = 0;
        virtual spark::geometry::mesh::ISparkMesh* loadMesh(const std::string& fileName) = 0;
        //virtual spark::font::ISparkFont* loadBitmapFont(const std::string& fileName) = 0;
        virtual void appendText(std::string filename, std::string text) = 0;
    };
}
#endif