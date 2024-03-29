#ifndef __SPARK_TIMER_TIMER_HPP_INCLUDED__
#define __SPARK_TIMER_TIMER_HPP_INCLUDED__

#include "ISparkTimer.hpp"
#include "Sparkling.hpp"
#include <ctime>

namespace spark {
    namespace timer {

        /**
        *
        */
        class Timer : public ISparkTimer
        {
        public:
            Timer(void);
            virtual ~Timer(void);

        public:
            uint32_t getTimestamp();
            SparkTime getDateTimeNow();

        public:	// Represents a stop watch
            void start();
            void stop();
            real32 getElapsedTime();

        private:
            uint32_t m_measurementTimeStart;
            uint32_t m_measurementTimeStop;
        };
    } // end namespace timer
} // end namespace spark
#endif

