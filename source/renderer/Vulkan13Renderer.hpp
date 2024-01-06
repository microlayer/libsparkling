#ifndef __SPARK_RENDERER_VULKAN13RENDERER_HPP_INCLUDED__
#define __SPARK_RENDERER_VULKAN13RENDERER_HPP_INCLUDED__
#include "spark/SparkSetup.hpp"
#if SPARK_COMPILE_VULKAN == 0x1
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS  || \
    SPARK_PLATFORM == SPARK_PLATFORM_LINUX
#include "VulkanRenderer.hpp"
#include <vulkan/vulkan.h>
#include "mlstl/MLBase64.hpp"
#include "shader/glsl-for-spir-feature-level-glsles10/DefaultShader.hpp"

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
            void createInstance();
            void createDebugCallback();
            void createWindowSurface();
            void findPhysicalDevice();
            void findQueueFamilies();
            void createLogicalDevice();
            void createCommandPool();
            void createPipeline();
            static VkBool32 debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t srcObject, size_t location, int32_t msgCode, const char* pLayerPrefix, const char* pMsg, void* pUserData);

        private: // spark            
            spark::log::ISparkLogger* m_logger;

        private: // vulkan            
            VkInstance m_vkInstance;
            VkSurfaceKHR m_windowSurface;   // Handle uint64_t
            VkPhysicalDevice m_physicalDevice;
            VkDevice m_device;
            VkQueue m_graphicsQueue;
            VkPhysicalDeviceMemoryProperties m_physicalDeviceMemoryProperties;
            VkCommandPool m_commandPool;
            // Pipeline
            VkPipeline m_graphicsPipeline;
            VkVertexInputBindingDescription m_vertexBindingDescription;
            std::vector<VkVertexInputAttributeDescription> m_vertexAttributeDescriptions;
            VkDescriptorSetLayout m_descriptorSetLayout;
            VkPipelineLayout m_pipelineLayout;

            uint32_t m_graphicsQueueFamily;
            uint32_t m_presentQueueFamily;
            const bool ENABLE_DEBUGGING = false;
            const char* DEBUG_LAYER = "VK_LAYER_LUNARG_standard_validation";
        };
    } // end namespace renderer
} // end namespace spark
#endif
#endif
#endif