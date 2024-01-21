#include "AbstractSparkWindow.hpp"

namespace spark {
    namespace device {
        namespace window {
            /**
            *
            */
            AbstractSparkWindow::AbstractSparkWindow(log::ISparkLogger* logger) : m_logger(logger)
            {
            }

            /**
            *
            */
            AbstractSparkWindow::~AbstractSparkWindow(void)
            {
            }

            /**
            * @Brief Hardcoded Screen Resolution for this win32 Device. Equal to Android
            */
            ScreenResolution AbstractSparkWindow::getScreenResolution()
            {
                if (!m_landscape)
                {
                    ScreenResolution sr = { 720, 1184, (720.0f / 1184.0f) };	//ratio:0.608
                    return sr;
                }
                else
                {
                    ScreenResolution sr = { 1196, 720, (1196.0f / 720.0f) };	//ratio:1.66
                    return sr;
                }
            }
        } // end namespace window
    } // end namespace device
} // end namespace spark
