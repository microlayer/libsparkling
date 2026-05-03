#ifndef __SPARK_SCENE_NODES_ISPARKSCENENODE_HPP_INCLUDED__
#define __SPARK_SCENE_NODES_ISPARKSCENENODE_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkRenderer.hpp"
#include "ISparkNodeAnimator.hpp"
#include "material/Material.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    class ISparkSceneNode : public virtual SparkRefCount
    {
    public:
        virtual bool isRootNode() = 0;
        virtual void addChildSceneNode(spark::scene::nodes::ISparkSceneNode* node) = 0;
        virtual std::vector<ISparkSceneNode*> getChildren() = 0;
        virtual void setPosition(spark::math::Vector3f position) = 0;
        virtual void setRotation(spark::math::Vector3f rotation) = 0;
        virtual void setScale(const real32 x, const real32 y, const real32 z) = 0;
        virtual void addAnimator(spark::animator::ISparkNodeAnimator* nodeAnimator) = 0;
        virtual void render(spark::renderer::ISparkRenderer* renderer) = 0;
        virtual void animate() = 0;

        // Material
        virtual void setMaterial(spark::material::ISparkMaterial* material) = 0;
    };
}
#endif