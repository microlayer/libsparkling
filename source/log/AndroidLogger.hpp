#ifndef __SPARK_LOG_ANDROIDLOGGER_HPP_INCLUDED__
#define __SPARK_LOG_ANDROIDLOGGER_HPP_INCLUDED__

#include "spark/SparkSetup.hpp"
#include "spark/SparkTypes.hpp"
#include "ISparkLogger.hpp"

#if SPARK_PLATFORM == SPARK_PLATFORM_ANDROID
#include <android/log.h>
#include <stdarg.h>
#include <stdio.h>

namespace spark {
    namespace log {
        /**
        *
        */
        class AndroidLogger : public ISparkLogger
        {
        public:
            AndroidLogger();
            virtual ~AndroidLogger(void);

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

#ifndef NDEBUG
#define microlayer_Log_debug(...) microlayer::Log::debug(__VA_ARGS__)
#else
#define microlayer_Log_debug(...)
#endif // NDEBUG
#endif // __SPARK_LOG_LOGANDROID_HPP_INCLUDED__
#endif // SPARK_PLATFORM_ANDROID 