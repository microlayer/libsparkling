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
            m_children.clear();
            if (m_mesh != NULL) delete m_mesh;
        }

        /**
        *
        */
        void SceneNode::addChildSceneNode(spark::scene::SceneNode* node)
        {
            m_children.push_back(node);
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
        std::vector<SceneNode*> SceneNode::getChildren()
        {
            return m_children;
        }

        /**
        *
        */
        spark::mesh::ISparkMesh* SceneNode::getMesh()
        {
            return m_mesh;
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
            m_mesh = mesh;
            //m_mesh->addRef();
        }
    }
}