#ifndef __SPARK_RENDERER_FRAMEBUFFER_OGLFRAMEBUFFER_HPP_INCLUDED__
#define __SPARK_RENDERER_FRAMEBUFFER_OGLFRAMEBUFFER_HPP_INCLUDED__

#include "ISparkFramebuffer.hpp"
#include "ISparkTexture.hpp"
#include "ISparkLogger.hpp"
#include "renderer/texture/OGLTexture.hpp"

#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS || \
    SPARK_PLATFORM == SPARK_PLATFORM_LINUX   || \
    SPARK_PLATFORM == SPARK_PLATFORM_APPLE
#include <GL/glew.h>
#endif
#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL || \
    SPARK_PLATFORM == SPARK_PLATFORM_ANDROID
#include <GLES3/gl3.h>
#endif

namespace spark::renderer::framebuffer {
    /**
    *
    */
    class OGLFramebuffer : public spark::renderer::ISparkFramebuffer
    {
    public:
        OGLFramebuffer();
        ~OGLFramebuffer();

    public:
        void attachDepthTexture(spark::renderer::ISparkTexture* depthTexture);
        uint32_t getWidth() const;
        uint32_t getHeight() const;

    public:
        GLuint getHandle();

    private:
        GLuint m_fbo;
        GLuint m_depthTextureId;
        spark::renderer::texture::OGLTexture* m_oglTexture;
    };
}
#endif