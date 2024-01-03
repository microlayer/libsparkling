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
        } // end namespace window
    } // end namespace device
} // end namespace spark
