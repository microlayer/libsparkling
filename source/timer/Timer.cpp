#include "spark/SparkSetup.hpp"
#include "timer/Timer.hpp"

#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS
#include <windows.h>
#include <thread>
#include <chrono>
#elif SPARK_PLATFORM == SPARK_PLATFORM_ANDROID
#include <time.h>
#include <thread>
#include <chrono>
#elif SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
#include <emscripten.h>
#endif

namespace spark::timer {
    /**
    *
    */
    Timer::Timer(void) :
        m_measurementTimeStart(0),
        m_measurementTimeStop(0)
    {
    }

    /**
    *
    */
    Timer::~Timer(void)
    {
    }

    /**
    * Returns the miliseconds part of current time - range from 1ms - 59999ms.
    * Usually used for frame independent animations.
    */
    uint32_t Timer::getTimestamp()
    {
        uint32_t timeNow = 0;

#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS
        std::clock_t c = std::clock();
        real32 sec = ((real32)c) / CLOCKS_PER_SEC;
        timeNow = uint32_t(sec * 1000);

#elif SPARK_PLATFORM == SPARK_PLATFORM_ANDROID || SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
        timespec val;
        // Use POSIX version
        clock_gettime(CLOCK_MONOTONIC, &val);
        timeNow = (uint32_t)(val.tv_sec * 1000) + (val.tv_nsec / 1000000);
#endif
        return timeNow;
    }

    /**
    *
    */
    SparkTime Timer::getDateTimeNow()
    {
        timer::SparkTime timeNow;

#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS
        SYSTEMTIME st;
        GetSystemTime(&st);

        timeNow.Year = st.wYear;
        timeNow.Month = st.wMonth;
        timeNow.DayOfWeek = st.wDayOfWeek;
        timeNow.Hour = st.wHour;
        timeNow.Minute = st.wMinute;
        timeNow.Second = st.wSecond;

#elif SPARK_PLATFORM == SPARK_PLATFORM_ANDROID
        time_t rawtime;
        tm* timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);

        timeNow.Year = timeinfo->tm_year;
        timeNow.Month = timeinfo->tm_mon;
        timeNow.DayOfWeek = timeinfo->tm_wday;
        timeNow.Hour = timeinfo->tm_hour;
        timeNow.Minute = timeinfo->tm_min;
        timeNow.Second = timeinfo->tm_sec;
#endif
        return timeNow;
    }

    /**
    *
    */
    void Timer::start()
    {
        m_measurementTimeStart = clock();
    }

    /**
    *
    */
    void Timer::stop()
    {
        m_measurementTimeStop = clock();
    }

    /**
    * Returns the elapsed time in seconds
    */
    real32 Timer::getElapsedTime()
    {
        return (m_measurementTimeStop / (1.0f * CLOCKS_PER_SEC)) - (m_measurementTimeStart / (1.0f * CLOCKS_PER_SEC));
    }

    /**
    *
    */
    void Timer::setTimeout(std::function<void()> function, uint32_t millisecond)
    {
        m_timeoutCallbackFunction = function;
#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL            
        emscripten_async_call(timeoutCallback, this, millisecond);
#else           
        std::thread([function, millisecond]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(millisecond));
            if (function) {
                function();
            }
            }).detach();
#endif
    }

    /**
    *
    */
    void Timer::timeoutCallback(void* arg)
    {
        spark::timer::Timer* instance = static_cast<spark::timer::Timer*>(arg);
        std::function<void()> function = instance->m_timeoutCallbackFunction;
        function();
    }
}

