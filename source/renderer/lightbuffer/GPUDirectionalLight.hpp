#ifndef __SPARK_RENDERER_LIGHTBUFFER_GPUDIRECTIONALLIGHT_HPP_INCLUDED__
#define __SPARK_RENDERER_LIGHTBUFFER_GPUDIRECTIONALLIGHT_HPP_INCLUDED__

#include <math/Vector3.hpp>
#include "drawing/Color.hpp"

namespace spark::renderer::lightbuffer {
    /**
    *
    */
    struct GPUDirectionalLight
    {
        spark::math::Vector3f direction;
        spark::drawing::Color color;
        real32 intensity;
    };
}
#endif