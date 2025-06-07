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
    }

private:
    spark::device::ISparkDevice* m_device;
};