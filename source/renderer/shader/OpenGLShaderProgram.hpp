#ifndef __SPARK_RENDERER_OPENGLSHADERPROGRAM_HPP_INCLUDED__
#define __SPARK_RENDERER_OPENGLSHADERPROGRAM_HPP_INCLUDED__

#include "spark/SparkSetup.hpp"
#include "ISparkShader.hpp"
#include "ISparkLogger.hpp"
#include "renderer/common/ERenderEngine.hpp"
#include "glsl_for_ogl_feature_level_glsles10/DefaultShader.hpp"
#include "glsl_for_gles2_feature_level_glsles10/DefaultShader.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS
#include <GL/glew.h>
#endif
#if SPARK_PLATFORM == SPARK_PLATFORM_ANDROID || \
    SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "stdlib.h"
#endif

namespace spark {
    namespace renderer {
        namespace shader {
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

            private:
                GLuint m_programObject;
                spark::log::ISparkLogger* m_logger;
                spark::renderer::E_RENDER_ENGINE m_rendererEngineType;
            };
        } // end namespace shader
    } // end namespace renderer
} // end namespace spark
#endif