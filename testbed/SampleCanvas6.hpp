/**
*
*/
class SampleCanvas6 : public spark::ui::AbstractCanvas
{
public:
    /**
    *
    */
    SampleCanvas6(spark::device::ISparkDevice* device) :
        m_device(device)
    {
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
        renderer->drawString(spark::font::ESFT_ARIAL_16, "Canvas6  on FPS: 60", spark::drawing::Color(255, 255, 0, 128), 800, 70);
    }

private:
    spark::device::ISparkDevice* m_device;
};