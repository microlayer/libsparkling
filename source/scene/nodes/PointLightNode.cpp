#include "PointLightNode.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    PointLightNode::PointLightNode()
    {
    }

    /**
    *
    */
    PointLightNode::~PointLightNode()
    {
    }

    /**
    *
    */
    void PointLightNode::setRange(real32 range)
    {
        m_range = range;
    }

    /**
    *
    */
    real32 PointLightNode::getRange() const
    {
        return m_range;
    }

    /**
    *
    */
    LightType PointLightNode::getLightType()
    {
        return spark::scene::nodes::LightType::Point;
    }

    /**
    *
    */
    spark::math::Matrix4f PointLightNode::getLightViewProjectionMatrix()
    {
        spark::math::Matrix4f m;

        return m;
    }

    /**
    *
    */
    bool PointLightNode::castsShadows()
    {
        return false;
    }

    /**
    *
    */
    void PointLightNode::render(spark::renderer::ISparkRenderer* renderer)
    {

    }
}