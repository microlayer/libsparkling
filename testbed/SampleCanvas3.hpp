/**
*
*/
class SampleCanvas3 : public spark::ui::AbstractCanvas
{
public:
    /**
    *
    */
    SampleCanvas3(spark::device::ISparkDevice* device) :
        m_device(device)
    {
        m_sceneGraphManager3D = device->createSceneGraphManager3D();

        spark::SparkSharedPointer<spark::geometry::pointcloud::ISparkPointCloud> pointCloud = device->getFileSystem()->loadPointCloud("building.ply");

        // Create SceneNode
        spark::SparkSharedPointer<spark::scene::ISparkSceneNode> node = new spark::scene::SceneNode();
        node->attachPointCloud(pointCloud.get());

        m_sceneGraphManager3D->rootNode()->addChildSceneNode(node.get());
    }

    /**
    *
    */
    virtual ~SampleCanvas3()
    {

    }

    /**
    *
    */
    void init()
    {
        m_device->getLogger()->info("Init Canvas3");
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