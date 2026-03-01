#include "AbstractSparkWindow.hpp"

namespace spark::device::window {
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
    * @brief Hardcoded Screen Resolution as default for this win32 and webgl Device
    */
    ScreenResolution AbstractSparkWindow::getScreenResolution()
    {
        return m_screenResolution;
    }
}
