#include "LogManager.hpp"

spark::log::ISparkLogger* spark::log::LogManager::m_logger = NULL;

namespace spark::log {

    /**
    *
    */
    ISparkLogger* LogManager::getLogger()
    {
        return m_logger;
    }

    /**
    *
    */
    void LogManager::setLogger(ISparkLogger* logger)
    {
        m_logger = logger;
    }
}
