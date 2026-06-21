#ifndef __SPARK_SCENE_NODES_LIGHTNODE_HPP_INCLUDED__
#define __SPARK_SCENE_NODES_LIGHTNODE_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "scene/nodes/SceneNode.hpp"
#include "ISparkLightNode.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    class LightNode : public spark::scene::nodes::SceneNode, public virtual spark::scene::nodes::ISparkLightNode
    {
    public:
        LightNode();
        virtual ~LightNode();

    public:
        void setLightColor(spark::drawing::Color lightColor) override;
        spark::drawing::Color getLightColor() override;
        void setIntensity(real32 intensity) override;
        real32 getIntesity() override;

    public:
        virtual LightType getLightType() override = 0;

    public:
        void render(spark::renderer::ISparkRenderer* renderer) override;

    private:
        spark::drawing::Color m_lightColor;
        real32 m_intensity;
    };
}
#endif