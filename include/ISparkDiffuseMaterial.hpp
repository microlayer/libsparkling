#ifndef __SPARK_MATERIAL_ISPARKDIFFUSEMATERIAL_HPP_INCLUDED__
#define __SPARK_MATERIAL_ISPARKDIFFUSEMATERIAL_HPP_INCLUDED__

#include "ISparkMaterial.hpp"

namespace spark::material {
    /**
    *
    */
    class ISparkDiffuseMaterial : public virtual spark::material::ISparkMaterial
    {
    public:
        virtual ~ISparkDiffuseMaterial() = default;
    };
}
#endif