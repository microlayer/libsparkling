#ifndef __SPARK_SCENE_NODES_POINTCLOUDSCENENODE_HPP_INCLUDED__
#define __SPARK_SCENE_NODES_POINTCLOUDSCENENODE_HPP_INCLUDED__

#include "SceneNode.hpp"
#include <ISparkPointCloudSceneNode.hpp>

namespace spark::scene::nodes {
    /**
    *
    */
    class PointCloudSceneNode : public spark::scene::nodes::SceneNode, public spark::scene::nodes::ISparkPointCloudSceneNode
    {
    public:
        PointCloudSceneNode();
        virtual ~PointCloudSceneNode();

    public:
        void attachPointCloud(spark::geometry::pointcloud::ISparkPointCloud* pointCloud) override;
        spark::geometry::pointcloud::ISparkPointCloud* getPointCloud() override;
        virtual void render(spark::renderer::ISparkRenderer* renderer) override;

    private:
        spark::geometry::pointcloud::ISparkPointCloud* m_pointCloud;
    };
}
#endif