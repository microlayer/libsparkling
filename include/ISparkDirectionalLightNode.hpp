#ifndef __SPARK_SCENE_ISPARKDIRECTIONALLIGHTNODE_HPP_INCLUDED__
#define __SPARK_SCENE_ISPARKDIRECTIONALLIGHTNODE_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkSceneNode.hpp"

namespace spark::scene {
    /**
    *
    */
    class ISparkDirectionalLightNode : public virtual ISparkLightNode
    {
    public:
        virtual void setDirection(spark::math::Vector3f lightDirection) = 0;
    };
}
#endif