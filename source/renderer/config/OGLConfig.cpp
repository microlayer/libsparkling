#include "OGLConfig.hpp"

namespace spark {
    namespace renderer {
        /**
        *
        */
        OGLConfig::OGLConfig(spark::device::window::ISparkWindow* window, spark::log::ISparkLogger* logger)
        {
            const GLubyte* version = glGetString(GL_VERSION);
            const GLubyte* renderer = glGetString(GL_RENDERER);
            const GLubyte* vendor = glGetString(GL_VENDOR);
            const GLubyte* extension = glGetString(GL_EXTENSIONS);
            const GLubyte* shadingLanguageVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

            logger->info((char*)version);
            logger->info((char*)renderer);
            logger->info((char*)vendor);
            //logger->info((char*)extension);
            logger->info((char*)shadingLanguageVersion);
        }

        /**
        *
        */
        OGLConfig::~OGLConfig()
        {

        }
    }
}