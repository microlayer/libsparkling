/**
*
*/
#pragma once
class ShadowMapCanvas : public spark::ui::AbstractCanvas
{
public:
    /**
    *
    */
    ShadowMapCanvas(spark::device::ISparkDevice* device) :
        m_device(device)
    {
        // Create SceneGraphManager3D                
        m_sceneGraphManager3D = device->createSceneGraphManager3D();
        m_sceneGraphManager3D->setShadowMappingEnabled(true);

        m_material = m_device->getRenderer()->createDiffuseMaterial();
        m_material->setAlbedo({ 0.0, 1.0, 1.0 });


        // Camera
        m_camera = m_device->getRenderer()->createPerspectiveCamera();
        m_camera->setPerspective(20.0f, m_device->getScreenResolution().m_ratio, 0.1f, 100.0f);
        m_camera->setPosition(spark::math::Vector3f(0, 2, 6.00f));
        m_camera->lookAt(spark::math::Vector3f(0, 0, 0), spark::math::Vector3f(0, 1, 0));
        m_sceneGraphManager3D->setActiveCamera(m_camera.get());

        // Create Mesh
        spark::SparkSharedPointer<spark::geometry::mesh::ISparkMesh> planeMesh(spark::geometry::mesh::generator::MeshGenerator::createPlaneMesh());
        spark::SparkSharedPointer<spark::geometry::mesh::ISparkMesh> cubeMesh(spark::geometry::mesh::generator::MeshGenerator::createQuadMesh());

        spark::SparkSharedPointer<spark::animator::ISparkNodeAnimator> nodeRotationAnimator = spark::animator::NodeRotationAnimator::create(spark::math::Vector3f(0, 30, 0));


        // Create SceneNode
        spark::SparkSharedPointer<spark::scene::nodes::ISparkMeshSceneNode> node1 = m_sceneGraphManager3D->createMeshSceneNode();
        node1->setPosition(spark::math::Vector3f(0, 0, 0));
        node1->setRotation(spark::math::Vector3f(0, 0, 0));
        node1->setMesh(planeMesh.get());
        node1->setMaterial(m_material.get());
        //node1->addAnimator(nodeRotationAnimator.get());

        spark::SparkSharedPointer<spark::scene::nodes::ISparkMeshSceneNode> node2 = m_sceneGraphManager3D->createMeshSceneNode();
        node2->setPosition(spark::math::Vector3f(0, 0.21f, 0));
        node2->setRotation(spark::math::Vector3f(0, 0, 0));
        node2->setMesh(cubeMesh.get());
        node2->setScale(0.25, 0.25, 0.25);
        node2->setMaterial(m_material.get());
        node2->addAnimator(nodeRotationAnimator.get());

        // Create Directional-Light
        spark::SparkSharedPointer<spark::scene::nodes::ISparkDirectionalLightNode> directionalLightNode = m_sceneGraphManager3D->createDirectionalLightNode();
        directionalLightNode->setIntensity(1.5);
        directionalLightNode->setLightColor(spark::drawing::Color(0, 255, 0, 255));
        directionalLightNode->setDirection(spark::math::Vector3f(1, -1, -1));

        m_sceneGraphManager3D->addLight(directionalLightNode.get());

        m_sceneGraphManager3D->rootNode()->addChildSceneNode(node1.get());
        m_sceneGraphManager3D->rootNode()->addChildSceneNode(node2.get());
    }

    /**
    *
    */
    virtual ~ShadowMapCanvas()
    {
        m_device->getLogger()->info("Deleting ShadowMapCanvas");
    }

    /**
    *
    */
    void init()
    {
    }

    /**
    *
    */
    void destroy()
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
    spark::SparkSharedPointer<spark::scene::camera::ISparkPerspectiveCamera> m_camera;
    spark::SparkSharedPointer<spark::material::ISparkMaterial> m_material;
};