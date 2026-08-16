#include "OpenGLShaderProgram.hpp"

namespace spark::renderer::shader {
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
                spark::renderer::shader::glsl_for_ogl_feature_level_glsles30::DefaultShader defaultShader;
                vertShaderSource = defaultShader.GetVertexShader();
                fragShaderSource = defaultShader.GetFragmentShader();
            }
            if (m_rendererEngineType == spark::renderer::ERE_OGLES2)
            {
                spark::renderer::shader::glsl_for_gles3_feature_level_glsles30::DefaultShader defaultShader;
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
    * TODO: remove glGetUniformLocation replace with cached uniform location in shader init O(n)
    */
    void OpenGLShaderProgram::setProjectionViewMatrix(const real32* matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_programObject, "uModelViewProjectionMatrix"), 1, GL_FALSE, matrix);
    }

    /**
    * TODO: remove glGetUniformLocation replace with cached uniform location in shader init O(n)
    */
    void OpenGLShaderProgram::setModelViewMatrix(const real32* matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_programObject, "uModelViewMatrix"), 1, GL_FALSE, matrix);
    }

    /**
    * TODO: remove glGetUniformLocation replace with cached uniform location in shader init O(n)
    */
    void OpenGLShaderProgram::setModelMatrix(const real32* matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_programObject, "uModelMatrix"), 1, GL_FALSE, matrix);
    }

    /**
    * TODO: remove glGetUniformLocation replace with cached uniform location in shader init O(n)
    */
    void OpenGLShaderProgram::setNormalMatrix(const real32* matrix)
    {
        glUniformMatrix3fv(glGetUniformLocation(m_programObject, "uNormalMatrix"), 1, GL_FALSE, matrix);
    }

    /**
    * TODO: remove glGetUniformLocation replace with cached uniform location in shader init O(n)
    */
    void OpenGLShaderProgram::setLightViewProjection(const real32* matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_programObject, "uLightViewProjection"), 1, GL_FALSE, matrix);
    }

    /**
    * TODO: remove glGetUniformLocation replace with cached uniform location in shader init O(n)
    */
    void OpenGLShaderProgram::setDrawMode(uint32_t drawMode)
    {
        glUniform1i(glGetUniformLocation(m_programObject, "uDrawMode"), drawMode);
    }

    /**
    * TODO: remove glGetUniformLocation replace with cached uniform location in shader init O(n)
    */
    void OpenGLShaderProgram::setTextureUnit(const std::string& name, uint32_t unit)
    {
        int uTextureLocation = glGetUniformLocation(m_programObject, name.c_str());


        glUniform1i(uTextureLocation, unit); // Tell the sampler with name to use texture unit 
    }

    /**
    * TODO: remove glGetUniformLocation replace with cached uniform location in shader init O(n)
    */
    void OpenGLShaderProgram::setFontColor(spark::drawing::Color fontColor)
    {
        glUniform3f(glGetUniformLocation(m_programObject, "uFontColor"), fontColor.m_redf, fontColor.m_greenf, fontColor.m_bluef);
    }

    /**
    * TODO: remove glGetUniformLocation replace with cached uniform location in shader init O(n)
    */
    void OpenGLShaderProgram::setLightBuffer(spark::renderer::lightbuffer::GPULightBuffer& lightBuffer)
    {
        GLint locDirectionalLightCount = glGetUniformLocation(m_programObject, "uDirectionalLightCount");
        GLint locDirectionallLightDirections = glGetUniformLocation(m_programObject, "uDirectionalLightDirection");
        GLint locDirectionallLightColors = glGetUniformLocation(m_programObject, "uDirectionalLightColor");
        GLint locDirectionallLightIntensitys = glGetUniformLocation(m_programObject, "uDirectionalLightIntensity");

        GLint locSpotLightCount = glGetUniformLocation(m_programObject, "uSpotLightCount");
        GLint locSpotLightPositions = glGetUniformLocation(m_programObject, "uSpotLightPosition");
        GLint locSpotLightDirections = glGetUniformLocation(m_programObject, "uSpotLightDirection");
        GLint locSpotLightColors = glGetUniformLocation(m_programObject, "uSpotLightColor");
        GLint locSpotLightIntensitys = glGetUniformLocation(m_programObject, "uSpotLightIntensity");
        GLint locSpotLightRanges = glGetUniformLocation(m_programObject, "uSpotLightRange");
        GLint locSpotLightAngles = glGetUniformLocation(m_programObject, "uSpotLightAngle");


        GLint locPointLightCount = glGetUniformLocation(m_programObject, "uPointLightCount");
        GLint locPointLightPositions = glGetUniformLocation(m_programObject, "uPointLightPosition");
        GLint locPointLightColors = glGetUniformLocation(m_programObject, "uPointLightColor");
        GLint locPointLightIntensitys = glGetUniformLocation(m_programObject, "uPointLightIntensity");
        GLint locPointLightRanges = glGetUniformLocation(m_programObject, "uPointLightRange");

        int directionalLightCount = std::min(static_cast<int>(lightBuffer.directionalLightCount), 4);
        if (locDirectionalLightCount != -1) glUniform1i(locDirectionalLightCount, directionalLightCount);

        if (directionalLightCount > 0)
        {
            real32 directions[4 * 3] = { 0.0f };
            real32 colors[4 * 3] = { 0.0f };
            real32 intensities[4] = { 0.0f };

            for (int i = 0; i < directionalLightCount; ++i)
            {
                const auto& light = lightBuffer.directionalLights[i];

                directions[i * 3 + 0] = light.direction.m_x;
                directions[i * 3 + 1] = light.direction.m_y;
                directions[i * 3 + 2] = light.direction.m_z;

                colors[i * 3 + 0] = (real32)light.color.m_redf;
                colors[i * 3 + 1] = (real32)light.color.m_greenf;
                colors[i * 3 + 2] = (real32)light.color.m_bluef;

                intensities[i] = light.intensity;
            }

            if (locDirectionallLightDirections != -1)  glUniform3fv(locDirectionallLightDirections, directionalLightCount, directions);
            if (locDirectionallLightColors != -1)     glUniform3fv(locDirectionallLightColors, directionalLightCount, colors);
            if (locDirectionallLightIntensitys != -1) glUniform1fv(locDirectionallLightIntensitys, directionalLightCount, intensities);
        }

        int spotLightCount = std::min(static_cast<int>(lightBuffer.spotLightCount), 4);
        if (locSpotLightCount != -1) glUniform1i(locSpotLightCount, spotLightCount);

        if (spotLightCount > 0)
        {
            real32 positions[4 * 3] = { 0.0f };
            real32 directions[4 * 3] = { 0.0f };
            real32 colors[4 * 3] = { 0.0f };
            real32 intensities[4] = { 0.0f };
            real32 ranges[4] = { 0.0f };
            real32 angles[4] = { 0.0f };

            for (int i = 0; i < spotLightCount; ++i)
            {
                const auto& light = lightBuffer.spotLights[i];

                positions[i * 3 + 0] = light.position.m_x;
                positions[i * 3 + 1] = light.position.m_y;
                positions[i * 3 + 2] = light.position.m_z;

                directions[i * 3 + 0] = light.direction.m_x;
                directions[i * 3 + 1] = light.direction.m_y;
                directions[i * 3 + 2] = light.direction.m_z;

                colors[i * 3 + 0] = (real32)light.color.m_redf;
                colors[i * 3 + 1] = (real32)light.color.m_greenf;
                colors[i * 3 + 2] = (real32)light.color.m_bluef;

                intensities[i] = light.intensity;
                ranges[i] = light.range;
                angles[i] = light.angle;
            }

            if (locSpotLightPositions != -1)  glUniform3fv(locSpotLightPositions, spotLightCount, positions);
            if (locSpotLightDirections != -1) glUniform3fv(locSpotLightDirections, spotLightCount, directions);
            if (locSpotLightColors != -1)     glUniform3fv(locSpotLightColors, spotLightCount, colors);
            if (locSpotLightIntensitys != -1) glUniform1fv(locSpotLightIntensitys, spotLightCount, intensities);
            if (locSpotLightRanges != -1)     glUniform1fv(locSpotLightRanges, spotLightCount, ranges);
            if (locSpotLightAngles != -1)     glUniform1fv(locSpotLightAngles, spotLightCount, angles);
        }

        int pointLightCount = std::min(static_cast<int>(lightBuffer.pointLightCount), 4);
        if (locPointLightCount != -1) glUniform1i(locPointLightCount, pointLightCount);

        if (pointLightCount > 0)
        {
            real32 positions[4 * 3] = { 0.0f };
            real32 colors[4 * 3] = { 0.0f };
            real32 intensities[4] = { 0.0f };
            real32 ranges[4] = { 0.0f };

            for (int i = 0; i < pointLightCount; ++i)
            {
                const auto& light = lightBuffer.pointLights[i];

                positions[i * 3 + 0] = light.position.m_x;
                positions[i * 3 + 1] = light.position.m_y;
                positions[i * 3 + 2] = light.position.m_z;

                colors[i * 3 + 0] = (real32)light.color.m_redf;
                colors[i * 3 + 1] = (real32)light.color.m_greenf;
                colors[i * 3 + 2] = (real32)light.color.m_bluef;

                intensities[i] = light.intensity;
                ranges[i] = light.range;
            }

            if (locPointLightPositions != -1)  glUniform3fv(locPointLightPositions, pointLightCount, positions);
            if (locPointLightColors != -1)     glUniform3fv(locPointLightColors, pointLightCount, colors);
            if (locPointLightIntensitys != -1) glUniform1fv(locPointLightIntensitys, pointLightCount, intensities);
            if (locPointLightRanges != -1)     glUniform1fv(locPointLightRanges, pointLightCount, ranges);
        }
    }

    /**
    *
    */
    void OpenGLShaderProgram::setAlbedo(spark::math::Vector3f albedo)
    {
        GLint loc = glGetUniformLocation(m_programObject, "uAlbedo");
        glUniform3f(loc, albedo.m_x, albedo.m_y, albedo.m_z);
    }

    /**
    *
    */
    void OpenGLShaderProgram::setRoughness(spark::real32 roughness)
    {
        GLint loc = glGetUniformLocation(m_programObject, "uRoughness");
        glUniform1f(loc, roughness);
    }

    /**
    *
    */
    void OpenGLShaderProgram::setMetallic(spark::real32 metallic)
    {
        GLint loc = glGetUniformLocation(m_programObject, "uMetallic");
        glUniform1f(loc, metallic);
    }

    /**
    *
    */
    void OpenGLShaderProgram::setAO(real32 ao)
    {
        GLint loc = glGetUniformLocation(m_programObject, "uAo");
        glUniform1f(loc, ao);
    }

    /**
    *
    */
    void OpenGLShaderProgram::setHasAlbedoTexture(bool flag)
    {
        GLint loc = glGetUniformLocation(m_programObject, "uHasAlbedoTexture");
        glUniform1i(loc, flag ? 1 : 0);
    }

    /**
    *
    */
    void OpenGLShaderProgram::setHasShadowMap(bool flag)
    {
        GLint loc = glGetUniformLocation(m_programObject, "uHasShadowMap");
        glUniform1i(loc, flag ? 1 : 0);
    }

    /**
    *
    */
    void OpenGLShaderProgram::setShadowPass(bool flag)
    {
        GLint loc = glGetUniformLocation(m_programObject, "uShadowPass");
        glUniform1i(loc, flag ? 1 : 0);
    }

    /**
    * Initializes shader
    */
    void OpenGLShaderProgram::init()
    {
        setTextureUnit("uDefaultTexture", 0);
        setTextureUnit("uAlbedoMap", 1);
        setTextureUnit("uNormalMap", 2);
        setTextureUnit("uRoughnessMap", 3);
        setTextureUnit("uMetallicMap", 4);
        setTextureUnit("uShadowMap", 7);

        setAlbedo(spark::math::Vector3f(1, 1, 1));
        setHasShadowMap(false);
    }
}