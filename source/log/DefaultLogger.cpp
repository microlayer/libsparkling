#include "DefaultLogger.hpp"

namespace spark {
    namespace log {
        /**
        *
        */
        DefaultLogger::DefaultLogger()
        {
        }

        /**
        *
        */
        DefaultLogger::~DefaultLogger(void)
        {
        }

        /**
        * %i: uint32_t / %f: real32
        */
        void DefaultLogger::error(const char* pMessage, ...)
        {
#if SPARK_TRACE == 0x1	
            char str[512];

            va_list args;
            va_start(args, pMessage);
            vsprintf(str, pMessage, args);
            va_end(args);

#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS
            OutputDebugString(str);
            OutputDebugString("\n");
#endif

#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
            printf("%s\n", str);
#endif
#endif
        }

        /**
        * %i: uint32_t / %f: real32
        */
        void DefaultLogger::warn(const char* pMessage, ...)
        {
#if SPARK_TRACE == 0x1	
            char str[512];

            va_list args;
            va_start(args, pMessage);
            vsprintf(str, pMessage, args);
            va_end(args);

#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS
            OutputDebugString(str);
            OutputDebugString("\n");
#endif

#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
            printf("%s\n", str);
#endif
#endif
        }

        /**
        * %i: uint32_t / %f: real32
        */
        void DefaultLogger::info(const char* pMessage, ...)
        {
#if SPARK_TRACE == 0x1	
            char str[512];

            va_list args;
            va_start(args, pMessage);
            vsprintf(str, pMessage, args);
            va_end(args);

#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS
            OutputDebugString(str);
            OutputDebugString("\n");
#endif

#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
            printf("%s\n", str);
#endif
#endif
        }

        /**
        * %i: uint32_t / %f: real32
        */
        void DefaultLogger::debug(const char* pMessage, ...)
        {
#if SPARK_TRACE == 0x1	
            char str[512];

            va_list args;
            va_start(args, pMessage);
            vsprintf(str, pMessage, args);
            va_end(args);

#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS
            OutputDebugString(str);
            OutputDebugString("\n");
#endif

#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
            printf("%s\n", str);
#endif
#endif
        }

        /**
        * %i: uint32_t / %f: real32
        */
        void DefaultLogger::infoLogFile(const char* pMessage, ...)
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

    } // end namespace log
} // end namespace spark

