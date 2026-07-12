#include "UnlitMaterial.hpp"

namespace spark::material {
    /**
    *
    */
    UnlitMaterial::UnlitMaterial() :
        Material(spark::material::RenderMode::UNLIT)
    {

    }

    /**
    *
    */
    UnlitMaterial::~UnlitMaterial()
    {

    }

    /**
    *
    */
    void UnlitMaterial::apply(spark::renderer::shader::ISparkShader* shader) const
    {
        shader->setDrawMode(6);

        Material::apply(shader);
    }
}