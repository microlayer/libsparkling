#ifndef __SPARK_FILE_ISPARKFILESYSTEM_HPP_INCLUDED__
#define __SPARK_FILE_ISPARKFILESYSTEM_HPP_INCLUDED__

#include "ISparkImage.hpp"
#include "game/TiledLayer.hpp"
#include "ISparkPointCloud.hpp"
#include <functional>

namespace spark::file {
    /**
    *
    */
    class ISparkFileSystem : public virtual spark::SparkRefCount
    {
    public:       
        virtual bool exists(const std::string& fileName) = 0;
        virtual void readBinaryAsync(const std::string& fileName, std::function<void(std::vector<uint8_t>)> callback) = 0;
        virtual std::vector<uint8_t> readBinary(const std::string& fileName) = 0;
        virtual void writeBinary(const std::string& fileName, const std::vector<uint8_t>& data) = 0;
    };
}
#endif