#ifndef __SPARK_RENDERER_VULKAN13RENDERER_HPP_INCLUDED__
#define __SPARK_RENDERER_VULKAN13RENDERER_HPP_INCLUDED__
#include "spark/SparkSetup.hpp"
#if SPARK_COMPILE_VULKAN == 0x1
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS  || \
    SPARK_PLATFORM == SPARK_PLATFORM_LINUX
#include "VulkanRenderer.hpp"
#include <vulkan/vulkan.h>

namespace spark {
    namespace renderer {
        class Vulkan13Renderer : public spark::renderer::VulkanRenderer
        {
        public:
            Vulkan13Renderer(spark::device::ISparkDevice* device, spark::renderer::shader::ISparkShader* shader);
            virtual ~Vulkan13Renderer(void);

        public: // ISparkRenderer
            // Lifecycle
            void onInit();
        private:
            VkInstance m_vkInstance;
        };
    } // end namespace renderer
} // end namespace spark
#endif
#endif
#endif