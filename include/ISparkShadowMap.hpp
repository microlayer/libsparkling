#ifndef __SPARK_RENDERER_ISPARKSHADOWMAP_HPP_INCLUDED__
#define __SPARK_RENDERER_ISPARKSHADOWMAP_HPP_INCLUDED__

#include "ISparkTexture.hpp"
#include "ISparkFramebuffer.hpp"

namespace spark::renderer {
    /**
    *
    */
    class ISparkShadowMap : public virtual SparkRefCount
    {
    public:
        virtual ISparkTexture* depthTexture() const = 0;

        virtual ISparkFramebuffer* framebuffer() const = 0;
    };
}
#endif