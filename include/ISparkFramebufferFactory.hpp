#ifndef __SPARK_RENDERER_ISPARKFRAMEBUFFERFACTORY_HPP_INCLUDED__
#define __SPARK_RENDERER_ISPARKFRAMEBUFFERFACTORY_HPP_INCLUDED__

#include "ISparkFramebuffer.hpp"

namespace spark::renderer {
    /**
    *
    */
    class ISparkFramebufferFactory : public virtual SparkRefCount
    {
    public:
        virtual spark::renderer::ISparkFramebuffer* createFramebuffer() = 0;
    };
}
#endif