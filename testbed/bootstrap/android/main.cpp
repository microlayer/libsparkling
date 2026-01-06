#include "Sparkling.hpp"
#include "../../SampleApp.hpp"

#define START_SAMPLEAPP 0
#if (START_SAMPLEAPP)
/**
* 
*/
void android_main(android_app* pApplication)
{
	spark::device::ISparkDevice* device = spark::createDevice(spark::renderer::ERE_OGLES2, 1196, 720, pApplication);
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
void android_main(android_app* pApplication)
{
    spark::device::ISparkDevice* device = spark::createDevice(spark::renderer::ERE_OGLES2, 1196, 720, pApplication);
    spark::log::ISparkLogger* logger = device->getLogger();
    {
        std::unique_ptr<SampleApp> sampleApp = std::make_unique<SampleApp>(device);
        device->run(sampleApp.get());
    }
    logger->info("Cleanup");
    device->release();
}
#endif