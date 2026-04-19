#ifndef __SPARK_SCENE_LIGHTNODE_HPP_INCLUDED__
#define __SPARK_SCENE_LIGHTNODE_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "scene/SceneNode.hpp"
#include "ISparkLightNode.hpp"

namespace spark::scene {
    /**
    *
    */
    class LightNode : public spark::scene::SceneNode, public  spark::scene::ISparkLightNode
    {
    public:
        LightNode();
        virtual ~LightNode();

    public:
        void setLight() override;

    public:
        void render(spark::renderer::ISparkRenderer* renderer) override;
    };
}
#endif