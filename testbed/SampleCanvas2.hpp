/**
*
*/
#pragma once
class SampleCanvas2 : public spark::ui::AbstractCanvas
{
public:
    SampleCanvas2(spark::device::ISparkDevice* device) :
        m_device(device)
    {
        m_sceneGraphManager3D = device->createSceneGraphManager3D();

        // Material
        m_material = m_device->getRenderer()->createMaterial(spark::material::RenderMode::DebugVisualizationNormals);

        // Create Mesh
        spark::SparkSharedPointer<spark::geometry::mesh::ISparkMesh> mesh = device->getFileSystem()->loadMesh("teapot.obj");

        // Create Animator
        spark::SparkSharedPointer<spark::animator::NodeRotationAnimator> nodeRotationAnimaror = new spark::animator::NodeRotationAnimator(spark::math::Vector3f(0, 50, 0));

        // Create SceneNode
        spark::SparkSharedPointer<spark::scene::ISparkSceneNode> node = m_sceneGraphManager3D->createSceneNode();
        node->setPosition(spark::math::Vector3f(0, -1, -1));
        node->attachMesh(mesh.get());
        node->addAnimator(nodeRotationAnimaror.get());
        node->setMaterial(m_material.get());

        m_sceneGraphManager3D->rootNode()->addChildSceneNode(node.get());
    }

    /**
    *
    */
    virtual ~SampleCanvas2()
    {

    }

    /**
    *
    */
    void init()
    {
        m_device->getLogger()->info("Init Canvas2");
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
    spark::SparkSharedPointer<spark::material::ISparkMaterial> m_material;
};