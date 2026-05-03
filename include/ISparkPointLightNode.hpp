#ifndef __SPARK_SCENE_NODES_ISPARKPOINTLIGHTNODE_HPP_INCLUDED__
#define __SPARK_SCENE_NODES_ISPARKPOINTLIGHTNODE_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkLightNode.hpp"

namespace spark::scene::nodes {
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