#ifndef __SPARK_RENDERER_SHADOWMAPFACTORY_HPP_INCLUDED__
#define __SPARK_RENDERER_SHADOWMAPFACTORY_HPP_INCLUDED__

#include "ISparkShadowMapFactory.hpp"
#include "ISparkShadowMap.hpp"
#include "ISparkTextureFactory.hpp"
#include "FramebufferFactory.hpp"
#include "renderer/shadowmap/ShadowMap.hpp"

namespace spark::renderer {
    /**
    *
    */
    class ShadowMapFactory : public spark::renderer::ISparkShadowMapFactory
    {
    public:
        ShadowMapFactory(
            spark::renderer::ISparkTextureFactory* textureFactory,
            spark::renderer::ISparkFramebufferFactory* framebufferFactory);
        ~ShadowMapFactory();

    public:
        spark::renderer::ISparkShadowMap* create(uint32_t width, uint32_t height);

    private:
        spark::renderer::ISparkTextureFactory* m_textureFactory;
        spark::renderer::ISparkFramebufferFactory* m_framebufferFactory;
    };
}
#endif