#include <ISparkMaterial.hpp>
#include "Material.hpp"
#include "MaterialLibrary.hpp"

namespace spark::material {
    /**
    *
    */
    ISparkMaterial* MaterialLibrary::getDefaultMaterial()
    {
        static DefaultMaterial defaultMaterial;
        return &defaultMaterial;
    }

    /**
    *
    */
    DefaultMaterial::DefaultMaterial() : Material(spark::material::RenderMode::Default)
    {
    }
}