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
        void setLightColor(spark::math::Vector3f lightColor) override;
        void setIntensity(real32 intensity) override;

    public:
        void render(spark::renderer::ISparkRenderer* renderer) override;

    private:
        spark::math::Vector3f m_light;
    };
}
#endif