#ifndef __SPARK_SCENE_NODES_SCENENODE_HPP_INCLUDED__
#define __SPARK_SCENE_NODES_SCENENODE_HPP_INCLUDED__

#include "ISparkSceneNode.hpp"
#include "material/MaterialLibrary.hpp"
#include "math/Matrix4.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    class SceneNode : public virtual spark::scene::nodes::ISparkSceneNode
    {
    public:
        SceneNode();
        virtual ~SceneNode();

    public:
        bool isRootNode();
        void addChildSceneNode(spark::scene::nodes::ISparkSceneNode* node);
        std::vector<ISparkSceneNode*> getChildren();

    protected:
        void setPosition(spark::math::Vector3f position);
        void setRotation(spark::math::Vector3f rotation);
        void setScale(const real32 x, const real32 y, const real32 z);

    protected:
        void addAnimator(spark::animator::ISparkNodeAnimator* nodeAnimator);

    protected:
        void render(spark::renderer::ISparkRenderer* renderer);

    protected:
        void animate();

    protected:
        void setMaterial(spark::material::ISparkMaterial* material);

    protected:
        std::vector<ISparkSceneNode*> m_children;
        spark::math::Vector3f m_position;
        spark::math::Vector3f m_rotation;
        spark::math::Matrix4f m_modelTransformationMatrix;
        spark::animator::ISparkNodeAnimator* m_nodeAnimator;
        spark::material::ISparkMaterial* m_material;
    };
}
#endif