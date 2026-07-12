#ifndef __SPARK_MATERIAL_ISPARKUNLITMATERIAL_HPP_INCLUDED__
#define __SPARK_MATERIAL_ISPARKUNLITMATERIAL_HPP_INCLUDED__

#include "ISparkMaterial.hpp"

namespace spark::material {
    /**
    *
    */
    class ISparkUnlitMaterial : public virtual spark::material::ISparkMaterial
    {
    public:
        virtual ~ISparkUnlitMaterial() = default;
    };
}
#endif