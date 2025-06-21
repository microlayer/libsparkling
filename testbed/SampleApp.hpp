#include "SampleCanvas1.hpp"
#include "SampleCanvas2.hpp"
#include "SampleCanvas3.hpp"
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
    SampleApp(spark::device::ISparkDevice* device) :
        m_device(device)
    {
        m_sampleCanvas1 = new SampleCanvas1(device);
        m_sampleCanvas2 = new SampleCanvas2(device);
        m_sampleCanvas3 = new SampleCanvas3(device);
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
        m_timer.setTimeout([this]() {this->switchToCanvas2(); }, 2000);
        m_timer.setTimeout([this]() {this->switchToCanvas3(); }, 4000);
    }

    /**
    *
    */
    void switchToCanvas2()
    {
        this->setActiveCanvas(m_sampleCanvas2.get());
    }

    /**
    *
    */
    void switchToCanvas3()
    {
        this->setActiveCanvas(m_sampleCanvas3.get());
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
    spark::SparkSharedPointer<SampleCanvas3> m_sampleCanvas3;
    spark::ui::AbstractCanvas* m_currentCanvas;
    spark::timer::Timer m_timer;
    spark::device::ISparkDevice* m_device;
};