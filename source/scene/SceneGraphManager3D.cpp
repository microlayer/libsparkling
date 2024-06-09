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
        spark::scene::SceneNode* SceneGraphManager3D::rootNode()
        {
            return &m_rootNode;
        }        

        /**
        *
        */
        void SceneGraphManager3D::drawGraph(spark::renderer::ISparkRenderer* renderer)
        {
            //spark::mesh::ISparkMesh* mesh = m_rootNode.getChildren().at(0)->getMesh();
            //renderer->renderMesh(mesh);
        }
    }
}