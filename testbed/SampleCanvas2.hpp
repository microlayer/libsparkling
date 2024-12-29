/**
*
*/
class SampleCanvas2 : public spark::ui::AbstractCanvas
{
public:
    /**
    *
    */
    SampleCanvas2(spark::device::ISparkDevice* device)
    {

    }

    /**
    *
    */
    void paint(spark::renderer::ISparkRenderer* renderer)
    {
        //renderer->drawString(spark::font::ESFT_ARIAL_16, "canvas2", spark::drawing::Color(128, 128, 128, 128), 600, 300);
        renderer->draw2DLine(0, 0, 1196, 720, spark::drawing::Color(0, 255, 0, 255));
    }

private:
};