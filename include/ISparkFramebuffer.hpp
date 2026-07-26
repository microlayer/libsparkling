#ifndef __SPARK_RENDERER_ISPARKFRAMEBUFFER_HPP_INCLUDED__
#define __SPARK_RENDERER_ISPARKFRAMEBUFFER_HPP_INCLUDED__

#include "ISparkTexture.hpp"

namespace spark::renderer {
    /**
    *
    */
    class ISparkFramebuffer : public virtual SparkRefCount
    {
    public:
        virtual void attachDepthTexture(spark::renderer::ISparkTexture* depthTexture) = 0;
        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;
    };
}
#endif