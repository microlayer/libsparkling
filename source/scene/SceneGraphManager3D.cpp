#include "scene/SceneGraphManager3D.hpp"

namespace spark::scene {
    /**
    *
    */
    SceneGraphManager3D::SceneGraphManager3D(
        spark::renderer::ISparkRenderer* renderer,
        spark::device::ScreenResolution screenResolution,
        spark::log::ISparkLogger* logger) : m_renderer(renderer),
        m_screenResolution(screenResolution),
        m_logger(logger),
        m_activeCamera(NULL),
        m_defaultCamera(screenResolution.m_ratio)
    {
        //m_renderer->setLightDirection(0.0, 0.0, -1.0); // Currently not used
        m_renderer->setDrawMode(0);
    }

    /**
    *
    */
    SceneGraphManager3D::~SceneGraphManager3D()
    {

    }

    /**
    *
    */
    spark::scene::nodes::ISparkSceneNode* SceneGraphManager3D::rootNode()
    {
        return &m_rootNode;
    }

    /**
    *
    */
    void SceneGraphManager3D::setDefaultCamera()
    {
        m_renderer->setPerspectiveProjectionMatrix(m_defaultCamera.getProjectionViewMatrix());
    }

    /**
    *
    */
    void SceneGraphManager3D::setActiveCamera(spark::scene::camera::ISparkPerspectiveCamera* camera)
    {
        m_activeCamera = camera;
    }

    /**
    *
    */
    void SceneGraphManager3D::drawGraph(spark::renderer::ISparkRenderer* renderer)
    {
        applyCamera();

        onBeforeDrawGraph();

        if (!m_rootNode.getChildren().empty())
        {
            for (spark::scene::nodes::ISparkSceneNode* node : m_rootNode.getChildren())
            {
                if (node)
                {
                    node->render(renderer);
                }
            }
        }

        onAfterDrawGraph();
    }

    /**
    *
    */
    void SceneGraphManager3D::applyCamera()
    {
        if (m_activeCamera == NULL)
        {
            setDefaultCamera();
        }
        else
        {
            auto projectionViewMatrix = m_activeCamera->getProjectionViewMatrix();
            m_renderer->setPerspectiveProjectionMatrix(projectionViewMatrix);
        }
    }

    /**
    *
    */
    void SceneGraphManager3D::onBeforeDrawGraph()
    {
        m_renderer->activateDepthTest(true);
    }

    /**
    *
    */
    void SceneGraphManager3D::onAfterDrawGraph()
    {
        m_renderer->flush3DLines();

        m_renderer->activateDepthTest(false);
        m_renderer->setDrawMode(0);
    }

    /**
    *
    */
    spark::scene::camera::ISparkPerspectiveCamera* SceneGraphManager3D::createPerspectiveCamera()
    {
        return new spark::scene::camera::PerspectiveCamera(m_screenResolution.m_ratio);
    }

    /**
    *
    */
    spark::scene::nodes::ISparkMeshSceneNode* SceneGraphManager3D::createMeshSceneNode()
    {
        return new spark::scene::nodes::MeshSceneNode();
    }

    /**
    *
    */
    spark::scene::nodes::ISparkPointCloudSceneNode* SceneGraphManager3D::createPointCloudSceneNode()
    {
        return new spark::scene::nodes::PointCloudSceneNode();
    }

    /**
    *
    */
    spark::scene::nodes::ISparkCoordinateSystemNode* SceneGraphManager3D::createCoordinateSystemNode()
    {
        return new spark::scene::nodes::CoordinateSystemNode();
    }

    /**
    *
    */
    spark::scene::nodes::ISparkDirectionalLightNode* SceneGraphManager3D::createDirectionalLightNode()
    {
        return new spark::scene::nodes::DirectionalLightNode();
    }
}