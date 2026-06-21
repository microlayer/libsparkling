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
    void Material::setRoughness(spark::real32 roughness)
    {
        m_roughness = roughness;
    }

    /**
    *
    */
    void Material::setMetallic(spark::real32 metallic)
    {
        m_metallic = metallic;
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
    spark::real32 Material::getRoughness() const
    {
        return m_roughness;
    }

    /**
    *
    */
    spark::real32 Material::getMetallic() const
    {
        return m_metallic;
    }
}