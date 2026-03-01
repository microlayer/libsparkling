/*
 * MIT License
 *
 * Copyright (c) [2026] [Thomas Schuebel]
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

 // Include configuration and symbols
#include "spark/SparkCompilerConfig.hpp"
#include "spark/SparkSetup.hpp"
#include "spark/SparkTypes.hpp"
#include "ISparkDevice.hpp"

#if SPARK_PLATFORM == SPARK_PLATFORM_ANDROID
#	include <android_native_app_glue.h>
#endif

/**
* @brief Create sparkling device. Rerturns pure virtual interface to keep.
*/
namespace spark {
#if (SPARK_PLATFORM == SPARK_PLATFORM_ANDROID)
    extern "C" SPARKLING_API device::ISparkDevice* SPARKCALLCONV createDevice(
        spark::renderer::E_RENDER_ENGINE rendererType,
        uint32_t screenWidth,
        uint32_t screenHeight,
        android_app* pApplication);
#else
    extern "C" SPARKLING_API device::ISparkDevice* SPARKCALLCONV createDevice(
        spark::renderer::E_RENDER_ENGINE rendererType,
        uint32_t screenWidth,
        uint32_t screenHeight);
#endif
} // end namespace spark


