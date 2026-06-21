#ifndef __SPARK_MATERIAL_ISPARKPBRMATERIAL_HPP_INCLUDED__
#define __SPARK_MATERIAL_ISPARKPBRMATERIAL_HPP_INCLUDED__

#include "ISparkMaterial.hpp"

namespace spark::material {
    /**
    *
    */
    class ISparkPBRMaterial : public virtual spark::material::ISparkMaterial
    {
    public:
        virtual ~ISparkPBRMaterial() = default;

        virtual void setRoughness(real32) = 0;
        virtual real32 getRoughness() const = 0;

        virtual void setMetallic(real32) = 0;
        virtual real32 getMetallic() const = 0;

        virtual void setAO(real32) = 0;
        virtual real32 getAO() const = 0;
    };
}
#endif