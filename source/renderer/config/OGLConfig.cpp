#include "OGLConfig.hpp"
#include <string.h>

namespace spark {
    namespace renderer {
        /**
        *
        */
        OGLConfig::OGLConfig(spark::device::window::ISparkWindow* window, spark::log::ISparkLogger* logger)
        {
            char extensionBuffer[512];
            const GLubyte* version = glGetString(GL_VERSION);
            const GLubyte* renderer = glGetString(GL_RENDERER);
            const GLubyte* vendor = glGetString(GL_VENDOR);
            const GLubyte* extension = glGetString(GL_EXTENSIONS);
            const GLubyte* shadingLanguageVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

            if (extension != NULL)
            {
                strncpy(extensionBuffer, (const char*)extension, sizeof(extensionBuffer) - 1);
                extensionBuffer[sizeof(extensionBuffer) - 1] = '\0';
            }

            logger->info((char*)version);
            logger->info((char*)renderer);
            logger->info((char*)vendor);
            logger->info((char*)extensionBuffer);
            logger->info((char*)shadingLanguageVersion);

            GLint profileMask = 0;
            glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profileMask);

            if (profileMask & GL_CONTEXT_CORE_PROFILE_BIT)
            {
                logger->info("Running in Core Profile");

            }
            else if (profileMask & GL_CONTEXT_COMPATIBILITY_PROFILE_BIT)
            {
                logger->info("Running in Compatibility Profile");
            }
            else
            {
                logger->info("Running inUnknown Profile");
            }
        }

        /**
        *
        */
        OGLConfig::~OGLConfig()
        {

        }
    }
}