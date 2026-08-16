#include "SpotLightNode.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    SpotLightNode::SpotLightNode()
    {
    }

    /**
    *
    */
    SpotLightNode::~SpotLightNode()
    {
    }

    /**
    *
    */
    void SpotLightNode::setRange(real32 range)
    {
        m_range = range;
    }

    /**
    *
    */
    real32 SpotLightNode::getRange() const
    {
        return m_range;
    }

    /**
    *
    */
    void SpotLightNode::setDirection(spark::math::Vector3f direction)
    {
        m_lightDirection = direction;
    }

    /**
    *
    */
    spark::math::Vector3f SpotLightNode::getDirection() const
    {
        return m_lightDirection;
    }

    /**
    *
    */
    void SpotLightNode::setAngle(real32 angle)
    {
        m_angle = angle;
    }

    /**
    *
    */
    real32 SpotLightNode::getAngel() const
    {
        return m_angle;
    }

    /**
    *
    */
    LightType SpotLightNode::getLightType()
    {
        return spark::scene::nodes::LightType::Spot;
    }

    /**
    *
    */
    spark::math::Matrix4f SpotLightNode::getLightViewProjectionMatrix()
    {
        spark::math::Matrix4f m;

        return m;
    }

    /**
    *
    */
    bool SpotLightNode::castsShadows()
    {
        return true;
    }

    /**
    *
    */
    void SpotLightNode::render(spark::renderer::ISparkRenderer* renderer)
    {

    }
}