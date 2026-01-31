#include "OpenGLShaderProgram.hpp"

namespace spark {
    namespace renderer {
        namespace shader {
            /**
            *
            */
            OpenGLShaderProgram::OpenGLShaderProgram(spark::log::ISparkLogger* logger, spark::renderer::E_RENDER_ENGINE rendererType)
                : m_logger(logger),
                m_rendererEngineType(rendererType),
                m_programObject(0)
            {

            }

            /**
            *
            */
            OpenGLShaderProgram::~OpenGLShaderProgram()
            {

            }

            /**
            *
            */
            void OpenGLShaderProgram::loadShader()
            {

            }

            /**
            *
            */
            void OpenGLShaderProgram::compile()
            {

            }

            /**
            *
            */
            ISparkShader* OpenGLShaderProgram::applyShader(std::string shaderName)
            {
                m_programObject = glCreateProgram();

                GLuint vertexShader;
                GLuint fragmentShader;
                GLint vertShaderCompiled;
                GLint fragShaderCompiled;

                vertexShader = glCreateShader(GL_VERTEX_SHADER);
                fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                if (vertexShader == 0 || fragmentShader == 0)
                {
                    m_logger->error("Creating shader failed.");
                }
                else
                {
                    const char* vertShaderSource = 0;
                    const char* fragShaderSource = 0;
                    if (m_rendererEngineType == spark::renderer::ERE_OGLFLES2)
                    {
                        spark::renderer::shader::glsl_for_ogl_feature_level_glsles10::DefaultShader defaultShader;
                        vertShaderSource = defaultShader.GetVertexShader();
                        fragShaderSource = defaultShader.GetFragmentShader();
                    }
                    if (m_rendererEngineType == spark::renderer::ERE_OGLES2)
                    {
                        spark::renderer::shader::glsl_for_gles2_feature_level_glsles10::DefaultShader defaultShader;
                        vertShaderSource = defaultShader.GetVertexShader();
                        fragShaderSource = defaultShader.GetFragmentShader();
                    }

                    glShaderSource(vertexShader, 1, &vertShaderSource, NULL);
                    glShaderSource(fragmentShader, 1, &fragShaderSource, NULL);
                    glCompileShader(vertexShader);
                    glCompileShader(fragmentShader);
                    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertShaderCompiled);
                    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragShaderCompiled);

                    GLint infoLen = 0;
                    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLen);
                    if (infoLen > 1)
                    {
                        char infoLog[2048];	//Attention: Fix buffer size
                        glGetShaderInfoLog(vertexShader, infoLen, NULL, infoLog);
                        m_logger->info("Vertex Shader result: %s", &infoLog);
                    }

                    glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLen);
                    if (infoLen > 1)
                    {
                        char infoLog[2048];	//Attention: Fix buffer size
                        glGetShaderInfoLog(fragmentShader, infoLen, NULL, infoLog);
                        m_logger->info("Fragment Shader result: %s", infoLog);
                    }

                    glAttachShader(m_programObject, vertexShader);
                    glAttachShader(m_programObject, fragmentShader);

                    glBindAttribLocation(m_programObject, 0, "aVertexPosition");
                    glBindAttribLocation(m_programObject, 1, "aVertexNormal");
                    glBindAttribLocation(m_programObject, 2, "aVertexColor");
                    glBindAttribLocation(m_programObject, 3, "aTextureCoord");
                    glBindAttribLocation(m_programObject, 4, "aBarycentric");

                    glLinkProgram(m_programObject);
                    GLint linked = 0;
                    glGetProgramiv(m_programObject, GL_LINK_STATUS, &linked);
                    if (!linked) {
                        char infoLog[1024];
                        glGetProgramInfoLog(m_programObject, sizeof(infoLog), NULL, infoLog);
                        m_logger->error("Linker failed: %s", infoLog);
                    }
                    else
                    {
                        m_logger->info("Shader linked successful");
                    }

                    glUseProgram(m_programObject);

                    if (vertShaderCompiled && fragShaderCompiled)
                    {
                        m_logger->info("Shader compiled and used successfully");
                    }
                    else
                    {
                        m_logger->error("Shader failed to use. Cleaning up resources");
                        glDeleteShader(vertexShader);
                        glDeleteShader(fragmentShader);
                        glDeleteProgram(m_programObject);
                    }
                }
                init();
                return this;
            }

            /**
            *
            */
            void OpenGLShaderProgram::setProjectionViewMatrix(const real32* matrix)
            {
                glUniformMatrix4fv(glGetUniformLocation(m_programObject, "uModelViewProjectionMatrix"), 1, GL_FALSE, matrix);
            }

            /**
            *
            */
            void OpenGLShaderProgram::setDrawMode(uint32_t drawMode)
            {
                glUniform1i(glGetUniformLocation(m_programObject, "uDrawMode"), drawMode);
            }

            /**
            *
            */
            void OpenGLShaderProgram::setTextureUnit(uint32_t unit)
            {
                glActiveTexture(GL_TEXTURE0);
                int uTexture0Location = glGetUniformLocation(m_programObject, "uTexture0");
                glUniform1i(uTexture0Location, 0); // Tell the sampler to use texture unit 0
            }

            /**
            *
            */
            void OpenGLShaderProgram::setFontColor(spark::drawing::Color fontColor)
            {
                glUniform3f(glGetUniformLocation(m_programObject, "uFontColor"), fontColor.m_redf, fontColor.m_greenf, fontColor.m_bluef);
            }

            /**
            *
            */
            void OpenGLShaderProgram::setLightDirection(real32 x, real32 y, real32 z)
            {
                glUniform3f(glGetUniformLocation(m_programObject, "uLightDirection"), x, y, z);
            }

            /**
            *
            */
            void OpenGLShaderProgram::init()
            {
                setTextureUnit(0);
            }
        } // end namespace shader
    } // end namespace renderer
} // end namespace spark