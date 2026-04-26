#ifndef __SPARK_SCENE_COORDINATESYSTEMNODE_HPP_INCLUDED__
#define __SPARK_SCENE_COORDINATESYSTEMNODE_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "scene/SceneNode.hpp"
#include "ISparkCoordinateSystemNode.hpp"

namespace spark::scene {
    /**
    *
    */
    class CoordinateSystemNode : public spark::scene::SceneNode, public  spark::scene::ISparkCoordinateSystemNode
    {
    public:
        CoordinateSystemNode();
        virtual ~CoordinateSystemNode();

    public:
        void setClamp() override;

    public:
        void render(spark::renderer::ISparkRenderer* renderer) override;
    };
}
#endif