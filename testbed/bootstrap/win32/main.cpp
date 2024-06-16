/****************************************************************************************************************
[1] Create an empty Console Application		                                                                    *
                                                                                                                *
[2] Includeverzeichnisse:                                                                                       * 
$(SolutionDir)../../include                                                                                     *
$(SolutionDir)../../source                                                                                      *
                                                                                                                *
[3] Bibliotheksverzeichnisse:                                                                                   *
$(SolutionDir)../../lib                                                                                         *                                             
$(VK_SDK_PATH)/lib32                                                                                            *
                                                                                                                *
[4] Preprocessordefinitions symbols:																			*
_CRT_SECURE_NO_DEPRECATE																						*
_SCL_SECURE_NO_DEPRECATE																						*
_CRT_SECURE_NO_WARNINGS																							*
GLEW_STATIC																										*
                                                                                                                *
[5] Character Set                                                                                               *
Multibyte Character Set                                                                                         * 
****************************************************************************************************************/
#include "Sparkling.hpp"

#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#pragma comment(lib, "glfw/lib-vc2022/glfw3.lib")
#pragma comment(lib, "lodepng/lib-vc2022/lodepng.lib")
#pragma comment(lib, "opengl32.lib")
#if SPARK_COMPILE_VULKAN == 0x1
#pragma comment(lib, "vulkan-1.lib")
#endif

#define START_SAMPLEAPP 0
#if (START_SAMPLEAPP)
/**
* 
*/
int main()
{
	_CrtMemDumpAllObjectsSince(NULL);
	spark::device::ISparkDevice* device = spark::createDevice(spark::renderer::ERE_OGLFLES2);
	spark::log::ISparkLogger* logger = device->getLogger();
	while (device->isDeviceRunning())
	{
		device->getRenderer()->beginScene();
		device->getRenderer()->draw2DPoint(0, 0, spark::drawing::Color(0, 0, 0, 0));
		device->getRenderer()->endScene();
	}
	logger->info("Cleanup");
	device->release();

	// Dump memory status
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int result = _CrtDumpMemoryLeaks();
}

#else
/**
*
*/
#include "Sparkling.hpp"
#include "../../SampleApp.hpp"

int main()
{
    _CrtMemDumpAllObjectsSince(NULL);
    spark::device::ISparkDevice* device = spark::createDevice(spark::renderer::ERE_OGLFLES2);
    spark::log::ISparkLogger* logger = device->getLogger();
    {
        std::unique_ptr<SampleApp> sampleApp = std::make_unique<SampleApp>(device);
        device->run(sampleApp.get());
    }
    logger->info("Cleanup");
    device->release();

    // Dump memory status
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    int result = _CrtDumpMemoryLeaks();
}
#endif