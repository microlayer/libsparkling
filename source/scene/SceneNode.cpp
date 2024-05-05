#include "scene/SceneNode.hpp"
#include <math/Vector3.hpp>

namespace spark {
    namespace scene {

        /**
        *
        */
        SceneNode::SceneNode()
        {

        }

        /**
        *
        */
        SceneNode::~SceneNode()
        {

        }

        /**
        *
        */
        SceneNode* SceneNode::addChildSceneNode()
        {
            return NULL;
        }

        /**
        *
        */
        bool SceneNode::isRootNode()
        {
            return false;
        }

        /**
        *
        */
        void SceneNode::setPosition(spark::math::Vector3f position)
        {

        }
    }
}