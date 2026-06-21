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

        // Material
        m_material = m_device->getRenderer()->createMaterial(spark::material::RenderMode::DIFFUSE);
        m_material->setAlbedo({ 1.0, 0.5, 0.0 });   // DIFFUSE only
        //m_material->setRoughness(0.3);            // PBR only
        //m_material->setMetallic(0.3);             // PBR only

        m_camera = m_device->getRenderer()->createPerspectiveCamera();
        m_camera->setPerspective(20.0f, m_device->getScreenResolution().m_ratio, 0.1f, 100.0f);
        m_camera->setPosition(spark::math::Vector3f(0, 2, 5.00f));
        m_camera->lookAt(spark::math::Vector3f(0, 0, 0), spark::math::Vector3f(0, 1, 0));
        m_sceneGraphManager3D->setActiveCamera(m_camera.get());

        // Create Mesh
        spark::SparkSharedPointer<spark::geometry::mesh::ISparkMesh> planeMesh(spark::geometry::mesh::generator::MeshGenerator::createPlaneMesh());
        spark::SparkSharedPointer<spark::geometry::mesh::ISparkMesh> cubeMesh(spark::geometry::mesh::generator::MeshGenerator::createQuadMesh());

        // Create Animator
        spark::SparkSharedPointer<spark::animator::ISparkNodeAnimator> nodeRotationAnimator = spark::animator::NodeRotationAnimator::create(spark::math::Vector3f(0, 30, 0));

        
        // Create SceneNode
        spark::SparkSharedPointer<spark::scene::nodes::ISparkMeshSceneNode> node1 = m_sceneGraphManager3D->createMeshSceneNode();
        node1->setPosition(spark::math::Vector3f(0, 0, 0));
        node1->setRotation(spark::math::Vector3f(0, 0, 0));
        node1->setMesh(planeMesh.get());
        node1->setMaterial(m_material.get());
        node1->addAnimator(nodeRotationAnimator.get());

        spark::SparkSharedPointer<spark::scene::nodes::ISparkMeshSceneNode> node2 = m_sceneGraphManager3D->createMeshSceneNode();
        node2->setPosition(spark::math::Vector3f(0, -0.251f, 0));
        node2->setRotation(spark::math::Vector3f(0, 0, 0));
        node2->setMesh(cubeMesh.get());
        node2->setScale(0.5, 0.25, 0.5);
        //node2->setMaterial(m_material.get());
        

        // Create Directional-Light
        spark::SparkSharedPointer<spark::scene::nodes::ISparkDirectionalLightNode> directionalLightNode = m_sceneGraphManager3D->createDirectionalLightNode();
        //directionalLightNode->setPosition(spark::math::Vector3f(0, -1, 0)); // Not needed in directional light
        directionalLightNode->setIntensity(0.5);
        directionalLightNode->setLightColor(spark::drawing::Color(0, 255, 0, 255));
        directionalLightNode->setDirection(spark::math::Vector3f(-1, -1, 0));
        
        // Create Point-Light
        spark::SparkSharedPointer<spark::scene::nodes::ISparkPointLightNode> pointLightNode = m_sceneGraphManager3D->createPointLightNode();
        pointLightNode->setPosition(spark::math::Vector3f(0, -1, 0));
        pointLightNode->setIntensity(2);
        pointLightNode->setLightColor(spark::drawing::Color(255, 242, 230, 255));
        pointLightNode->setRange(5.0);       
        
        m_sceneGraphManager3D->addLight(directionalLightNode.get());
        m_sceneGraphManager3D->addLight(pointLightNode.get());

        m_sceneGraphManager3D->rootNode()->addChildSceneNode(node1.get());
        m_sceneGraphManager3D->rootNode()->addChildSceneNode(node2.get());
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
    spark::SparkSharedPointer<spark::scene::camera::ISparkPerspectiveCamera> m_camera;
    spark::SparkSharedPointer<spark::material::ISparkMaterial> m_material;
};