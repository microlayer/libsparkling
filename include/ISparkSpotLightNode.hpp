#ifndef __SPARK_SCENE_NODES_ISPARKSPOTLIGHTNODE_HPP_INCLUDED__
#define __SPARK_SCENE_NODES_ISPARKSPOTLIGHTNODE_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkLightNode.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    class ISparkSpotLightNode : public virtual ISparkLightNode
    {
    public:
        virtual void setDirection(spark::math::Vector3f direction) = 0;
        virtual void setAngle(real32 angle) = 0;
    };
}
#endif