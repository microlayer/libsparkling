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
                    m_logger->error("Creating shader failed");
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
                   
                    if (!vertexShader)
                    {
                        GLint infoLen = 0;
                        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLen);
                        if (infoLen > 1)
                        {
                            char infoLog[2048];	//Attention: Fix buffer size
                            glGetShaderInfoLog(vertexShader, infoLen, NULL, infoLog);
                            m_logger->info("Vertex Shader result: ", infoLog);
                        }
                        glDeleteShader(vertexShader);
                    }

                    if (!fragmentShader)
                    {
                        GLint infoLen = 0;
                        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLen);
                        if (infoLen > 1)
                        {
                            char infoLog[2048];	//Attention: Fix buffer size
                            glGetShaderInfoLog(fragmentShader, infoLen, NULL, infoLog);
                            m_logger->info("Fragment Shader result: ", infoLog);
                        }
                        glDeleteShader(fragmentShader);
                    }
                    glAttachShader(m_programObject, vertexShader);
                    glAttachShader(m_programObject, fragmentShader);

                    glBindAttribLocation(m_programObject, 0, "aVertexPosition");
                    glBindAttribLocation(m_programObject, 1, "aVertexNormal");
                    glBindAttribLocation(m_programObject, 2, "aVertexColor");
                    glBindAttribLocation(m_programObject, 3, "aTextureCoord");

                    glLinkProgram(m_programObject);
                    glUseProgram(m_programObject);

                    m_logger->info("Shader attached successfully")
                }
                return this;
            }

            /**
            *
            */
            void OpenGLShaderProgram::setProjectionViewMatrix(const real32* matrix)
            {
                glUniformMatrix4fv(glGetUniformLocation(m_programObject, "uModelViewProjectionMatrix"), 1, GL_FALSE, matrix);
            }
        } // end namespace shader
    } // end namespace renderer
} // end namespace spark