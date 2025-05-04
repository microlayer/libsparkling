#ifndef __SPARK_LOG_DEFAULTLOGGER_HPP_INCLUDED__
#define __SPARK_LOG_DEFAULTLOGGER_HPP_INCLUDED__

#include "spark/SparkSetup.hpp"
#include "spark/SparkLibConfig.hpp"
#include "ISparkLogger.hpp"
#include <iostream>
#include <fstream>
#include "ISparkLogger.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS
#include "Windows.h"
#endif

namespace spark {
    namespace log {
        /**
        *
        */
        class DefaultLogger : public ISparkLogger
        {
        public:
            DefaultLogger();
            virtual ~DefaultLogger(void);

        public: // Logs messages to the console
            void error(const char* pMessage, ...);
            void warn(const char* pMessage, ...);
            void info(const char* pMessage, ...);
            void debug(const char* pMessage, ...);

        public: // Logs messages to the InfoLogFile - file can be found in the root path
            void infoLogFile(const char* pMessage, ...);
        };
    } // end namespace log
} // end namespace spark
#endif

