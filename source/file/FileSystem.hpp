#ifndef __SPARK_FILE_FILESYSTEM_HPP_INCLUDED__
#define __SPARK_FILE_FILESYSTEM_HPP_INCLUDED__

#include "log/LogManager.hpp"
#include "ISparkFileSystem.hpp"
#include <vector>
#include <sstream>
#include "drawing/Bitmap.hpp"
#include "game/TiledLayer.hpp"
#include "ISparkImage.hpp"
#include "ISparkMeshImporter.hpp"
#include "geometry/mesh/importer/WavefrontFileReader.hpp" 
#include "geometry/pointcloud/importer/PlyFileReader.hpp"
#include "mlstl/MLHash.hpp"
#include "../../lib/lodepng/lodepng.h"
#include "../../lib/tinyxml2/tinyxml2.h"

namespace spark::file {
    /**
    *
    */
    class FileSystem : public file::ISparkFileSystem
    {
    public:
        FileSystem(spark::log::ISparkLogger* logger, std::string rootPath);
        virtual ~FileSystem(void);

    public: // ISparkFileSystem       
        bool exists(const std::string& fileName);
        void readBinaryAsync(const std::string& fileName, std::function<void(std::vector<uint8_t>)> callback);
        std::vector<uint8_t> readBinary(const std::string& fileName);
        void writeBinary(const std::string& fileName, const std::vector<uint8_t>& data);

    private:
        spark::log::ISparkLogger* m_logger;
        std::string m_rootPath;
    };
}
#endif
