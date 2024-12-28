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
        renderer->drawString(spark::font::ESFT_ARIAL_16, "canvas2", spark::drawing::Color(128, 128, 128, 128), 600, 300);
    }

private:
};