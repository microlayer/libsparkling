#include "Sparkling.hpp"
#include "../../SampleApp.hpp"
#include <memory>
#include <emscripten.h>

#define START_SAMPLEAPP 0
#if (START_SAMPLEAPP)
/**
* 
*/
void mainLoopWrapper(void* arg);

int main(void)
{
	spark::device::ISparkDevice* device = spark::createDevice(spark::renderer::ERE_OGLES2, 1196, 720);
	spark::log::ISparkLogger* logger = device->getLogger();	
	
	auto mainLoop = [device]() {
		device->getRenderer()->beginScene();
		device->getRenderer()->draw2DPoint(0, 0, spark::drawing::Color(0, 0, 0, 0));		
		device->getRenderer()->endScene();
	};
	
	auto lambda = new std::function<void()>(mainLoop);
	emscripten_set_main_loop_arg(mainLoopWrapper, lambda, 0, 1);
	
	logger->info("Cleanup");
	device->release();
}

void mainLoopWrapper(void* arg)
{
    auto lambda = static_cast<std::function<void()>*>(arg);
    (*lambda)();
}
#else
/**
*
*/
int main()
{    
	spark::device::ISparkDevice* device = spark::createDevice(spark::renderer::ERE_OGLES2, 1196, 720);    
	spark::log::ISparkLogger* logger = device->getLogger();
    SampleApp* sampleApp = new SampleApp(device);
    logger->info("Starting application");
	device->run(sampleApp);
	logger->info("Cleanup");
    delete sampleApp;
	device->release();
}
#endif