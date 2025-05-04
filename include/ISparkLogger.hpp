#ifndef __SPARK_LOG_ISPARKLOGGER_HPP_INCLUDED__
#define __SPARK_LOG_ISPARKLOGGER_HPP_INCLUDED__

#include "spark/SparkTypes.hpp"
#include "SparkRefCount.hpp"

namespace spark {
	namespace log {
		/**
		*
		*/
		class ISparkLogger : public virtual spark::SparkRefCount
		{
		public: // Logs messages to the console
			virtual void error(const char* pMessage, ...) = 0;
			virtual void warn(const char* pMessage, ...) = 0;
			virtual void info(const char* pMessage, ...) = 0;
			virtual void debug(const char* pMessage, ...) = 0;

		public: // Logs messages to the InfoLogFile - file can be found in the root path
			virtual void infoLogFile(const char* pMessage, ...) = 0;
		};
	} // end namespace log
} // end namespace spark
#endif