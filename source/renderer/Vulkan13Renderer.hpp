#ifndef __SPARK_RENDERER_VULKAN13RENDERER_HPP_INCLUDED__
#define __SPARK_RENDERER_VULKAN13RENDERER_HPP_INCLUDED__
#include "spark/SparkSetup.hpp"
#include "ISparkTextureFactory.hpp"
#if SPARK_COMPILE_VULKAN == 0x1
#define GLFW_INCLUDE_VULKAN
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS  || \
    SPARK_PLATFORM == SPARK_PLATFORM_LINUX    || \
    SPARK_PLATFORM == SPARK_PLATFORM_ANDROID
#include "VulkanRenderer.hpp"

namespace spark {
    namespace renderer {
        /**
        *
        */
        class Vulkan13Renderer : public spark::renderer::VulkanRenderer
        {
        public:
            Vulkan13Renderer(spark::device::ISparkDevice* device,
                spark::renderer::shader::ISparkShader* shader
                spark::renderer::ISparkTextureFactory* textureFactory);
            virtual ~Vulkan13Renderer(void);

        public: // ISparkRenderer
            // Lifecycle
            void onInit();
        };
    } // end namespace renderer
} // end namespace spark
#endif
#endif
#endif