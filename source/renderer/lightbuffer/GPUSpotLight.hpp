#ifndef __SPARK_RENDERER_LIGHTBUFFER_GPUSPOTLIGHT_HPP_INCLUDED__
#define __SPARK_RENDERER_LIGHTBUFFER_GPUSPOTLIGHT_HPP_INCLUDED__

#include <math/Vector3.hpp>
#include "drawing/Color.hpp"

namespace spark::renderer::lightbuffer {
    /**
    *
    */
    struct GPUSpotLight
    {
        spark::math::Vector3f position;
        spark::math::Vector3f direction;
        spark::drawing::Color color;
        real32 intensity;
        real32 range;
        real32 angle;
    };
}
#endif