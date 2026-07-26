#ifndef __SPARK_RENDERER_ISPARKSHADOWMAPFACTORY_HPP_INCLUDED__
#define __SPARK_RENDERER_ISPARKSHADOWMAPFACTORY_HPP_INCLUDED__

#include "ISparkShadowMap.hpp"

namespace spark::renderer {
    /**
    *
    */
    class ISparkShadowMapFactory : public virtual SparkRefCount
    {
    public:
        virtual spark::renderer::ISparkShadowMap* create(uint32_t width, uint32_t height) = 0;
    };
}
#endif