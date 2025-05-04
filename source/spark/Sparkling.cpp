#include "SparkSetup.hpp"
#include "Sparkling.hpp"
#include "ISparkDevice.hpp"

#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS
#include "device/Win32Device.hpp"
#endif

#if SPARK_PLATFORM == SPARK_PLATFORM_ANDROID
#include "device/AndroidDevice.hpp"
#include <android_native_app_glue.h>
#endif

#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
#include "device/WebGLDevice.hpp"
#endif

/**
* @Brief Creates a device for the Windows platform
*/
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS
spark::device::ISparkDevice* spark::createDevice(spark::renderer::E_RENDER_ENGINE rendererType)
{
    spark::device::ISparkDevice* dev = new spark::device::Win32Device(rendererType);
    return dev;
}
#endif

/**
* @Brief Creates a device for the Android platform
*/
#if SPARK_PLATFORM == SPARK_PLATFORM_ANDROID
spark::device::ISparkDevice* spark::createDevice(spark::renderer::E_RENDER_ENGINE rendererType, android_app* pApplication)
{
    spark::device::ISparkDevice* dev = new spark::device::AndroidDevice(rendererType, pApplication);
    return dev;
}
#endif

/**
* @Brief Creates a device for the WebGL platform
*/
#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
spark::device::ISparkDevice* spark::createDevice(spark::renderer::E_RENDER_ENGINE rendererType)
{
    spark::device::ISparkDevice* dev = new spark::device::WebGLDevice(rendererType);
    return dev;
}
#endif

/**
* @Brief Creates a device for the Apple platform
*/
#if SPARK_PLATFORM == SPARK_PLATFORM_APPLE
spark::device::ISparkDevice* spark::createDevice(spark::renderer::E_RENDER_ENGINE rendererType)
{
    spark::device::ISparkDevice* dev = new spark::device::AppleDevice(rendererType);
    return dev;
}
#endif
