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
     
    }

    /**
    *
    */
    void init()
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
    {
        std::unique_ptr<SampleApp> sampleApp = std::make_unique<SampleApp>(device);
        device->run(sampleApp.get());
    }
    logger->info("Cleanup");
    device->release();
}
```

## Used libraries

|Lib|Version|Release Date|Source|
|---|---|---|---|
|glew|2.1.0 |July 31, 2017|[OpenGL Extension Wrangler Library](https://glew.sourceforge.net/)|
|glfw|3.4.0 |Feb 23, 2024|[GLFW](https://www.glfw.org/download.html)|
|lodepng|20230410|April 04, 2023|[lodepng](https://lodev.org/lodepng/)|
|tinyxml2|10.0.0|Dec 31, 2023|[tinyxml2](https://github.com/leethomason/tinyxml2)|
|vulkan|1.3.296.0|Oct 8, 2024|[Vulkan](https://de.wikipedia.org/wiki/Vulkan_(API))|
|box2d|2.3.1|April 06, 2014|[box2D](https://box2d.org/)|
