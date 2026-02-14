#ifndef __SPARK_APPLICATION_ISPARKAPP_HPP_INCLUDED__
#define __SPARK_APPLICATION_ISPARKAPP_HPP_INCLUDED__

#include "ui/AbstractCanvas.hpp"

namespace spark::app {
    /**
    *
    */
    class ISparkApp
    {
    public:
        virtual void onInit() = 0;
        virtual spark::ui::AbstractCanvas* getActiveCanvas() = 0;
        virtual void setActiveCanvas(spark::ui::AbstractCanvas* canvas) = 0;
    };
}
#endif