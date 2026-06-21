#include "OGLLightBuffer.hpp"
#include "GPULightBuffer.hpp"

namespace spark::renderer::lightbuffer {
    /**
    *
    */
    OGLLightBuffer::OGLLightBuffer()
    {

    }

    /**
    *
    */
    OGLLightBuffer::~OGLLightBuffer()
    {

    }

    /**
    * With GLSL ES 3.00 GL_UNIFORM_BUFFER can be used.
    */
    void OGLLightBuffer::init()
    {

    }

    /**
    *
    */
    void OGLLightBuffer::uploadLights(
        spark::renderer::shader::ISparkShader* shader,
        std::vector<renderer::lightbuffer::GPUDirectionalLight>& gpuDirectionalLights,
        std::vector<renderer::lightbuffer::GPUPointLight>& gpuPointLights)
    {
        spark::renderer::lightbuffer::GPULightBuffer lightBuffer{};

        lightBuffer.directionalLightCount = std::min(gpuDirectionalLights.size(), static_cast<size_t>(MAX_DIR_LIGHTS));
        lightBuffer.pointLightCount = std::min(gpuPointLights.size(), static_cast<size_t>(MAX_POINT_LIGHTS));

        memcpy(
            lightBuffer.directionalLights, gpuDirectionalLights.data(),
            lightBuffer.directionalLightCount * sizeof(GPUDirectionalLight));

        memcpy(lightBuffer.pointLights, gpuPointLights.data(),
            lightBuffer.pointLightCount * sizeof(GPUPointLight));

        shader->setLightBuffer(lightBuffer);
    }
}