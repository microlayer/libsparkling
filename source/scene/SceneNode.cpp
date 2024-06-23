#include "scene/SceneNode.hpp"

namespace spark {
    namespace scene {

        /**
        *
        */
        SceneNode::SceneNode() :
            m_mesh(NULL)
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
        bool SceneNode::isRootNode()
        {
            return false;
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
        std::vector<ISparkSceneNode*> SceneNode::getChildren()
        {
            return m_children;
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
        void SceneNode::setRotation(spark::math::Vector3f rotation)
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
        void SceneNode::addAnimator()
        {

        }

        /**
        *
        */
        void SceneNode::render(spark::renderer::ISparkRenderer* renderer)
        {
            animate();
            renderer->setModelTransformation(m_modelTransformationMatrix);
            renderer->renderMesh(m_mesh);
        }

        /**
        *
        */
        void SceneNode::animate()
        {
            m_rotation.m_x += 0.0001;
            if (m_rotation.m_x > 0.01)
            {
                m_rotation.m_x = 0;
            }
            m_modelTransformationMatrix = m_modelTransformationMatrix.setRotation(m_rotation);
        }
    }
}