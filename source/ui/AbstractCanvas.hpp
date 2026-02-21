#ifndef __SPARK_UI_ABSTRACTCANVAS_HPP_INCLUDED__
#define __SPARK_UI_ABSTRACTCANVAS_HPP_INCLUDED__

#include "ISparkRenderer.hpp"
#include "SparkRefCount.hpp"

namespace spark::ui {
    /**
    *
    */
    class AbstractCanvas : public virtual spark::SparkRefCount
    {
    public:
        AbstractCanvas();
        virtual ~AbstractCanvas(void);

    public:
        virtual void onKeyPressed(int key, int action);
        virtual void onMouseMove(real32 x, real32 y);
        virtual void onMouseClick(int button, int action);

    public:
        virtual void init() = 0;
        virtual void paint(spark::renderer::ISparkRenderer* renderer) = 0;
    };
}
#endif