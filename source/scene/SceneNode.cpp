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
            for (auto& node : m_children)
            {
                node->release();
            }
            m_children.clear();
            if (m_mesh != NULL) m_mesh->release();
        }

        /**
        *
        */
        void SceneNode::addChildSceneNode(spark::scene::ISparkSceneNode* node)
        {
            node->addRef();
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
        std::vector<ISparkSceneNode*> SceneNode::getChildren()
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
            mesh->addRef();
            m_mesh = mesh;            
        }
    }
}