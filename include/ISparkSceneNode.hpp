#ifndef __SPARK_SCENE_ISPARKSCENENODE_HPP_INCLUDED__
#define __SPARK_SCENE_ISPARKSCENENODE_HPP_INCLUDED__

#include "SparkRefCount.hpp"

namespace spark {
    namespace scene {
        /**
        *
        */
        class ISparkSceneNode : public virtual SparkRefCount
        {
        public:
            virtual void setPosition(spark::math::Vector3f position) = 0;
            virtual void attachMesh(spark::mesh::ISparkMesh* mesh) = 0;
            virtual spark::mesh::ISparkMesh* getMesh() = 0;
        };
    }
}
#endif