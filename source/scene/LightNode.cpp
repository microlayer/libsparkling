#include "scene/LightNode.hpp"

namespace spark::scene {
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
    void LightNode::setLight()
    {

    }

    /**
    *
    */
    void LightNode::render(spark::renderer::ISparkRenderer* renderer)
    {
        renderer->setLightDirection(0, 0, 0);
    }
}
