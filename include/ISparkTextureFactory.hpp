#ifndef __SPARK_RENDERER_ISPARKTEXTUREFACTORY_HPP_INCLUDED__
#define __SPARK_RENDERER_ISPARKTEXTUREFACTORY_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkTexture.hpp"

namespace spark {
    namespace renderer {
        /**
        *
        */
        class ISparkTextureFactory : public virtual spark::SparkRefCount
        {
        public:
            virtual spark::renderer::ISparkTexture* CreateOrUpdate(uc8_t* data) = 0;
        };
    }
}
#endif