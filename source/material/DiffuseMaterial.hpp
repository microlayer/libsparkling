#ifndef __SPARK_MATERIAL_DIFFUSEMATERIAL_HPP_INCLUDED__
#define __SPARK_MATERIAL_DIFFUSEMATERIAL_HPP_INCLUDED__

#include "Material.hpp"
#include "ISparkDiffuseMaterial.hpp"

namespace spark::material {
    /**
    *
    */
    class DiffuseMaterial : public spark::material::Material, public spark::material::ISparkDiffuseMaterial
    {
    public:
        DiffuseMaterial();
        ~DiffuseMaterial();

    public:
        void apply(spark::renderer::shader::ISparkShader* shader) const override;
    };
}
#endif
