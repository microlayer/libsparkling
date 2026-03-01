/**
*
*/
#pragma once
class SampleCanvas3 : public spark::ui::AbstractCanvas
{
public:
    /**
    *
    */
    SampleCanvas3(spark::device::ISparkDevice* device) :
        m_device(device),
        m_rot_x(0.0f),
        m_lastY(0.0f)
    {
        m_sceneGraphManager3D = device->createSceneGraphManager3D();

        spark::SparkSharedPointer<spark::geometry::pointcloud::ISparkPointCloud> pointCloud
            = device->getAssetManager()->loadPointCloud("file://0036_Schuebel_bDOM.ply");

        //spark::SparkSharedPointer<spark::geometry::pointcloud::ISparkPointCloud> pointCloud
        //    = device->getAssetManager()->loadPointCloud("http://www.microlayer.org/libsparkling/0036_Schuebel_bDOM.ply");

        // Create SceneNode
        spark::SparkSharedPointer<spark::scene::ISparkSceneNode> sceneNode = m_sceneGraphManager3D->createSceneNode();
        sceneNode->setPosition(spark::math::Vector3f(0, 0, -23));
        sceneNode->setRotation(spark::math::Vector3f(0, 0, 0));
        sceneNode->attachPointCloud(pointCloud.get());


        spark::SparkSharedPointer<spark::scene::ISparkCoordinateSystemNode> coordinateNode = m_sceneGraphManager3D->createCoordinateSystemNode();
        coordinateNode->setClamp();


        m_sceneGraphManager3D->rootNode()->addChildSceneNode(sceneNode.get());
        m_sceneGraphManager3D->rootNode()->addChildSceneNode(coordinateNode.get());

        // Load HTTP data
        spark::SparkSharedPointer<spark::network::ISparkHttpClient> httpClient = device->getHttpClient();
        httpClient.get()->get("http://test.microlayer.org/test.html", [this](std::vector<spark::uc8_t> data)
            {
                std::string s(data.begin(), data.end());
                m_device->getLogger()->info("Received data from HTTP request, size: %i bytes (%s)", data.size(), s.c_str());
            });
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
    void onMouseMove(spark::real32 x, spark::real32 y)
    {
        if (!m_mouseDown)
        {
            m_lastX = x;
            m_lastY = y;
            return;
        }

        spark::real32 dx = x - m_lastX;
        spark::real32 dy = y - m_lastY;

        m_lastX = x;
        m_lastY = y;

        // Mouse right/left Y-Rotation
        m_rot_y += dx * m_sensitivity;

        // Mouse up/down X-Rotation
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

    spark::real32 m_rot_x;
    spark::real32 m_rot_y;

    bool m_mouseDown = false;
    spark::real32 m_lastX = 0.0f;
    spark::real32 m_lastY = 0.0f;
    spark::real32 m_sensitivity = 0.005f;
};