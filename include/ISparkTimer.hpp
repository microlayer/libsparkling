#ifndef __SPARK_TIMER_ISPARKTIMER_HPP_INCLUDED__
#define __SPARK_TIMER_ISPARKTIMER_HPP_INCLUDED__

#include "spark/SparkTypes.hpp"
#include "SparkRefCount.hpp"

namespace spark {
    namespace timer {
        /**
        *
        */
        struct SparkTime
        {
            uint32_t Year;
            uint32_t Month;
            uint32_t DayOfWeek;
            uint32_t Hour;
            uint32_t Minute;
            uint32_t Second;
        };

        /**
        *
        */
        class ISparkTimer : public virtual SparkRefCount
        {
        public:
            virtual uint32_t getTimestamp() = 0;
            virtual SparkTime getDateTimeNow() = 0;

        public: // Represents a stop watch
            virtual void start() = 0;
            virtual void stop() = 0;
            virtual real32 getElapsedTime() = 0;
        };
    } // end namespace timer
} // end namespace spark
#endif