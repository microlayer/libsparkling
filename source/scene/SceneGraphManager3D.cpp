#include "scene/SceneGraphManager3D.hpp"

namespace spark {
    namespace scene {
        /**
        *
        */
        SceneGraphManager3D::SceneGraphManager3D(spark::renderer::ISparkRenderer* renderer,
            spark::device::ScreenResolution screenResolution,
            spark::log::ISparkLogger* logger)
            : m_renderer(renderer),
            m_screenResolution(screenResolution)
        {
            //m_renderer->setLightDirection(0.0, 0.0, -1.0); // Currently not used
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
        spark::scene::ISparkSceneNode* SceneGraphManager3D::rootNode()
        {
            return &m_rootNode;
        }

        /**
        *
        */
        void SceneGraphManager3D::setNormalVectorDebugVisualizationMode()
        {
            m_renderer->setDrawMode(3);
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
            renderer->activateDepthTest(true);

            //spark::mesh::ISparkMesh* mesh = m_rootNode.getMesh();
            spark::scene::ISparkSceneNode* node = m_rootNode.getChildren().at(0);
            spark::mesh::ISparkMesh* mesh = node->getMesh();
            node->render(renderer);
            renderer->activateDepthTest(false);
        }
    }
}