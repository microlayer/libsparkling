#ifndef __SPARK_SHADER_ISPARKSHADER_HPP_INCLUDED__
#define __SPARK_SHADER_ISPARKSHADER_HPP_INCLUDED__

#include "spark/SparkTypes.hpp"
#include "SparkRefCount.hpp"
#include "drawing/Color.hpp"
#include "math/Vector3.hpp"
#include "renderer/lightbuffer/GPUDirectionalLight.hpp"
#include "renderer/lightbuffer/GPUPointLight.hpp"
#include "renderer/lightbuffer/GPULightBuffer.hpp"
#include <string>
#include <vector>

namespace spark::renderer::shader {
    /**
    *
    */
    class ISparkShader : public virtual SparkRefCount
    {
    public:
        virtual void loadShader() = 0;
        virtual void compile() = 0;
        virtual ISparkShader* applyShader(std::string shaderName) = 0;

    public:
        virtual void setProjectionViewMatrix(const real32* matrix) = 0;
        virtual void setModelViewMatrix(const real32* matrix) = 0;
        virtual void setModelMatrix(const real32* matrix) = 0;
        virtual void setNormalMatrix(const real32* matrix) = 0;

    public:
        virtual void setDrawMode(uint32_t drawMode) = 0;
        virtual void setTextureUnit(uint32_t unit) = 0;
        virtual void setFontColor(spark::drawing::Color fontColor) = 0;

    public: // Light
        virtual void setLightBuffer(spark::renderer::lightbuffer::GPULightBuffer& lightBuffer) = 0;

    public: // PBR
        virtual void setAlbedo(spark::math::Vector3f albedo) = 0;
        virtual void setRoughness(spark::real32 roughness) = 0;
        virtual void setMetallic(spark::real32 metallic) = 0;
    };
}
#endif