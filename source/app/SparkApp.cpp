#include "SparkApp.hpp"

namespace spark {
    namespace app {
        /**
        *
        */
        SparkApp::SparkApp(void)
        {
            m_activeCanvas = NULL;
            m_isCanvasChanged = false;
        }

        /**
        *
        */
        SparkApp::~SparkApp(void)
        {

        }

        /**
        *
        */
        spark::ui::AbstractCanvas* SparkApp::getActiveCanvas()
        {
            return m_activeCanvas;
        }

        /**
         *
         */
        void SparkApp::setActiveCanvas(spark::ui::AbstractCanvas* canvas)
        {
            m_activeCanvas = canvas;
            m_isCanvasChanged = true;
        }

        /**
        *
        */
        bool SparkApp::isCanvasChanged()
        {
            return m_isCanvasChanged;
        }

        /**
         *
         */
        void SparkApp::resetIsCanvasChanged()
        {
            m_isCanvasChanged = false;
        }
    } // end namespace application
} // end namespace spark
