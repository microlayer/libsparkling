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
    void LightNode::render(spark::renderer::ISparkRenderer* renderer)
    {

    }
}
