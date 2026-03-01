#include "scene/CoordinateSystemNode.hpp"

namespace spark::scene {
    /**
    *
    */
    CoordinateSystemNode::CoordinateSystemNode()
    {

    }

    /**
    *
    */
    CoordinateSystemNode::~CoordinateSystemNode()
    {

    }

    /**
    *
    */
    void CoordinateSystemNode::setClamp()
    {

    }

    /**
    *
    */
    void CoordinateSystemNode::render(spark::renderer::ISparkRenderer* renderer)
    {
        // X-Axis
        renderer->draw3DLine(math::Vector3f(0, 0, 0), math::Vector3f(1, 0, 0), spark::drawing::Color(255, 0, 0, 255));
        // Y-Axis
        renderer->draw3DLine(math::Vector3f(0, 0, 0), math::Vector3f(0, 1, 0), spark::drawing::Color(0, 255, 0, 255));
        // Z-Axis
        renderer->draw3DLine(math::Vector3f(0, 0, 0), math::Vector3f(0, 0, 1), spark::drawing::Color(0, 0, 255, 255));
    }
}
