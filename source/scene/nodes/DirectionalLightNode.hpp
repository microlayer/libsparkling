#ifndef __SPARK_SCENE_NODES_DIRECTIONALLIGHTNODE_HPP_INCLUDED__
#define __SPARK_SCENE_NODES_DIRECTIONALLIGHTNODE_HPP_INCLUDED__

#include "scene/nodes/LightNode.hpp"
#include "ISparkDirectionalLightNode.hpp"
#include "math/ProjectionMatrix.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    class DirectionalLightNode : public spark::scene::nodes::LightNode, public spark::scene::nodes::ISparkDirectionalLightNode
    {
    public:
        DirectionalLightNode();
        virtual ~DirectionalLightNode();

    public:
        void setDirection(spark::math::Vector3f lightDirection) override;
        spark::math::Vector3f getDirection() override;

    public:
        LightType getLightType() override;

    public:
        spark::math::Matrix4f getLightViewProjectionMatrix() override;
        bool castsShadows() override;

    public:
        void render(spark::renderer::ISparkRenderer* renderer) override;

    private:
        spark::math::Vector3f m_lightDirection;
    };
}
#endif