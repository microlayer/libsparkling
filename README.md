# Sparkling engine

See [sparkling wiki](https://github.com/tschuebel/libsparkling/wiki) page for more information about computer graphics.

## Tutorial

### 'Hello Sparkling' application

```cpp
#include "Sparkling.hpp"

int main(void)
{
    spark::device::ISparkDevice* device = spark::createDevice(spark::renderer::ERE_OGLFLES2);
    spark::log::ISparkLogger* logger = device->getLogger();
    while (device->isDeviceRunning())
    {
        device->getRenderer()->beginScene();
        device->getRenderer()->drawString(spark::font::ESFT_ARIAL_16, "Hello sparkling", spark::drawing::Color(0, 255, 0, 0), 300, 30);
        device->getRenderer()->endScene();
    }
    logger->info("Cleanup");
    device->release();
}
```

### Default application

```cpp
/**
*
*/
class SampleApp : public spark::application::SparkApp, public spark::ui::ISparkCommandListener
{
public:
    /**
    *
    */
    SampleApp(spark::device::ISparkDevice* device)
    {
        m_sampleCanvas = new SampleCanvas(device);
        m_sampleCanvas->registerCommandListener(this);
    }

    /**
    *
    */
    virtual ~SampleApp()
    {
        if(m_sampleCanvas != NULL)
        {
            delete m_sampleCanvas;
        }
    }

    /**
    *
    */
    void init()
    {
        this->setActiveCanvas(m_sampleCanvas);
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
    SampleCanvas* m_sampleCanvas;
};

class SampleCanvas : public spark::ui::AbstractCanvas
{
public:
    /**
    * 
    */ 
    SampleCanvas(spark::device::ISparkDevice* device)
    {  
    }

public:
    /**
    *
    */
    void paint(spark::renderer::ISparkRenderer* renderer)
    {  
        renderer->drawString(spark::font::ESFT_ARIAL_16, "Hello sparkling", spark::drawing::Color(0, 255, 0, 0), 300, 30);
    }
private:
};

#include "Sparkling.hpp"

int main(void)
{
    spark::device::ISparkDevice* device = spark::createDevice(spark::renderer::ERE_OGLFLES2);
    spark::log::ISparkLogger* logger = device->getLogger();
    SampleApp* sampleApp = new SampleApp(device);
    device->run(sampleApp);
    logger->info("Cleanup");
    delete sampleApp;
    device->release();
}
```

## Used libraries

|Lib|Version|Release Date|Source|
|---|---|---|---|
|glew|2.1.0 |July 31, 2017|[OpenGL Extension Wrangler Library](https://glew.sourceforge.net/)|
|glfw|3.4.0 |Feb 23, 2024|[GLFW](https://www.glfw.org/download.html)|
|lodepng|20230410|April 04, 2023|[lodepng](https://lodev.org/lodepng/)|
|vulkan|1.3.224.1|August 21, 2022|[Vulkan](https://de.wikipedia.org/wiki/Vulkan_(API))|
