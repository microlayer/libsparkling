/**
*
*/
class SampleCanvas4 : public spark::ui::AbstractCanvas
{
public:
    /**
    *
    */
    SampleCanvas4(spark::device::ISparkDevice* device) :
        m_device(device)
    {
        m_sceneGraphManager2D = m_device->createSceneGraphManager2D();

        m_quadImage = m_device->getFileSystem()->loadBitmap("quad.png");
        m_sunsetImage = m_device->getFileSystem()->loadBitmap("sunset.png");

        spark::game::ISparkSprite* quadSprite1 = m_sceneGraphManager2D->createSprite(m_quadImage.get());
        spark::game::ISparkSprite* quadSprite2 = m_sceneGraphManager2D->createSprite(m_quadImage.get());
        spark::game::ISparkSprite* quadSprite3 = m_sceneGraphManager2D->createSprite(m_quadImage.get());

        quadSprite1->setPosition(200, 75);
        quadSprite1->setRotation(-0.775f);

        quadSprite2->setPosition(250, 15);

        quadSprite3->setPosition(200, 40);

        spark::game::ISparkLineLayer* line1 = m_sceneGraphManager2D->createLineLayer(0, 600, 500, 600, spark::drawing::Color(0, 0, 0, 255));
        spark::game::ISparkLineLayer* line2 = m_sceneGraphManager2D->createLineLayer(0, 300, 200, 300, spark::drawing::Color(0, 0, 0, 255));

        //line1->setPosition(10, 10);
    }

    /**
    *
    */
    virtual ~SampleCanvas4()
    {

    }

    /**
    *
    */
    void init()
    {
        m_device->getLogger()->info("Init Canvas4");

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
        renderer->draw2DBitmap(m_sunsetImage.get(), 0, 0);
        renderer->drawString(spark::font::ESFT_ARIAL_16, "FPS: 60", spark::drawing::Color(255, 255, 0, 128), 1000, 70);
        m_sceneGraphManager2D->drawGraph(renderer);
    }

private:
    spark::device::ISparkDevice* m_device;
    spark::SparkSharedPointer<spark::scene::ISceneGraphManager2D> m_sceneGraphManager2D;
    spark::SparkSharedPointer<spark::drawing::ISparkImage> m_quadImage;
    spark::SparkSharedPointer<spark::drawing::ISparkImage> m_sunsetImage;
};