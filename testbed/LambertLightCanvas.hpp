#include <ISparkLightNode.hpp>

/**
*
*/
#pragma once
class LambertLightCanvas : public spark::ui::AbstractCanvas
{
public:
    /**
    *
    */
    LambertLightCanvas(spark::device::ISparkDevice* device) :
        m_device(device)
    {
        // Create SceneGraphManager3D
        m_sceneGraphManager3D = device->createSceneGraphManager3D();

        // Create Mesh
        spark::SparkSharedPointer<spark::geometry::mesh::ISparkMesh> cubeMesh(spark::geometry::mesh::generator::MeshGenerator::createQuadMesh());

        // Create SceneNode
        spark::SparkSharedPointer<spark::scene::ISparkSceneNode> node = m_sceneGraphManager3D->createSceneNode();
        node->setPosition(spark::math::Vector3f(0, 0, 0));
        node->attachMesh(cubeMesh.get());

        // Create Light
        spark::SparkSharedPointer<spark::scene::ISparkLightNode> lightNode = m_sceneGraphManager3D->createLightNode();

        m_sceneGraphManager3D->rootNode()->addChildSceneNode(node.get());
        m_sceneGraphManager3D->rootNode()->addChildSceneNode(lightNode.get());
    }

    /**
    *
    */
    virtual ~LambertLightCanvas()
    {

    }

    /**
    *
    */
    void init()
    {
        m_device->getLogger()->info("Init LambertLightCanvas");

        // Set virtual resolution
        spark::perspective::OrthographicProjection orthographicProjection(m_device->getScreenResolution().m_width, m_device->getScreenResolution().m_height);
        orthographicProjection.setVirtualResolution(1196, 720, spark::perspective::VirtualResolution::E_LETTER_OR_PILLARBOX);
        m_device->getRenderer()->setOrthographicProjectionMatrix(orthographicProjection);
    }

    /**
    *
    */
    void onKeyPressed()
    {

    }

    /**
    *
    */
    void paint(spark::renderer::ISparkRenderer* renderer)
    {
        m_sceneGraphManager3D->drawGraph(renderer);
    }

private:
    spark::device::ISparkDevice* m_device;
    spark::SparkSharedPointer<spark::scene::ISceneGraphManager3D> m_sceneGraphManager3D;
};