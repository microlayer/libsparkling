/**
*
*/
class SampleCanvas2 : public spark::ui::AbstractCanvas
{
public:
    /**
    *
    */
    SampleCanvas2(spark::device::ISparkDevice* device) :
        m_device(device)
    {
        m_sceneGraphManager2D = m_device->createSceneGraphManager2D();

        m_quadImage = m_device->getFileSystem()->loadBitmap("quad.png");
        m_quadSprite = m_sceneGraphManager2D->addSprite(m_quadImage.get());
        m_sceneGraphManager2D->addLineLayer(0, 200, 200, 200, spark::drawing::Color(255, 0, 0, 255));
        //m_quadSprite->setPosition(100, 100);
        //m_quadSprite->setRotation(25);
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
        renderer->drawString(spark::font::ESFT_ARIAL_16, "canvas2", spark::drawing::Color(128, 128, 128, 128), 600, 300);
        renderer->draw2DLine(0, 0, 1196, 720, spark::drawing::Color(0, 255, 0, 255));

        m_sceneGraphManager2D->drawGraph(renderer);
    }

private:
    spark::device::ISparkDevice* m_device;
    spark::SparkSharedPointer<spark::scene::ISceneGraphManager2D> m_sceneGraphManager2D;
    spark::SparkSharedPointer<spark::drawing::ISparkImage> m_quadImage;
    spark::SparkSharedPointer<spark::game::Sprite> m_quadSprite;
};