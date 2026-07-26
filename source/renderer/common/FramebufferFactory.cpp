#include "FramebufferFactory.hpp"
#include "renderer/framebuffer/OGLFramebuffer.hpp"

namespace spark::renderer {
    /**
    *
    */
    FramebufferFactory::FramebufferFactory()
    {

    }

    /**
    *
    */
    FramebufferFactory::~FramebufferFactory()
    {

    }

    /**
    *
    */
    spark::renderer::ISparkFramebuffer* FramebufferFactory::createFramebuffer()
    {
        auto* framebuffer = new renderer::framebuffer::OGLFramebuffer();

        return framebuffer;
    }
}