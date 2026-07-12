#ifndef __SPARK_MATERIAL_UNLITMATERIAL_HPP_INCLUDED__
#define __SPARK_MATERIAL_UNLITMATERIAL_HPP_INCLUDED__

#include "Material.hpp"
#include "ISparkUnlitMaterial.hpp"

namespace spark::material {
    /**
    *
    */
    class UnlitMaterial : public spark::material::Material, public spark::material::ISparkUnlitMaterial
    {
    public:
        UnlitMaterial();
        ~UnlitMaterial();

    public:
        void apply(spark::renderer::shader::ISparkShader* shader) const override;
    };
}
#endif