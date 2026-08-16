#ifndef __SPARK_SCENE_NODES_SPOTLIGHTNODE_HPP_INCLUDED__
#define __SPARK_SCENE_NODES_SPOTLIGHTNODE_HPP_INCLUDED__

#include "scene/nodes/LightNode.hpp"
#include "ISparkSpotLightNode.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    class SpotLightNode : public spark::scene::nodes::LightNode, public spark::scene::nodes::ISparkSpotLightNode
    {
    public:
        SpotLightNode();
        virtual ~SpotLightNode();

    public:
        void setRange(real32 range) override;
        real32 getRange() const override;
        void setDirection(spark::math::Vector3f direction) override;
        spark::math::Vector3f getDirection() const override;
        void setAngle(real32 angle) override;
        real32 getAngel() const override;

    public:
        LightType getLightType() override;

    public:
        spark::math::Matrix4f getLightViewProjectionMatrix() override;
        bool castsShadows() override;

    public:
        void render(spark::renderer::ISparkRenderer* renderer) override;

    private:
        real32 m_range;
        spark::math::Vector3f m_lightDirection;
        real32 m_angle;
    };
}
#endif