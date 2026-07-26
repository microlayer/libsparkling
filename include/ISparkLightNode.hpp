#ifndef __SPARK_SCENE_NODES_ISPARKLIGHTNODE_HPP_INCLUDED__
#define __SPARK_SCENE_NODES_ISPARKLIGHTNODE_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkSceneNode.hpp"
#include "ISparkShadowMap.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    enum class LightType
    {
        Directional,
        Point
    };

    /**
    *
    */
    class ISparkLightNode : public virtual ISparkSceneNode
    {
    public:
        virtual void setLightColor(spark::drawing::Color lightColor) = 0;
        virtual spark::drawing::Color getLightColor() = 0;
        virtual void setIntensity(real32 intensity) = 0;
        virtual real32 getIntesity() = 0;
        virtual LightType getLightType() = 0;

        virtual void setShadowMap(spark::renderer::ISparkShadowMap* shadowMap) = 0;
        virtual spark::renderer::ISparkShadowMap* getShadowMap() = 0;

        virtual spark::math::Matrix4f getLightViewProjectionMatrix() = 0;
        virtual bool castsShadows() = 0;
    };
}
#endif