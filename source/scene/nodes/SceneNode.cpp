#include "SceneNode.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    SceneNode::SceneNode() :
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
    void SceneNode::addChildSceneNode(spark::scene::nodes::ISparkSceneNode* node)
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
        updateModelMatrix();
    }

    /**
    *
    */
    spark::math::Vector3f SceneNode::getPosition()
    {
        return m_position;
    }

    /**
    *
    */
    void SceneNode::setRotation(spark::math::Vector3f rotation)
    {
        m_rotation = rotation;
        updateModelMatrix();
    }

    /**
    *
    */
    spark::math::Vector3f SceneNode::getRotation()
    {
        return m_rotation;
    }

    /**
    *
    */
    void SceneNode::setScale(const real32 x, const real32 y, const real32 z)
    {
        /*spark::math::Matrix4f m;
        S.setScale(x, y, z);
        m_modelTransformationMatrix = m_modelTransformationMatrix * m;*/

        m_scale = { x,y,z };
        updateModelMatrix();
    }

    /**
    *
    */
    void SceneNode::updateModelMatrix()
    {
        spark::math::Matrix4f T;
        spark::math::Matrix4f R;
        spark::math::Matrix4f S;

        T.setTranslation(m_position);
        R.setRotation(m_rotation);
        S.setScale(m_scale.m_x, m_scale.m_y, m_scale.m_z);

        m_modelTransformationMatrix = T * R * S;
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

    }

    /**
    *
    */
    void SceneNode::animate()
    {
        if (m_nodeAnimator != NULL)
        {
            m_nodeAnimator->animate(this);
        }
    }

    /**
    *
    */
    void SceneNode::setMaterial(spark::material::ISparkMaterial* material)
    {
        m_material = material;
    }
}
