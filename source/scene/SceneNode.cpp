#include "scene/SceneNode.hpp"

namespace spark {
    namespace scene {

        /**
        *
        */
        SceneNode::SceneNode() :
            m_mesh(NULL),
            m_nodeAnimator(NULL)
        {
            m_material = spark::material::MaterialLibrary::getDefaultMaterial();
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
            if (m_nodeAnimator != NULL) m_nodeAnimator->release();
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
            m_position = position;
            m_modelTransformationMatrix.setTranslation(position);
        }

        /**
        *
        */
        void SceneNode::setRotation(spark::math::Vector3f rotation)
        {
            m_rotation = rotation;
            m_modelTransformationMatrix.setRotation(rotation);
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
        void SceneNode::addAnimator(spark::animator::ISparkNodeAnimator* nodeAnimator)
        {
            nodeAnimator->addRef();
            m_nodeAnimator = nodeAnimator;
        }

        /**
        *
        */
        void SceneNode::render(spark::renderer::ISparkRenderer* renderer)
        {
            animate();
            renderer->setModelTransformation(m_modelTransformationMatrix);
            renderer->renderMesh(m_mesh, m_material);
        }

        /**
        *
        */
        void SceneNode::animate()
        {
            m_nodeAnimator->animate(this);
        }

        /**
        *
        */
        void SceneNode::setMaterial(spark::material::ISparkMaterial* material)
        {
            m_material = material;
        }
    }
}