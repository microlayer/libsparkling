#ifndef __SPARK_RENDERER_LIGHTBUFFER_GPULIGHTBUFFER_HPP_INCLUDED__
#define __SPARK_RENDERER_LIGHTBUFFER_GPULIGHTBUFFER_HPP_INCLUDED__

#include "spark/SparkLibConfig.hpp"
#include "GPUDirectionalLight.hpp"
#include "GPUPointLight.hpp"

namespace spark::renderer::lightbuffer {
    /**
    *
    */
    struct GPULightBuffer
    {
        uint32_t directionalLightCount;
        uint32_t pointLightCount;

        GPUDirectionalLight directionalLights[MAX_DIR_LIGHTS];
        GPUPointLight pointLights[MAX_POINT_LIGHTS];
    };
}
#endif