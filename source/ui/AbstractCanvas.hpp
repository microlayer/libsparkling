#ifndef __SPARK_UI_ABSTRACTCANVAS_HPP_INCLUDED__
#define __SPARK_UI_ABSTRACTCANVAS_HPP_INCLUDED__

#include "ISparkRenderer.hpp"
#include "SparkRefCount.hpp"
//#include "ISparkCommandListener.hpp"
//#include "ui/Event.hpp"

namespace spark {
    namespace ui {
        /**
        *
        */
        class AbstractCanvas : public virtual spark::SparkRefCount
        {
        public:
            AbstractCanvas();
            virtual ~AbstractCanvas(void);
            //virtual void processMoveEvent(spark::math::Vector2f direction, spark::real32 strength);
            //void eventAction(spark::ui::Event::E_EVENT_TYPE eventType, spark::ui::Command::E_COMMAND_TYPE cmdType);
            //void registerCommandListener(spark::ui::ISparkCommandListener* commandListener);
            //void deRegisterCommandListener(spark::ui::ISparkCommandListener* commandListener);

        public:
            virtual void paint(spark::renderer::ISparkRenderer* renderer) = 0;

        private:
            //spark::ui::ISparkCommandListener* m_currentCommandListener;
        };

    } // end namespace ui
} // end namespace spark
#endif