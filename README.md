# Sparkling engine

## Tutorial

### Basic 'Hello Sparkling' application

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