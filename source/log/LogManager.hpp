#ifndef __SPARK_LOG_LOGMANAGER_HPP_INCLUDED__
#define __SPARK_LOG_LOGMANAGER_HPP_INCLUDED__

#include "spark/SparkSetup.hpp"
#include "ISparkLogger.hpp"
#include "log/AndroidLogger.hpp"
#include "log/DefaultLogger.hpp"

namespace spark::log {
    /**
    *
    */
    class LogManager
    {
    public:
        static ISparkLogger* getLogger();
        static void setLogger(ISparkLogger* logger);

    private:
        static ISparkLogger* m_logger;
    };
}
#endif

