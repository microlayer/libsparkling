#include "Material.hpp"

namespace spark::material {
    /**
    *
    */
    Material::Material(RenderMode renderMode) :
        m_renderMode(renderMode)
    {
        if (m_renderMode == RenderMode::Wireframe || m_renderMode == RenderMode::DebugVisualizationBarycentric)
        {
            m_meshVariant = VertexLayout::NonIndexed;
        }
    }

    /**
    *
    */
    Material::~Material()
    {
        if (m_texture != NULL) m_texture->release();
    }

    /**
    *
    */
    RenderMode Material::getRenderMode() const
    {
        return m_renderMode;
    }

    /**
    *
    */
    VertexLayout Material::getRequiredMeshVariant() const
    {
        return m_meshVariant;
    }

    /**
    *
    */
    void Material::setAlbedo(spark::math::Vector3f albedo)
    {
        m_albedo = albedo;
    }

    /**
    *
    */
    spark::math::Vector3f Material::getAlbedo() const
    {
        return m_albedo;
    }

    /**
    *
    */
    void Material::setAlbedoTexture(spark::renderer::ISparkTexture* texture)
    {
        texture->addRef();
        m_texture = texture;
    }

    /**
    *
    */
    spark::renderer::ISparkTexture* Material::getAlbedoTexture() const
    {
        return m_texture;
    }

    /**
    *
    */
    void Material::apply(spark::renderer::shader::ISparkShader* shader) const
    {
        auto* albedoTex = Material::getAlbedoTexture();

        shader->setHasAlbedoTexture(albedoTex != nullptr);
        if (albedoTex)
        {
            albedoTex->bind(spark::renderer::TextureSlot::Albedo);
        }

        shader->setAlbedo(Material::getAlbedo());
    }
}