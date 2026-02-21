#include "AbstractCanvas.hpp"
#include "ISparkRenderer.hpp"
#include "ISparkCommandListener.hpp"
//#include "ui/Event.hpp"

namespace spark::ui {
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
    void AbstractCanvas::onKeyPressed(int key, int action)
    {

    }

    /**
    *
    */
    void AbstractCanvas::onMouseMove(real32 x, real32 y)
    {

    }

    /**
    *
    */
    void AbstractCanvas::onMouseClick(int button, int action)
    {

    }

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
}
