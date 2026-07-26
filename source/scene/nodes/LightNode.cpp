#include "LightNode.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    LightNode::LightNode()
    {

    }

    /**
    *
    */
    LightNode::~LightNode()
    {
        if (m_shadowMap != NULL)
        {
            m_shadowMap->release();
        }
    }

    /**
    *
    */
    void LightNode::setLightColor(spark::drawing::Color lightColor)
    {
        m_lightColor = lightColor;
    }

    /**
    *
    */
    spark::drawing::Color LightNode::getLightColor()
    {
        return m_lightColor;
    }

    /**
    *
    */
    void LightNode::setIntensity(real32 intensity)
    {
        m_intensity = intensity;
    }

    /**
    *
    */
    real32 LightNode::getIntesity()
    {
        return m_intensity;
    }

    /**
    *
    */
    void LightNode::setShadowMap(spark::renderer::ISparkShadowMap* shadowMap)
    {
        m_shadowMap = shadowMap;
    }

    /**
    *
    */
    spark::renderer::ISparkShadowMap* LightNode::getShadowMap()
    {
        return m_shadowMap;
    }

    /**
    *
    */
    void LightNode::render(spark::renderer::ISparkRenderer* renderer)
    {

    }
}
