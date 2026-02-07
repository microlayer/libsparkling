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

        spark::SparkSharedPointer<spark::geometry::pointcloud::ISparkPointCloud> pointCloud = device->getFileSystem()->loadPointCloud("0036_Schuebel_bDOM.ply");

        // Create SceneNode
        spark::SparkSharedPointer<spark::scene::ISparkSceneNode> node = new spark::scene::SceneNode();
        node->setPosition(spark::math::Vector3f(0, 0, -23));
        node->setRotation(spark::math::Vector3f(0, 0, 0));
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
    void onKeyPressed(int key, int action)
    {
        spark::scene::ISparkSceneNode* root = m_sceneGraphManager3D->rootNode();
        // 4 / 6: Rotation Y-Axis (left/right).
        if (key == 324) m_rot_y -= 0.05f;
        if (key == 326) m_rot_y += 0.05f;

        // 8 / 2: Rotation X-Axis (up/down).
        if (key == 328) m_rot_x -= 0.05f;
        if (key == 322) m_rot_x += 0.05f;

        // 7 / 9: Rotation Z-Axis (roll).
        if (key == 327) m_rot_z += 0.05f;
        if (key == 329) m_rot_z -= 0.05f;

        root->getChildren()[0]->setRotation(spark::math::Vector3f(m_rot_x, m_rot_y, m_rot_z));
    }

    /**
    *
    */
    void paint(spark::renderer::ISparkRenderer* renderer)
    {
        m_sceneGraphManager3D->drawGraph(renderer);

        spark::perspective::OrthographicProjection orthographicProjection(m_device->getScreenResolution().m_width, m_device->getScreenResolution().m_height);
        orthographicProjection.setVirtualResolution(1196, 720, spark::perspective::VirtualResolution::E_LETTER_OR_PILLARBOX);
        m_device->getRenderer()->setOrthographicProjectionMatrix(orthographicProjection);

        renderer->drawString(spark::font::ESFT_ARIAL_16, "X " + std::to_string(m_rot_x), spark::drawing::Color(255, 255, 0, 128), 1000, 70);
        renderer->drawString(spark::font::ESFT_ARIAL_16, "Y " + std::to_string(m_rot_y), spark::drawing::Color(255, 255, 0, 128), 1000, 90);
        renderer->drawString(spark::font::ESFT_ARIAL_16, "Z " + std::to_string(m_rot_z), spark::drawing::Color(255, 255, 0, 128), 1000, 110);
    }

private:
    spark::device::ISparkDevice* m_device;
    spark::SparkSharedPointer<spark::scene::ISceneGraphManager3D> m_sceneGraphManager3D;

    float m_rot_x;
    float m_rot_y;
    float m_rot_z;
};