#include "FileSystem.hpp"
#include <thread>

namespace spark::file {
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
    bool FileSystem::exists(const std::string& fileName)
    {
        std::ifstream file(m_rootPath + fileName);
        return file.good();
    }

    /**
    *
    */
    void FileSystem::readBinaryAsync(const std::string& fileName, std::function<void(std::vector<uint8_t>)> callback)
    {
        std::thread([fileName, callback, this] {
            std::vector<uint8_t> data = readBinary(fileName);
            callback(data);
            }).detach();
    }

    /**
    *
    */
    std::vector<uint8_t> FileSystem::readBinary(const std::string& fileName)
    {
        std::string absolutePathFile = m_rootPath + fileName;
        std::ifstream file(absolutePathFile, std::ios::binary | std::ios::ate);
        if (!file)
        {
            m_logger->error("File %s could not be found", fileName.c_str());
            return std::vector<uint8_t>();
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        std::vector<uint8_t> buffer(static_cast<size_t>(size));
        file.read(reinterpret_cast<char*>(buffer.data()), size);
        return buffer;
    }

    /**
    *
    */
    void FileSystem::writeBinary(const std::string& fileName, const std::vector<uint8_t>& data)
    {
        std::ofstream file(fileName, std::ios::binary);
        if (!file)
        {
            m_logger->error("File %s could not be found", fileName.c_str());
            return;
        }

        if (!file.write(reinterpret_cast<const char*>(data.data()), data.size()))
        {
            m_logger->error("Failed to write file %s", fileName.c_str());
            return;
        }
    }
}

