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
    void Material::apply(spark::renderer::shader::ISparkShader* shader) const
    {

    }
}