#ifndef __SPARK_SCENE_NODES_ISPARKPOINTCLOUDSCENENODE_HPP_INCLUDED__
#define __SPARK_SCENE_NODES_ISPARKPOINTCLOUDSCENENODE_HPP_INCLUDED__

#include "ISparkSceneNode.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    class ISparkPointCloudSceneNode : public virtual ISparkSceneNode
    {
    public:
        virtual void attachPointCloud(spark::geometry::pointcloud::ISparkPointCloud* pointCloud) = 0;
        virtual spark::geometry::pointcloud::ISparkPointCloud* getPointCloud() = 0;
    };
}
#endif