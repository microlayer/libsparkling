#ifndef __SPARK_RENDERER_LIGHTBUFFER_OGLLIGHTBUFFER_HPP_INCLUDED__
#define __SPARK_RENDERER_LIGHTBUFFER_OGLLIGHTBUFFER_HPP_INCLUDED__

#include "ISparkLightBuffer.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS || \
    SPARK_PLATFORM == SPARK_PLATFORM_LINUX   || \
    SPARK_PLATFORM == SPARK_PLATFORM_APPLE
#include <GL/glew.h>
#endif
#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL || \
    SPARK_PLATFORM == SPARK_PLATFORM_ANDROID
#include <GLES3/gl3.h>
#endif

namespace spark::renderer::lightbuffer {
    /**
    *
    */
    class OGLLightBuffer : public ISparkLightBuffer
    {
    public:
        OGLLightBuffer();
        ~OGLLightBuffer();

    public:
        void init();
        void uploadLights(
            spark::renderer::shader::ISparkShader* shader,
            std::vector<renderer::lightbuffer::GPUDirectionalLight>& gpuDirectionalLights,
            std::vector<renderer::lightbuffer::GPUPointLight>& gpuPointLights);
    };
}
#endif