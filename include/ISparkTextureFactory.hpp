#ifndef __SPARK_RENDERER_ISPARKTEXTUREFACTORY_HPP_INCLUDED__
#define __SPARK_RENDERER_ISPARKTEXTUREFACTORY_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkTexture.hpp"
#include <string>

namespace spark {
    namespace renderer {
        /**
        *
        */
        class ISparkTextureFactory : public virtual spark::SparkRefCount
        {
        public:
            virtual spark::renderer::ISparkTexture* createOrUpdate(std::string id, uc8_t* data, int32_t width, int32_t height, spark::drawing::E_PIXEL_FORMAT pixelFormat) = 0;
        };
    } // end namespace renderer
} // end namespace spark
#endif