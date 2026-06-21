#include "DirectionalLightNode.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    DirectionalLightNode::DirectionalLightNode()
    {
    }

    /**
    *
    */
    DirectionalLightNode::~DirectionalLightNode()
    {
    }

    /**
    *
    */
    void DirectionalLightNode::setDirection(spark::math::Vector3f lightDirection)
    {
        m_lightDirection = lightDirection;
    }

    /**
    *
    */
    spark::math::Vector3f DirectionalLightNode::getDirection()
    {
        return m_lightDirection;
    }

    /**
    *
    */
    LightType DirectionalLightNode::getLightType()
    {
        return spark::scene::nodes::LightType::Directional;
    }

    /**
    *
    */
    void DirectionalLightNode::render(spark::renderer::ISparkRenderer* renderer)
    {

    }
}