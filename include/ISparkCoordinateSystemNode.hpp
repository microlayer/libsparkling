#ifndef __SPARK_SCENE_ISPARKCOORDINATESYSTEMNODE_HPP_INCLUDED__
#define __SPARK_SCENE_ISPARKCOORDINATESYSTEMNODE_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkSceneNode.hpp"

namespace spark::scene {
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