#include "AbstractSparkWindow.hpp"

namespace spark {
    namespace device {
        namespace window {
            /**
            *
            */
            AbstractSparkWindow::AbstractSparkWindow(log::ISparkLogger* logger) :
                m_logger(logger),
                m_screenResolution({ 1196, 720 , real32(1196.0f / 720.0f) })
            {

            }

            /**
            *
            */
            AbstractSparkWindow::~AbstractSparkWindow(void)
            {
            }

            /**
            * @Brief Hardcoded Screen Resolution as default for this win32 and webgl Device
            */
            ScreenResolution AbstractSparkWindow::getScreenResolution()
            {
                return m_screenResolution;
            }
        } // end namespace window
    } // end namespace device
} // end namespace spark
