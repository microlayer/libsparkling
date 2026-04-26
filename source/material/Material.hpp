#ifndef __SPARK_MATERIAL_MATERIAL_HPP_INCLUDED__
#define __SPARK_MATERIAL_MATERIAL_HPP_INCLUDED__

#include "ISparkMaterial.hpp"
#include <math/Vector3.hpp>

namespace spark::material {
    /**
    *
    */
    class Material : public spark::material::ISparkMaterial
    {
    public:
        Material(RenderMode renderMode);
        ~Material();

    public:
        RenderMode getRenderMode() const;
        VertexLayout getRequiredMeshVariant() const;

    private:
        RenderMode m_renderMode = RenderMode::Default;
        VertexLayout m_meshVariant = VertexLayout::Indexed;

    private: // PBR Core
        spark::math::Vector3f m_albedo = { 1.0f, 1.0f, 1.0f };
        real32 m_metallic = 0.0f;
        real32 m_roughness = 1.0f;
        real32 m_ao = 1.0f;
    };
}
#endif