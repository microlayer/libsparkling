#ifndef __SPARK_MATERIAL_ISPARKMATERIAL_HPP_INCLUDED__
#define __SPARK_MATERIAL_ISPARKMATERIAL_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "math/Vector3.hpp"
#include "ISparkShader.hpp"

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

    public:
        virtual void setAlbedo(spark::math::Vector3f albedo) = 0;
        virtual spark::math::Vector3f getAlbedo() const = 0;

    public:
        virtual void apply(spark::renderer::shader::ISparkShader* shader) const = 0;
    };
}
#endif