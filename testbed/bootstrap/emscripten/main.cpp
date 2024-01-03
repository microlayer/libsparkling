#define START_SAMPLEAPP 0
#if (START_SAMPLEAPP)
/**
* 
*/
#include "Sparkling.hpp"
#include <memory>

int main(void)
{
	spark::device::ISparkDevice* device = spark::createDevice(spark::renderer::ERE_OGLES2);
	spark::log::ISparkLogger* logger = device->getLogger();	
	while (device->isDeviceRunning())
	{
		device->getRenderer()->beginScene();
		device->getRenderer()->draw2DPoint(0, 0, spark::drawing::Color(0, 0, 0, 0));
		device->getRenderer()->endScene();
	}
	logger->info("Cleanup");
	device->release();
}
#else
/**
*
*/
#include "Sparkling.hpp"
#include "../../SampleApp.hpp"

int main()
{
    
	spark::device::ISparkDevice* device = spark::createDevice(spark::renderer::ERE_OGLES2);    
	spark::log::ISparkLogger* logger = device->getLogger();
    SampleApp* sampleApp = new SampleApp(device);
    logger->info("Starting application");
	device->run(sampleApp);
	logger->info("Cleanup");
    delete sampleApp;
	device->release();
}
#endif