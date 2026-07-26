#include "ShadowMap.hpp"

namespace spark::renderer::shadowmap {
    /**
    *
    */
    ShadowMap::ShadowMap(
        spark::renderer::ISparkTexture* depthTexture,
        spark::renderer::ISparkFramebuffer* framebuffer) :
        m_depthTexture(depthTexture),
        m_framebuffer(framebuffer)
    {

    }

    /**
    *
    */
    ShadowMap::~ShadowMap()
    {
        m_depthTexture->release();
        m_framebuffer->release();
    }

    /**
    *
    */
    spark::renderer::ISparkTexture* ShadowMap::depthTexture() const
    {
        return m_depthTexture;
    }

    /**
    *
    */
    spark::renderer::ISparkFramebuffer* ShadowMap::framebuffer() const
    {
        return m_framebuffer;
    }
}