#include "SampleCanvas1.hpp"
#include "ISparkCommandListener.hpp"

/**
*
*/
class SampleApp : public spark::app::SparkApp, public spark::ui::ISparkCommandListener
{
public:
    /**
    *
    */
    SampleApp(spark::device::ISparkDevice* device)
    {
        m_sampleCanvas = new SampleCanvas1(device);
        //m_sampleCanvas->registerCommandListener(this);
    }

    /**
    *
    */
    virtual ~SampleApp()
    {

    }

    /**
    *
    */
    void onInit()
    {
        this->setActiveCanvas(m_sampleCanvas.get());
    }

    /**
    *
    */
    void executeCommand(spark::ui::Command::E_COMMAND_TYPE cmd, spark::ui::AbstractCanvas* canvas)
    {
        if (spark::ui::Command::ECT_BACK == cmd)
        {

        }
    }

private:
    spark::SparkSharedPointer<SampleCanvas1> m_sampleCanvas;
};