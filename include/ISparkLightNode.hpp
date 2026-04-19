#ifndef __SPARK_SCENE_ISPARKLIGHTNODE_HPP_INCLUDED__
#define __SPARK_SCENE_ISPARKLIGHTNODE_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkSceneNode.hpp"

namespace spark::scene {
    /**
    *
    */
    class ISparkLightNode : public virtual ISparkSceneNode
    {
    public:
        virtual void setLight() = 0;
    };
}
#endif