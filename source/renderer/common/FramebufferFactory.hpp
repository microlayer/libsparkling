#ifndef __SPARK_RENDERER_FRAMEBUFFERFACTORY_HPP_INCLUDED__
#define __SPARK_RENDERER_FRAMEBUFFERFACTORY_HPP_INCLUDED__

#include "ISparkFramebufferFactory.hpp"

namespace spark::renderer {
    /**
    *
    */
    class FramebufferFactory : public spark::renderer::ISparkFramebufferFactory
    {
    public:
        FramebufferFactory();
        ~FramebufferFactory();

    public:
        spark::renderer::ISparkFramebuffer* createFramebuffer();

    };
}
#endif