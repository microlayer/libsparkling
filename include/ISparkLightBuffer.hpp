#ifndef __SPARK_RENDERER_LIGHTBUFFER_ISPARKLIGHTBUFFER_HPP_INCLUDED__
#define __SPARK_RENDERER_LIGHTBUFFER_ISPARKLIGHTBUFFER_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "renderer/lightbuffer/GPUDirectionalLight.hpp"
#include "renderer/lightbuffer/GPUPointLight.hpp"
#include "ISparkShader.hpp"
#include <vector>

namespace spark::renderer::lightbuffer {
    /**
    *
    */
    class ISparkLightBuffer :public virtual SparkRefCount
    {
    public:
        virtual void init() = 0;
        virtual void uploadLights(
            spark::renderer::shader::ISparkShader* shader,
            std::vector<renderer::lightbuffer::GPUDirectionalLight>& gpuDirectionalLights,
            std::vector<renderer::lightbuffer::GPUPointLight>& gpuPointLights) = 0;
    };
}
#endif