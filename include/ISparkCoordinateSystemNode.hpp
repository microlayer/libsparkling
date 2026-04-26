#ifndef __SPARK_SCENE_NODES_ISPARKCOORDINATESYSTEMNODE_HPP_INCLUDED__
#define __SPARK_SCENE_NODES_ISPARKCOORDINATESYSTEMNODE_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkSceneNode.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    class ISparkCoordinateSystemNode : public virtual ISparkSceneNode
    {
    public:
        virtual void setClamp() = 0;
    };
}
#endif