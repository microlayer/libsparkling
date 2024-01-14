#ifndef __SPARK_RENDERER_VULKAN13RENDERER_HPP_INCLUDED__
#define __SPARK_RENDERER_VULKAN13RENDERER_HPP_INCLUDED__
#include "spark/SparkSetup.hpp"
#if SPARK_COMPILE_VULKAN == 0x1
#define GLFW_INCLUDE_VULKAN
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS  || \
    SPARK_PLATFORM == SPARK_PLATFORM_LINUX
#include "ISparkWindow.hpp"
#include "VulkanRenderer.hpp"
#include <glfw/glfw3.h>
#include <vulkan/vulkan.h>
#include "mlstl/MLBase64.hpp"
#include "shader/glsl-for-spir-feature-level-glsles10/DefaultShader.hpp"

namespace spark {
    namespace renderer {
        /**
        *
        */
        struct VulkanConfig
        {
            std::vector<VkPhysicalDevice> gpus;
            std::vector<VkQueueFamilyProperties> queueFamilyProperties;
            uint32_t queueFamilyIndex;

            // createSwapChain
            std::vector<VkSurfaceFormatKHR> surfaceFormats;
            std::vector<VkPresentModeKHR> presentModes;
            std::vector<VkImage> swapChainImages;
            VkFormat format;

            // Supported GLFW Window Extensions
            uint32_t windowExtensionCount;
            std::vector<const char*> windowExtensions;
        };

        /**
        *
        */
        class Vulkan13Renderer : public spark::renderer::VulkanRenderer
        {
        public:
            Vulkan13Renderer(spark::device::ISparkDevice* device, spark::renderer::shader::ISparkShader* shader, spark::device::window::ISparkWindow* window);
            virtual ~Vulkan13Renderer(void);

        public: // ISparkRenderer
            // Lifecycle
            void onInit();

        private:
            void createInstance();
            void createDebugCallback();
            void createWindowSurface();
            void findPhysicalDevices();
            void createLogicalDevice();
            void createCommandBuffer();
            void isSwapChainSupportAvailable();
            void createSwapChain();
            void createRenderPass();
            void createPipeline();
            static VkBool32 debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t srcObject, size_t location, int32_t msgCode, const char* pLayerPrefix, const char* pMsg, void* pUserData);

        private: // spark            
            spark::log::ISparkLogger* m_logger;
            spark::device::window::ISparkWindow* m_window;

        private: // vulkan            
            VkInstance m_vkInstance;
            VkSurfaceKHR m_windowSurface;
            VkDevice m_device;
            // Command Buffer
            VkCommandPool m_commandPool;
            // Swap chain
            //VkFormat m_swapChainFormat;
            VkExtent2D m_swapChainExtent;
            VkSwapchainKHR m_swapChain;
            // Render pass
            VkRenderPass m_renderPass;
            // Pipeline
            VkPipeline m_graphicsPipeline;
            VkVertexInputBindingDescription m_vertexBindingDescription;
            std::vector<VkVertexInputAttributeDescription> m_vertexAttributeDescriptions;
            VkDescriptorSetLayout m_descriptorSetLayout;
            VkPipelineLayout m_pipelineLayout;

        private:
            const bool ENABLE_VULKAN_DEBUGGING = true;

        private:
            VulkanConfig m_vulkanConfig = {};
        };
    } // end namespace renderer
} // end namespace spark
#endif
#endif
#endif