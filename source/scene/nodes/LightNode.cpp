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
    void LightNode::setLightColor(spark::math::Vector3f lightColor)
    {

    }

    /**
    *
    */
    void LightNode::setIntensity(real32 intensity)
    {

    }

    /**
    *
    */
    void LightNode::render(spark::renderer::ISparkRenderer* renderer)
    {
        renderer->setLightDirection(0, 0, 0);
        //renderer->setLightColor(/* default white */)
    }
}
