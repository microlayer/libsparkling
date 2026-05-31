/**
*
*/
#pragma once
class PerspectiveCameraTestCanvas : public spark::ui::AbstractCanvas
{
public:
    /**
    *
    */
    PerspectiveCameraTestCanvas(spark::device::ISparkDevice* device) :
        m_device(device)
    {
        // Create SceneGraphManager3D
        m_sceneGraphManager3D = device->createSceneGraphManager3D();

        m_camera = m_sceneGraphManager3D->createPerspectiveCamera();
        m_camera->setPerspective(20.0f, m_device->getScreenResolution().m_ratio, 0.1f, 100.0f);
        m_camera->setPosition(spark::math::Vector3f(0, 0, 5.67f));
        m_camera->lookAt(spark::math::Vector3f(0, 0, 0), spark::math::Vector3f(0, 1, 0));
        m_sceneGraphManager3D->setActiveCamera(m_camera.get());

        // Create Mesh
        spark::SparkSharedPointer<spark::geometry::mesh::ISparkMesh> planeMesh(spark::geometry::mesh::generator::MeshGenerator::createPlaneMesh());

        // Create SceneNode
        spark::SparkSharedPointer<spark::scene::nodes::ISparkMeshSceneNode> node = m_sceneGraphManager3D->createMeshSceneNode();
        node->setPosition(spark::math::Vector3f(0, 0, -0));
        node->setRotation(spark::math::Vector3f(1.57f, 0, -0));
        node->attachMesh(planeMesh.get());

        m_sceneGraphManager3D->rootNode()->addChildSceneNode(node.get());
    }

    /**
    *
    */
    void init()
    {
        m_device->getLogger()->info("Init PerspectiveCameraTestCanvas");
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
    spark::SparkSharedPointer<spark::scene::camera::ISparkPerspectiveCamera> m_camera;
};