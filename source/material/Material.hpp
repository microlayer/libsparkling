#ifndef __SPARK_MATERIAL_MATERIAL_HPP_INCLUDED__
#define __SPARK_MATERIAL_MATERIAL_HPP_INCLUDED__

#include "ISparkMaterial.hpp"

namespace spark {
    namespace material {
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
        };
    }
}
#endif