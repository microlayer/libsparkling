#ifndef __SPARK_RENDERER_OGLCONFIG_HPP_INCLUDED__
#define __SPARK_RENDERER_OGLCONFIG_HPP_INCLUDED__

#include "ISparkRendererApiConfig.hpp"
#include "ISparkWindow.hpp"
#include "ISparkLogger.hpp"
#include <GL/glew.h>

namespace spark::renderer {
    /**
    *
    */
    class OGLConfig : public spark::renderer::ISparkRendererApiConfig
    {
    public:
        OGLConfig(spark::device::window::ISparkWindow* window, spark::log::ISparkLogger* logger);
        ~OGLConfig();
    };
}
#endif