#include "scene/SceneNode.hpp"

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

        /**
        *
        */
        void SceneNode::attachMesh(spark::mesh::ISparkMesh* mesh)
        {

        }
    }
}