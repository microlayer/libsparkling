#include "scene/SceneGraphManager3D.hpp"

namespace spark {
    namespace scene {
        /**
        *
        */
        SceneGraphManager3D::SceneGraphManager3D()
        {

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
        void SceneGraphManager3D::setActiveCamera()
        {

        }

        /**
        *
        */
        void SceneGraphManager3D::drawGraph(spark::renderer::ISparkRenderer* renderer)
        {
            //spark::mesh::ISparkMesh* mesh = m_rootNode.getMesh();
            spark::scene::ISparkSceneNode* node = m_rootNode.getChildren().at(0);
            spark::mesh::ISparkMesh* mesh = node->getMesh();
            node->render(renderer);
        }
    }
}