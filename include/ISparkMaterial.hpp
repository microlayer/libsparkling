#ifndef __SPARK_MATERIAL_ISPARKMATERIAL_HPP_INCLUDED__
#define __SPARK_MATERIAL_ISPARKMATERIAL_HPP_INCLUDED__

#include "SparkRefCount.hpp"

namespace spark::material {
    /**
    *
    */
    enum class VertexLayout : uint32_t {
        Indexed,
        NonIndexed
    };

    /**
    *
    */
    enum class RenderMode {
        Default,
        Wireframe,
        DebugVisualizationBarycentric,
        DebugVisualizationNormals
    };

    /**
    *
    */
    class ISparkMaterial : public spark::SparkRefCount
    {
    public:
        virtual ~ISparkMaterial() = default;
        virtual RenderMode getRenderMode() const = 0;
        virtual VertexLayout getRequiredMeshVariant() const = 0;
    };
}
#endif