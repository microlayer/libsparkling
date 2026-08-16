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
        virtual void setRange(real32 range) = 0;
        virtual real32 getRange() const = 0;
        virtual void setDirection(spark::math::Vector3f direction) = 0;
        virtual spark::math::Vector3f getDirection() const = 0;
        virtual void setAngle(real32 angle) = 0;
        virtual real32 getAngel() const = 0;
    };
}
#endif