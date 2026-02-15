/**
*
*/
#pragma once
class SampleCanvas4 : public spark::ui::AbstractCanvas
{
public:
    /**
    *
    */
    SampleCanvas4(spark::device::ISparkDevice* device) :
        m_device(device)
    {
        m_texture1Image = m_device->getFileSystem()->loadBitmap("texture1.png");
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
    void paint(spark::renderer::ISparkRenderer* renderer)
    {
        renderer->drawString(spark::font::ESFT_ARIAL_16, "Hello Canvas 4", spark::drawing::Color(255, 255, 0, 128), 600, 300);
        renderer->draw2DLine(0, 0, 1196, 720, spark::drawing::Color(0, 255, 0, 255));
        renderer->draw2DBitmap(m_texture1Image.get(), 0, 464);
        renderer->draw2DBitmap(m_texture1Image.get(), 940, 0);
    }

private:
    spark::device::ISparkDevice* m_device;
    spark::SparkSharedPointer<spark::drawing::ISparkImage> m_texture1Image;
};