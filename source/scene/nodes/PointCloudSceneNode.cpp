#include "PointCloudSceneNode.hpp"
#include <ISparkRenderer.hpp>

namespace spark::scene::nodes {
    /**
    *
    */
    PointCloudSceneNode::PointCloudSceneNode() : m_pointCloud(NULL)
    {

    }

    /**
    *
    */
    PointCloudSceneNode::~PointCloudSceneNode()
    {
        if (m_pointCloud != NULL) m_pointCloud->release();
    }

    /**
    *
    */
    void PointCloudSceneNode::attachPointCloud(spark::geometry::pointcloud::ISparkPointCloud* pointCloud)
    {
        if (pointCloud != NULL)
        {
            pointCloud->addRef();
            m_pointCloud = pointCloud;
        }
    }

    /**
    *
    */
    spark::geometry::pointcloud::ISparkPointCloud* PointCloudSceneNode::getPointCloud()
    {
        return m_pointCloud;
    }

    /**
    *
    */
    void PointCloudSceneNode::render(spark::renderer::ISparkRenderer* renderer)
    {
        animate();
        renderer->setModelTransformation(m_modelTransformationMatrix);

        if (m_pointCloud != NULL)
        {
            renderer->renderPointCloud(m_pointCloud);
        }
    }
}