#include "Material.hpp"

namespace spark::material {
    /**
    *
    */
    Material::Material(RenderMode renderMode) :
        m_renderMode(renderMode)
    {
        if (m_renderMode == RenderMode::Wireframe || m_renderMode == RenderMode::DebugVisualizationBarycentric)
        {
            m_meshVariant = VertexLayout::NonIndexed;
        }
    }

    /**
    *
    */
    Material::~Material()
    {

    }

    /**
    *
    */
    RenderMode Material::getRenderMode() const
    {
        return m_renderMode;
    }

    /**
    *
    */
    VertexLayout Material::getRequiredMeshVariant() const
    {
        return m_meshVariant;
    }
}