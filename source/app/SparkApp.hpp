#ifndef __SPARK_APPLICATION_SPARKAPP_HPP_INCLUDED__
#define __SPARK_APPLICATION_SPARKAPP_HPP_INCLUDED__

#include "ISparkApp.hpp"
#include "ui/AbstractCanvas.hpp"

namespace spark {
    namespace app {
        /**
        *
        */
        class SparkApp : public ISparkApp
        {
        public:
            SparkApp(void);
            virtual ~SparkApp(void);
            virtual spark::ui::AbstractCanvas* getActiveCanvas();
            void setActiveCanvas(spark::ui::AbstractCanvas* canvas);
            bool isCanvasChanged();
            void resetIsCanvasChanged();

        private:
            spark::ui::AbstractCanvas* m_activeCanvas;
            bool m_isCanvasChanged;
        };
    } // end namespace app
} // end namespace spark
#endif