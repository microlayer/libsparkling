#ifndef __SPARK_RENDERER_OPENGLSHADERPROGRAM_HPP_INCLUDED__
#define __SPARK_RENDERER_OPENGLSHADERPROGRAM_HPP_INCLUDED__

#include "spark/SparkSetup.hpp"
#include "ISparkShader.hpp"
#include "glsl-for-ogl-feature-level-glsles10/DefaultShader.hpp"
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
                OpenGLShaderProgram();
                virtual ~OpenGLShaderProgram(void);

            public:
                void loadShader();
                void compile();
                ISparkShader* applyShader(std::string shaderName);

            public:
                void setProjectionViewMatrix(const real32* matrix);

            private:
                GLuint m_programObject;
            };
        } // end namespace shader
    } // end namespace renderer
} // end namespace spark
#endif