#ifndef __SPARK_SCENE_NODES_POINTLIGHTNODE_HPP_INCLUDED__
#define __SPARK_SCENE_NODES_POINTLIGHTNODE_HPP_INCLUDED__

#include "scene/nodes/LightNode.hpp"
#include "ISparkPointLightNode.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    class PointLightNode : public spark::scene::nodes::LightNode, public spark::scene::nodes::ISparkPointLightNode
    {
    public:
        PointLightNode();
        virtual ~PointLightNode();

    public:
        void setRange(real32 range) override;
        real32 getRange() const override;

    public:
        LightType getLightType() override;

    public:
        void render(spark::renderer::ISparkRenderer* renderer) override;

    private:
        real32 m_range;
    };
}
#endif