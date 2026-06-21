#include "PBRMaterial.hpp"

namespace spark::material {
    /**
    *
    */
    PBRMaterial::PBRMaterial() :
        Material(spark::material::RenderMode::PBR)
    {

    }

    /**
    *
    */
    PBRMaterial::~PBRMaterial()
    {

    }

    /**
    *
    */
    void PBRMaterial::setRoughness(spark::real32 roughness)
    {
        m_roughness = roughness;
    }

    /**
    *
    */
    spark::real32 PBRMaterial::getRoughness() const
    {
        return m_roughness;
    }

    /**
    *
    */
    void PBRMaterial::setMetallic(spark::real32 metallic)
    {
        m_metallic = metallic;
    }

    /**
    *
    */
    spark::real32 PBRMaterial::getMetallic() const
    {
        return m_metallic;
    }

    /**
    *
    */
    void PBRMaterial::setAO(real32 ao)
    {
        m_ao = ao;
    }

    /**
    *
    */
    real32 PBRMaterial::getAO() const
    {
        return m_ao;
    }

    /**
    *
    */
    void PBRMaterial::apply(spark::renderer::shader::ISparkShader* shader) const
    {
        shader->setDrawMode(7);
        shader->setAlbedo(Material::getAlbedo());
        shader->setRoughness(getRoughness());
        shader->setMetallic(getMetallic());
    }
}