#include "ShadowMapFactory.hpp"

namespace spark::renderer {
    /**
    *
    */
    ShadowMapFactory::ShadowMapFactory(
        spark::renderer::ISparkTextureFactory* textureFactory,
        spark::renderer::ISparkFramebufferFactory* framebufferFactory) :
        m_textureFactory(textureFactory),
        m_framebufferFactory(framebufferFactory)
    {

    }

    /**
    *
    */
    ShadowMapFactory::~ShadowMapFactory()
    {

    }

    /**
    *
    */
    spark::renderer::ISparkShadowMap* ShadowMapFactory::create(uint32_t width, uint32_t height)
    {
        spark::renderer::ISparkTexture* depthTexture = m_textureFactory->createDepthTexture(width, height);
        spark::renderer::ISparkFramebuffer* framebuffer = m_framebufferFactory->createFramebuffer();
        framebuffer->attachDepthTexture(depthTexture);

        auto* shadowMap = new spark::renderer::shadowmap::ShadowMap(depthTexture, framebuffer);

        return shadowMap;
    }
}