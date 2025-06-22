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
        spark::file::ISparkFileSystem* m_fileSystem = device->getFileSystem();

        m_level = m_fileSystem->loadTiledLayer("tiles4x4_32_v1-11.tmx");
        m_level->setPosition(0, 150);
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
    }

private:
    spark::device::ISparkDevice* m_device;
    spark::SparkSharedPointer<spark::game::ISparkTiledLayer> m_level;
};