#ifndef __SPARK_MATERIAL_ISPARKMATERIAL_HPP_INCLUDED__
#define __SPARK_MATERIAL_ISPARKMATERIAL_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "math/Vector3.hpp"

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
        DebugVisualizationNormals,
        DIFFUSE,
        PBR
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

    public: // PBR
        virtual void setAlbedo(spark::math::Vector3f albedo) = 0;
        virtual void setRoughness(spark::real32 roughness) = 0;
        virtual void setMetallic(spark::real32 metallic) = 0;
        virtual spark::math::Vector3f getAlbedo() const = 0;
        virtual spark::real32 getRoughness() const = 0;
        virtual spark::real32 getMetallic() const = 0;
    };
}
#endif