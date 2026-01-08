/**
*
*/
class SampleCanvas2 : public spark::ui::AbstractCanvas
{
public:
    SampleCanvas2(spark::device::ISparkDevice* device) :
        m_device(device)
    {
        m_sceneGraphManager3D = device->createSceneGraphManager3D();
        m_sceneGraphManager3D->setNormalVectorDebugVisualizationMode();

        // Create Mesh
        spark::SparkSharedPointer<spark::mesh::ISparkMesh> mesh = device->getFileSystem()->loadMesh("teapot.obj");

        // Create Animator
        spark::SparkSharedPointer<spark::animator::NodeRotationAnimator> nodeRotationAnimaror = new spark::animator::NodeRotationAnimator(spark::math::Vector3f(0, 50, 0));

        // Create SceneNode
        spark::SparkSharedPointer<spark::scene::ISparkSceneNode> node = new spark::scene::SceneNode();
        node->setPosition(spark::math::Vector3f(0, -1, -3));
        node->attachMesh(mesh.get());
        node->addAnimator(nodeRotationAnimaror.get());

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
};