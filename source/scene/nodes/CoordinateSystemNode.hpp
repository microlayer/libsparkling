#ifndef __SPARK_SCENE_NODES_COORDINATESYSTEMNODE_HPP_INCLUDED__
#define __SPARK_SCENE_NODES_COORDINATESYSTEMNODE_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "scene/nodes/SceneNode.hpp"
#include "ISparkCoordinateSystemNode.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    class CoordinateSystemNode : public spark::scene::nodes::SceneNode, public  spark::scene::nodes::ISparkCoordinateSystemNode
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