#include "OGLFramebuffer.hpp"
#include <assert.h>

namespace spark::renderer::framebuffer {
    /**
    *
    */
    OGLFramebuffer::OGLFramebuffer()
    {
        glGenFramebuffers(1, &m_fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

    }

    /**
    *
    */
    OGLFramebuffer::~OGLFramebuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDeleteFramebuffers(1, &m_fbo);
        m_fbo = 0;
    }

    /**
    *
    */
    void OGLFramebuffer::attachDepthTexture(spark::renderer::ISparkTexture* depthTexture)
    {
        m_oglTexture = static_cast<spark::renderer::texture::OGLTexture*>(depthTexture);

        m_depthTextureId = m_oglTexture->getHandle();


        depthTexture->bind(spark::renderer::TextureSlot::ShadowMap);
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

      

        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_DEPTH_ATTACHMENT,
            GL_TEXTURE_2D,
            m_depthTextureId,
            0);

        //glDrawBuffer(GL_NONE);
        //glReadBuffer(GL_NONE);

        const GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        assert(status == GL_FRAMEBUFFER_COMPLETE);
       
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    /**
    *
    */
    uint32_t OGLFramebuffer::getWidth() const
    {
        return m_oglTexture->getWidth();
    }

    /**
    *
    */
    uint32_t OGLFramebuffer::getHeight() const
    {
        return m_oglTexture->getHeight();
    }

    /**
    *
    */
    GLuint OGLFramebuffer::getHandle()
    {
        return m_fbo;
    }
}