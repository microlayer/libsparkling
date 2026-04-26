#ifndef __SPARK_SCENE_NODES_DIRECTIONALLIGHTNODE_HPP_INCLUDED__
#define __SPARK_SCENE_NODES_DIRECTIONALLIGHTNODE_HPP_INCLUDED__

#include "scene/nodes/LightNode.hpp"
#include "ISparkDirectionalLightNode.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    class DirectionalLightNode : public spark::scene::nodes::LightNode, public  spark::scene::nodes::ISparkDirectionalLightNode
    {
    public:
        DirectionalLightNode();
        virtual ~DirectionalLightNode();

    public:
        void setDirection(spark::math::Vector3f lightDirection) override;

    public:
        void render(spark::renderer::ISparkRenderer* renderer) override;
    };
}
#endif