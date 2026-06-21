#ifndef __SPARK_MATERIAL_MATERIAL_HPP_INCLUDED__
#define __SPARK_MATERIAL_MATERIAL_HPP_INCLUDED__

#include "ISparkMaterial.hpp"
#include <math/Vector3.hpp>

namespace spark::material {
    /**
    *
    */
    class Material : public virtual spark::material::ISparkMaterial
    {
    public:
        Material(RenderMode renderMode);
        ~Material();

    public:
        RenderMode getRenderMode() const override;
        VertexLayout getRequiredMeshVariant() const override;

    public: // Used in Diffuse and PBR Lightning model
        void setAlbedo(spark::math::Vector3f albedo) override;
        spark::math::Vector3f getAlbedo() const override;

    public:
        void apply(spark::renderer::shader::ISparkShader* shader) const override;

    private:
        RenderMode m_renderMode = RenderMode::Default;
        VertexLayout m_meshVariant = VertexLayout::Indexed;

    private:
        spark::math::Vector3f m_albedo = { 1.0f, 1.0f, 1.0f };
    };
}
#endif