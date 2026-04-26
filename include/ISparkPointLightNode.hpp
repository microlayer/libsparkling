#ifndef __SPARK_SCENE_ISPARKPOINTLIGHTNODE_HPP_INCLUDED__
#define __SPARK_SCENE_ISPARKPOINTLIGHTNODE_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkSceneNode.hpp"

namespace spark::scene {
    /**
    *
    */
    class ISparkPointLightNode : public virtual ISparkLightNode
    {
    public:
        virtual void setRange(real32 range) = 0;
    };
}
#endif