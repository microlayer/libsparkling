#ifndef __SPARK_MATERIAL_PBRMATERIAL_HPP_INCLUDED__
#define __SPARK_MATERIAL_PBRMATERIAL_HPP_INCLUDED__

#include "Material.hpp"
#include "ISparkPBRMaterial.hpp"

namespace spark::material {
    /**
    *
    */
    class PBRMaterial : public spark::material::Material, public spark::material::ISparkPBRMaterial
    {
    public:
        PBRMaterial();
        ~PBRMaterial();

    public:
        void setRoughness(spark::real32 roughness) override;
        spark::real32 getRoughness() const override;
        void setMetallic(spark::real32 metallic) override;
        spark::real32 getMetallic() const override;
        void setAO(real32 ao) override;
        real32 getAO() const override;

    public:
        void apply(spark::renderer::shader::ISparkShader* shader) const override;

    private:
        real32 m_metallic = 0.0f;
        real32 m_roughness = 1.0f;
        real32 m_ao = 1.0f;
    };
}
#endif