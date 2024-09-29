#include "OpenGLShaderProgram.hpp"

namespace spark {
    namespace renderer {
        namespace shader {
            /**
            *
            */
            OpenGLShaderProgram::OpenGLShaderProgram()
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
                if (vertexShader == 0 || fragmentShader)
                {
                    // NOK
                }
                spark::renderer::shader::glslfles10::DefaultShader defaultShader;
                const char* vertShaderSource = defaultShader.GetVertexShader();
                const char* fragShaderSource = defaultShader.GetFragmentShader();
                glShaderSource(vertexShader, 1, &vertShaderSource, NULL);
                glShaderSource(fragmentShader, 1, &fragShaderSource, NULL);
                glCompileShader(vertexShader);
                glCompileShader(fragmentShader);
                glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertShaderCompiled);
                glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragShaderCompiled);


                char infoLog[512];
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);

                //m_logger->info(infoLog);

                if (!vertexShader)
                {
                    GLint infoLen = 0;
                    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLen);
                    if (infoLen > 1)
                    {
                        char infoLog[2048];	//Attention: Fix buffer size
                        glGetShaderInfoLog(vertexShader, infoLen, NULL, infoLog);
                        //m_logger->info("Error compiling shader:\n%s\n", infoLog);
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
                        //m_logger->info("Error compiling shader:\n%s\n", infoLog);
                    }
                    glDeleteShader(fragmentShader);
                }
                glAttachShader(m_programObject, vertexShader);
                glAttachShader(m_programObject, fragmentShader);

                glBindAttribLocation(m_programObject, 0, "aPosition");
                glBindAttribLocation(m_programObject, 1, "aNormal");
                glBindAttribLocation(m_programObject, 2, "aColor");
                glBindAttribLocation(m_programObject, 3, "aTextureCoord");

                glLinkProgram(m_programObject);
                glUseProgram(m_programObject);
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