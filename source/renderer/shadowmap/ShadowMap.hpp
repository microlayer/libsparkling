#ifndef __SPARK_RENDERER_SHADOWMAP_OGLSHADOWMAP_HPP_INCLUDED__
#define __SPARK_RENDERER_SHADOWMAP_OGLSHADOWMAP_HPP_INCLUDED__

#include "ISparkShadowMap.hpp"
#include "ISparkTexture.hpp"
#include "ISparkFramebuffer.hpp"

namespace spark::renderer::shadowmap {
    /**
    *
    */
    class ShadowMap : public ISparkShadowMap
    {
    public:
        ShadowMap(
            spark::renderer::ISparkTexture* depthTexture,
            spark::renderer::ISparkFramebuffer* framebuffer);
        ~ShadowMap();

    public:
        spark::renderer::ISparkTexture* depthTexture() const;
        spark::renderer::ISparkFramebuffer* framebuffer() const;

    private:
        spark::renderer::ISparkTexture* m_depthTexture;
        spark::renderer::ISparkFramebuffer* m_framebuffer;
    };
}
#endif