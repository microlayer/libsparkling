#ifndef __SPARK_SCENE_NODES_ISPARKDIRECTIONALLIGHTNODE_HPP_INCLUDED__
#define __SPARK_SCENE_NODES_ISPARKDIRECTIONALLIGHTNODE_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkLightNode.hpp"

namespace spark::scene::nodes {
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