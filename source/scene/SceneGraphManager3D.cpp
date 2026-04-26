#include "scene/SceneGraphManager3D.hpp"

namespace spark::scene {
    /**
    *
    */
    SceneGraphManager3D::SceneGraphManager3D(spark::renderer::ISparkRenderer* renderer,
        spark::device::ScreenResolution screenResolution,
        spark::log::ISparkLogger* logger)
        : m_renderer(renderer),
        m_screenResolution(screenResolution),
        m_logger(logger)
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
        spark::perspective::PerspectiveProjection perspectiveProjection;
        perspectiveProjection.m_aspect = m_screenResolution.m_ratio;
        perspectiveProjection.m_fovy = 45;
        perspectiveProjection.m_zFar = 100.0f;
        perspectiveProjection.m_zNear = 1.0f;
        m_renderer->setPerspectiveProjectionMatrix(perspectiveProjection);
    }

    /**
    *
    */
    void SceneGraphManager3D::setActiveCamera()
    {

    }

    /**
    *
    */
    void SceneGraphManager3D::drawGraph(spark::renderer::ISparkRenderer* renderer)
    {
        setDefaultCamera();
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
    spark::scene::nodes::ISparkSceneNode* SceneGraphManager3D::createSceneNode()
    {
        return new spark::scene::nodes::SceneNode();
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