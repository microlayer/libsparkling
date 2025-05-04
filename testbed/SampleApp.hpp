#include "SampleCanvas1.hpp"
#include "SampleCanvas2.hpp"
#include "ISparkCommandListener.hpp"

/**
*
*/
class SampleApp : public spark::app::ISparkApp, public spark::ui::ISparkCommandListener
{
public:
    /**
    *
    */
    SampleApp(spark::device::ISparkDevice* device)
    {
        m_sampleCanvas1 = new SampleCanvas1(device);
        m_sampleCanvas2 = new SampleCanvas2(device);
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
        this->setActiveCanvas(m_sampleCanvas1.get());
        m_timer.setTimeout([this]() {this->switchCanvas(); }, 2000);
    }

    /**
    *
    */
    void switchCanvas()
    {
        this->setActiveCanvas(m_sampleCanvas2.get());
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

    /**
    *
    */
    spark::ui::AbstractCanvas* getActiveCanvas()
    {
        return m_currentCanvas;
    }

    /**
    *
    */
    void setActiveCanvas(spark::ui::AbstractCanvas* canvas)
    {
        m_currentCanvas = canvas;
    }

private:
    spark::SparkSharedPointer<SampleCanvas1> m_sampleCanvas1;
    spark::SparkSharedPointer<SampleCanvas2> m_sampleCanvas2;
    spark::ui::AbstractCanvas* m_currentCanvas;
    spark::timer::Timer m_timer;
};