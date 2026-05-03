#include "MeshSceneNode.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    MeshSceneNode::MeshSceneNode() : m_mesh(NULL)
    {

    }

    /**
    *
    */
    MeshSceneNode::~MeshSceneNode()
    {
        if (m_mesh != NULL) m_mesh->release();
    }

    /**
    *
    */
    void MeshSceneNode::attachMesh(spark::geometry::mesh::ISparkMesh* mesh)
    {

        if (mesh != NULL)
        {
            mesh->addRef();
            m_mesh = mesh;
        }
    }

    /**
    *
    */
    spark::geometry::mesh::ISparkMesh* MeshSceneNode::getMesh()
    {
        return m_mesh;
    }

    /**
    *
    */
    void MeshSceneNode::render(spark::renderer::ISparkRenderer* renderer)
    {
        animate();
        renderer->setModelTransformation(m_modelTransformationMatrix);

        if (m_mesh != NULL)
        {
            renderer->renderMesh(m_mesh, m_material);
        }
    }
}