#include "spark/SparkSetup.hpp"
#include "log/AndroidLogger.hpp"

#if SPARK_PLATFORM == SPARK_PLATFORM_ANDROID

namespace spark::log {
    /**
    *
    */
    AndroidLogger::AndroidLogger()
    {
    }

    /**
    *
    */
    AndroidLogger::~AndroidLogger()
    {
    }

    /**
    * %i: uint32_t / %f: real32 / %s: string
    */
    void AndroidLogger::info(const char* pMessage, ...)
    {
#if SPARK_TRACE == 0x1		
        va_list lVarArgs;
        va_start(lVarArgs, pMessage);
        __android_log_vprint(ANDROID_LOG_INFO, "libsparkling", pMessage, lVarArgs);
        va_end(lVarArgs);
#endif
    }

    /**
    * %i: uint32_t / %f: real32 / %s: string
    */
    void AndroidLogger::error(const char* pMessage, ...)
    {
#if SPARK_TRACE == 0x1		
        va_list lVarArgs;
        va_start(lVarArgs, pMessage);
        __android_log_vprint(ANDROID_LOG_ERROR, "libsparkling", pMessage, lVarArgs);
        va_end(lVarArgs);
#endif
    }

    /**
    * %i: uint32_t / %f: real32 / %s: string
    */
    void AndroidLogger::warn(const char* pMessage, ...)
    {
#if SPARK_TRACE == 0x1	
        va_list lVarArgs;
        va_start(lVarArgs, pMessage);
        __android_log_vprint(ANDROID_LOG_WARN, "libsparkling", pMessage, lVarArgs);
        va_end(lVarArgs);
#endif	
    }

    /**
    * %i: uint32_t / %f: real32 / %s: string
    */
    void AndroidLogger::debug(const char* pMessage, ...)
    {
#if SPARK_TRACE == 0x1	
        va_list lVarArgs;
        va_start(lVarArgs, pMessage);
        __android_log_vprint(ANDROID_LOG_DEBUG, "libsparkling", pMessage, lVarArgs);
        va_end(lVarArgs);
#endif
    }

    /**
    * %i: uint32_t / %f: real32 / %s: string
    */
    void AndroidLogger::infoLogFile(const char* pMessage, ...)
    {
#if SPARK_TRACE == 0x1
#if SPARK_TRACE_TO_FILE == 0x1		
        char str[512];

        va_list args;
        va_start(args, pMessage);
        vsprintf(str, pMessage, args);
        va_end(args);

        //m_fileSystem->appendText(m_device->getRootPath().append("info.log"), str);
#endif
#endif
    }
}
#endif