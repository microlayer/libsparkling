#ifndef __SPARK_SHADER_ISPARKSHADER_HPP_INCLUDED__
#define __SPARK_SHADER_ISPARKSHADER_HPP_INCLUDED__

#include "spark/SparkTypes.hpp"
#include "SparkRefCount.hpp"
#include "drawing/Color.hpp"
#include <string>

namespace spark {
    namespace renderer {
        namespace shader {
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
                virtual void setDrawMode(uint32_t drawMode) = 0;
                virtual void setTextureUnit(uint32_t unit) = 0;
                virtual void setFontColor(spark::drawing::Color fontColor) = 0;
                virtual void setLightDirection(real32 x, real32 y, real32 z) = 0;
            };
        } // end namespace shader
    } // end namespace renderer
} // end namespace spark
#endif