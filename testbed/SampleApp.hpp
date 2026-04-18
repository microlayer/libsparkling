#include "RotatingCubeCanvas.hpp"
#include "TeapotCanvas.hpp"
#include "PointCloudCanvas.hpp"
#include "SampleCanvas4.hpp"
#include "FallingBlocksPhysicsCanvas.hpp"
#include "SampleCanvas6.hpp"
#include "SampleCanvas7.hpp"
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
        m_rotatingCubeCanvas = new RotatingCubeCanvas(device);
        m_teapotCanvas = new TeapotCanvas(device);
        m_pointCloudCanvas = new PointCloudCanvas(device);
        m_sampleCanvas4 = new SampleCanvas4(device);
        m_fallingBlocksPhysicsCanvas = new FallingBlocksPhysicsCanvas(device);
        m_sampleCanvas6 = new SampleCanvas6(device);
        m_sampleCanvas7 = new SampleCanvas7(device);
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
        this->setActiveCanvas(m_rotatingCubeCanvas.get());
        m_timer1.setTimeout([this]() {this->switchToCanvas2(); }, 4000);
        m_timer2.setTimeout([this]() {this->switchToCanvas3(); }, 8000);
        m_timer3.setTimeout([this]() {this->switchToCanvas4(); }, 12000);
        m_timer4.setTimeout([this]() {this->switchToCanvas5(); }, 22000);
        m_timer5.setTimeout([this]() {this->switchToCanvas6(); }, 26000);
        m_timer6.setTimeout([this]() {this->switchToCanvas7(); }, 30000);
    }

    /**
    *
    */
    void switchToCanvas2()
    {
        this->setActiveCanvas(m_teapotCanvas.get());
    }

    /**
    *
    */
    void switchToCanvas3()
    {
        this->setActiveCanvas(m_pointCloudCanvas.get());
    }

    /**
    *
    */
    void switchToCanvas4()
    {
        this->setActiveCanvas(m_sampleCanvas4.get());
    }

    /**
    *
    */
    void switchToCanvas5()
    {
        this->setActiveCanvas(m_fallingBlocksPhysicsCanvas.get());
    }

    /**
    *
    */
    void switchToCanvas6()
    {
        this->setActiveCanvas(m_sampleCanvas6.get());
    }

    /**
    *
    */
    void switchToCanvas7()
    {
        this->setActiveCanvas(m_sampleCanvas7.get());
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
    spark::SparkSharedPointer<RotatingCubeCanvas> m_rotatingCubeCanvas;
    spark::SparkSharedPointer<TeapotCanvas> m_teapotCanvas;
    spark::SparkSharedPointer<PointCloudCanvas> m_pointCloudCanvas;
    spark::SparkSharedPointer<SampleCanvas4> m_sampleCanvas4;
    spark::SparkSharedPointer<FallingBlocksPhysicsCanvas> m_fallingBlocksPhysicsCanvas;
    spark::SparkSharedPointer<SampleCanvas6> m_sampleCanvas6;
    spark::SparkSharedPointer<SampleCanvas7> m_sampleCanvas7;
    spark::ui::AbstractCanvas* m_currentCanvas;
    spark::device::ISparkDevice* m_device;
    spark::timer::Timer m_timer1;
    spark::timer::Timer m_timer2;
    spark::timer::Timer m_timer3;
    spark::timer::Timer m_timer4;
    spark::timer::Timer m_timer5;
    spark::timer::Timer m_timer6;
};