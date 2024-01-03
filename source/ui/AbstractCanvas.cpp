#include "AbstractCanvas.hpp"
#include "ISparkRenderer.hpp"
#include "ISparkCommandListener.hpp"
//#include "ui/Event.hpp"

namespace spark {
    namespace ui {
        /**
        *
        */
        AbstractCanvas::AbstractCanvas()
        {
            //m_currentCommandListener = NULL;
        }

        /**
        *
        */
        AbstractCanvas::~AbstractCanvas(void)
        {
        }

        /**
         *
         */
         //void AbstractCanvas::processMoveEvent(spark::math::Vector2f direction, spark::real32 strength)
         //{

         //}

         /**
         *
         */
         //void AbstractCanvas::eventAction(spark::ui::Event::E_EVENT_TYPE eventType, spark::ui::Command::E_COMMAND_TYPE cmdType)
         //{
         //    if (m_currentCommandListener != NULL)
         //    {
         //        if (eventType == spark::ui::Event::EET_COMMAND)
         //        {
         //            m_currentCommandListener->executeCommand(cmdType, this);
         //        }

         //        if (eventType == spark::ui::Event::EET_MOVE)
         //        {
         //            processMoveEvent(spark::math::Vector2f(1.0, 0.0), 1.0);
         //        }

         //        if (eventType == spark::ui::Event::EET_SELECT)
         //        {
         //            //ProcessMoveEvent(spark::math::Vector2f(1.0, 0.0), 1.0);
         //        }
         //    }
         //}

         /**
         *
         */
         //void AbstractCanvas::registerCommandListener(spark::ui::ISparkCommandListener* commandListener)
         //{
         //    m_currentCommandListener = commandListener;
         //}

         /**
         *
         */
         //void AbstractCanvas::deRegisterCommandListener(spark::ui::ISparkCommandListener* commandListener)
         //{
         //    if (m_currentCommandListener == commandListener)
         //    {
         //        m_currentCommandListener = NULL;
         //    }
         //}
    } // end namespace ui
} // end namespace spark
