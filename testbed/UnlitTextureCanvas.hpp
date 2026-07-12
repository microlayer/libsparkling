/**
*
*/
#pragma once
class UnlitTextureCanvas : public spark::ui::AbstractCanvas
{
public:
    UnlitTextureCanvas(spark::device::ISparkDevice* device) :
        m_device(device)
    {
        // Create SceneGraphManager3D                
        m_sceneGraphManager3D = device->createSceneGraphManager3D();

        // Create Texture
        m_texture = m_device->getAssetManager()->loadTexture("file://texture2.png");

        // Material
        m_material = m_device->getRenderer()->createUnlitMaterial();
        m_material->setAlbedoTexture(m_texture.get());
        m_material->setAlbedo(spark::math::Vector3f(1, 1, 1));

        // Camera
        m_camera = m_device->getRenderer()->createPerspectiveCamera();
        m_camera->setPosition(spark::math::Vector3f(0, 0, -15.00f));
        m_sceneGraphManager3D->setActiveCamera(m_camera.get());

        // Create Mesh
        spark::SparkSharedPointer<spark::geometry::mesh::ISparkMesh> cubeMesh(spark::geometry::mesh::generator::MeshGenerator::createQuadMesh());

        // Create Animator
        spark::SparkSharedPointer<spark::animator::ISparkNodeAnimator> nodeRotationAnimator = spark::animator::NodeRotationAnimator::create(spark::math::Vector3f(5, 100, 5));

        // Create SceneNode
        spark::SparkSharedPointer<spark::scene::nodes::ISparkMeshSceneNode> node = m_sceneGraphManager3D->createMeshSceneNode();
        node->setPosition(spark::math::Vector3f(0, 0, 0));
        //node->setRotation(spark::math::Vector3f(0, 0, 0));
        node->setMesh(cubeMesh.get());
        node->setScale(0.25, 0.25, 0.25);
        node->setMaterial(m_material.get());
        node->addAnimator(nodeRotationAnimator.get());

        m_sceneGraphManager3D->rootNode()->addChildSceneNode(node.get());
    }

    /**
    *
    */
    virtual ~UnlitTextureCanvas()
    {
        m_device->getLogger()->info("Deleting UnlitTextureCanvas");
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
    void paint(spark::renderer::ISparkRenderer* renderer)
    {
        m_sceneGraphManager3D->drawGraph(renderer);
    }


private:
    spark::device::ISparkDevice* m_device;
    spark::SparkSharedPointer<spark::scene::ISceneGraphManager3D> m_sceneGraphManager3D;
    spark::SparkSharedPointer<spark::scene::camera::ISparkPerspectiveCamera> m_camera;
    spark::SparkSharedPointer<spark::material::ISparkMaterial> m_material;
    spark::SparkSharedPointer<spark::renderer::ISparkTexture> m_texture;
};