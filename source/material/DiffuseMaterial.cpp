#include "DiffuseMaterial.hpp"

namespace spark::material {
    /**
    *
    */
    DiffuseMaterial::DiffuseMaterial() :
        Material(spark::material::RenderMode::DIFFUSE)
    {

    }

    /**
    *
    */
    DiffuseMaterial::~DiffuseMaterial()
    {

    }

    /**
    *
    */
    void DiffuseMaterial::apply(spark::renderer::shader::ISparkShader* shader) const
    {
        shader->setDrawMode(6);
        shader->setAlbedo(Material::getAlbedo());
    }
}