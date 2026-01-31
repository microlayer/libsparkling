#ifndef __SPARK_MATERIAL_MATERIALLIBRARY_HPP_INCLUDED__
#define __SPARK_MATERIAL_MATERIALLIBRARY_HPP_INCLUDED__

#include "ISparkMaterial.hpp"

namespace spark::material {

    /**
    *
    */
    class DefaultMaterial : public spark::material::Material
    {
    public:
        DefaultMaterial();
    };

    /**
    *
    */
    class MaterialLibrary {
    public:
        static ISparkMaterial* getDefaultMaterial();
    };
}
#endif