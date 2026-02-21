#ifndef __SPARK_RENDERER_OPENGLSHADERPROGRAM_HPP_INCLUDED__
#define __SPARK_RENDERER_OPENGLSHADERPROGRAM_HPP_INCLUDED__

#include "spark/SparkSetup.hpp"
#include "ISparkShader.hpp"
#include "ISparkLogger.hpp"
#include "renderer/common/ERenderEngine.hpp"
#include "drawing/Color.hpp"
#include "glsl_for_ogl_feature_level_glsles10/DefaultShader.hpp"
#include "glsl_for_gles2_feature_level_glsles10/DefaultShader.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS || \
    SPARK_PLATFORM == SPARK_PLATFORM_LINUX   || \
    SPARK_PLATFORM == SPARK_PLATFORM_APPLE
#include <GL/glew.h>
#endif
#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL || \
    SPARK_PLATFORM == SPARK_PLATFORM_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "stdlib.h"
#endif

namespace spark::renderer::shader {
    /**
    *
    */
    class OpenGLShaderProgram : public spark::renderer::shader::ISparkShader
    {
    public:
        OpenGLShaderProgram(spark::log::ISparkLogger* logger, spark::renderer::E_RENDER_ENGINE rendererType);
        virtual ~OpenGLShaderProgram(void);

    public:
        void loadShader();
        void compile();
        ISparkShader* applyShader(std::string shaderName);

    public:
        void setProjectionViewMatrix(const real32* matrix);
        void setDrawMode(uint32_t drawMode);
        void setTextureUnit(uint32_t unit);
        void setFontColor(spark::drawing::Color fontColor);
        void setLightDirection(real32 x, real32 y, real32 z);

    private:
        void init();

    private:
        GLuint m_programObject;
        spark::log::ISparkLogger* m_logger;
        spark::renderer::E_RENDER_ENGINE m_rendererEngineType;
    };
}
#endif