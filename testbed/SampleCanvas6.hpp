/**
*
*/
#pragma once
class SampleCanvas6 : public spark::ui::AbstractCanvas
{
public:
    /**
    *
    */
    SampleCanvas6(spark::device::ISparkDevice* device) :
        m_device(device)
    {
        spark::file::ISparkFileSystem* m_fileSystem = device->getFileSystem();

        m_level = m_fileSystem->loadTiledLayer("tiles4x4_32_v1-11.tmx");
        m_level->setPosition(200, 150);

        //       
        m_explosionImage = m_fileSystem->loadBitmap("explosion.png");
        m_explosionSprite = m_device->createSprite(m_explosionImage.get());
        m_explosionSprite->setPosition(100, 100);
        m_explosionSprite->startAnimation();
        m_explosionSprite->setAnimationDetails(100, 25, 25);
    }

    /**
    *
    */
    virtual ~SampleCanvas6()
    {

    }

    /**
    *
    */
    void init()
    {
        m_device->getLogger()->info("Init Canvas6");

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
        renderer->drawBackground(spark::drawing::Color(0, 0, 0, 255));
        renderer->drawString(spark::font::ESFT_ARIAL_16, "FPS: 60", spark::drawing::Color(255, 255, 0, 128), 1000, 70);
        m_level->paint(renderer);

        //m_explosionSprite->paint(renderer);
    }

private:
    spark::device::ISparkDevice* m_device;
    spark::SparkSharedPointer<spark::game::ISparkTiledLayer> m_level;
    spark::SparkSharedPointer<spark::drawing::ISparkImage> m_explosionImage;
    spark::SparkSharedPointer<spark::game::ISparkSprite> m_explosionSprite;
};