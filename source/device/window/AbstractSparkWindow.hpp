#ifndef __SPARK_DEVICE_WINDOW_ABSTRACTSPARKWINDOW_HPP_INCLUDED__
#define __SPARK_DEVICE_WINDOW_ABSTRACTSPARKWINDOW_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkRenderer.hpp"
#include "ISparkLogger.hpp"
#include "ISparkDevice.hpp"
#include "ISparkWindow.hpp"

namespace spark {
    namespace device {
        namespace window {
            /**
            *
            */
            class AbstractSparkWindow : public spark::device::window::ISparkWindow
            {
            public:
                AbstractSparkWindow(spark::log::ISparkLogger* logger);
                virtual ~AbstractSparkWindow(void);

            public:
                virtual int32_t init() = 0;
                virtual int32_t createWindow(uint32_t screenWidth, uint32_t screenHeight) = 0;
                virtual void terminate() = 0;
                virtual void setWindowTitle(const char* title) = 0;
                virtual void swapBuffers() = 0;
                virtual bool isWindowActive() = 0;

            public:
                virtual ScreenResolution getScreenResolution();

            protected:
                log::ISparkLogger* m_logger;
                spark::device::ScreenResolution m_screenResolution;
            };
        } // end namespace window
    } // end namespace device
} // end namespace spark
#endif
