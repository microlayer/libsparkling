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
        m_rot_x = 0.0f;
        m_rot_y = 0.0f;
        spark::scene::ISparkSceneNode* root = m_sceneGraphManager3D->rootNode();
        root->getChildren()[0]->setRotation(spark::math::Vector3f(m_rot_x, m_rot_y, 0.0f));
    }

    /**
    *
    */
    void onMouseMove(float x, float y)
    {
        if (!m_mouseDown)
        {
            m_lastX = x;
            m_lastY = y;
            return;
        }

        float dx = x - m_lastX;
        float dy = y - m_lastY;

        m_lastX = x;
        m_lastY = y;

        // Maus right/left Y-Rotation
        m_rot_y += dx * m_sensitivity;

        // Maus up/down X-Rotation
        m_rot_x += dy * m_sensitivity;

        spark::scene::ISparkSceneNode* root = m_sceneGraphManager3D->rootNode();
        root->getChildren()[0]->setRotation(spark::math::Vector3f(m_rot_x, m_rot_y, 0.0f));
    }

    /**
    *
    */
    void onMouseClick(int button, int action)
    {
        if (button == 0)
        {
            if (action == 1)
                m_mouseDown = true;
            else if (action == 0)
                m_mouseDown = false;
        }
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

        renderer->drawString(spark::font::ESFT_ARIAL_16, "X: " + std::to_string(m_rot_x), spark::drawing::Color(255, 255, 0, 128), 1000, 70);
        renderer->drawString(spark::font::ESFT_ARIAL_16, "Y: " + std::to_string(m_rot_y), spark::drawing::Color(255, 255, 0, 128), 1000, 90);
    }

private:
    spark::device::ISparkDevice* m_device;
    spark::SparkSharedPointer<spark::scene::ISceneGraphManager3D> m_sceneGraphManager3D;

    float m_rot_x;
    float m_rot_y;

    bool m_mouseDown = false;
    float m_lastX = 0.0f;
    float m_lastY = 0.0f;
    float m_sensitivity = 0.005;
};