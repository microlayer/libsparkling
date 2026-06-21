#ifndef __SPARK_RENDERER_LIGHTBUFFER_GPUPOINTLIGHT_HPP_INCLUDED__
#define __SPARK_RENDERER_LIGHTBUFFER_GPUPOINTLIGHT_HPP_INCLUDED__

#include <math/Vector3.hpp>
#include "drawing/Color.hpp"

namespace spark::renderer::lightbuffer {
    /**
    *
    */
    struct GPUPointLight
    {
        spark::math::Vector3f position;
        spark::drawing::Color color;
        real32 intensity;
        real32 range;
    };
}
#endif