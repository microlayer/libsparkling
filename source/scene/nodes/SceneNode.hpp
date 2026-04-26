#ifndef __SPARK_SCENE_SCENENODE_HPP_INCLUDED__
#define __SPARK_SCENE_SCENENODE_HPP_INCLUDED__

#include "ISparkSceneNode.hpp"
#include <material/MaterialLibrary.hpp>
#include "ISparkMesh.hpp"
#include "ISparkPointCloud.hpp"
#include "math/Matrix4.hpp"

namespace spark::scene {
    /**
    *
    */
    class SceneNode : public virtual spark::scene::ISparkSceneNode
    {
    public:
        SceneNode();
        virtual ~SceneNode();

    public:
        bool isRootNode();
        void addChildSceneNode(spark::scene::ISparkSceneNode* node);
        std::vector<ISparkSceneNode*> getChildren();

    public:
        void setPosition(spark::math::Vector3f position);
        void setRotation(spark::math::Vector3f rotation);
        void setScale(const real32 x, const real32 y, const real32 z);

    public:
        void attachMesh(spark::geometry::mesh::ISparkMesh* mesh);
        spark::geometry::mesh::ISparkMesh* getMesh();

        void attachPointCloud(spark::geometry::pointcloud::ISparkPointCloud* pointCloud);
        spark::geometry::pointcloud::ISparkPointCloud* getPointCloud();

        void addAnimator(spark::animator::ISparkNodeAnimator* nodeAnimator);

    public:
        void render(spark::renderer::ISparkRenderer* renderer);

    private:
        void animate();

    public:
        void setMaterial(spark::material::ISparkMaterial* material);

    private:
        std::vector<ISparkSceneNode*> m_children;
        spark::math::Vector3f m_position;
        spark::math::Vector3f m_rotation;
        spark::geometry::mesh::ISparkMesh* m_mesh;
        spark::geometry::pointcloud::ISparkPointCloud* m_pointCloud;
        spark::math::Matrix4f m_modelTransformationMatrix;
        spark::animator::ISparkNodeAnimator* m_nodeAnimator;
        spark::material::ISparkMaterial* m_material;
    };
}
#endif