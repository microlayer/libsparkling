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
        m_sceneGraphManager2D = m_device->createSceneGraphManager2D();

        m_quadImage = m_device->getFileSystem()->loadBitmap("quad.png");
        m_sunsetImage = m_device->getFileSystem()->loadBitmap("sunset.png");

        spark::game::Sprite* quadSprite1 = m_sceneGraphManager2D->createSprite(m_quadImage.get());
        spark::game::Sprite* quadSprite2 = m_sceneGraphManager2D->createSprite(m_quadImage.get());
        spark::game::Sprite* quadSprite3 = m_sceneGraphManager2D->createSprite(m_quadImage.get());

        quadSprite1->setPosition(200, 75);
        quadSprite1->setRotation(-0.775f);

        quadSprite2->setPosition(200, 15);

        quadSprite3->setPosition(200, 40);

        m_sceneGraphManager2D->createLineLayer(0, 600, 500, 600, spark::drawing::Color(255, 0, 0, 255));
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
        // Set virtual resolution
        spark::perspective::OrthographicProjection orthographicProjection(m_device->getScreenResolution().m_width, m_device->getScreenResolution().m_height);
        orthographicProjection.setVirtualResolution(1196, 720, spark::perspective::VirtualResolution::E_LETTER_OR_PILLARBOX);
        m_device->getRenderer()->setOrthographicProjectionMatrix(orthographicProjection);
    }

    /**
    *
    */
    void paint(spark::renderer::ISparkRenderer* renderer)
    {
        renderer->draw2DBitmap(m_sunsetImage.get(), 0, 0);
        renderer->drawString(spark::font::ESFT_ARIAL_16, "CPU: 2.8%", spark::drawing::Color(0, 128, 0, 0), 600, 50);
        m_sceneGraphManager2D->drawGraph(renderer);
    }

private:
    spark::device::ISparkDevice* m_device;
    spark::SparkSharedPointer<spark::scene::ISceneGraphManager2D> m_sceneGraphManager2D;
    spark::SparkSharedPointer<spark::drawing::ISparkImage> m_quadImage;
    spark::SparkSharedPointer<spark::drawing::ISparkImage> m_sunsetImage;
};