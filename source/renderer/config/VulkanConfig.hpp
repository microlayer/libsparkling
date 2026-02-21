#ifndef __SPARK_RENDERER_VULKANCONFIG_HPP_INCLUDED__
#define __SPARK_RENDERER_VULKANCONFIG_HPP_INCLUDED__
#include "spark/SparkSetup.hpp"
#if SPARK_COMPILE_VULKAN == 0x1
#include "ISparkRendererApiConfig.hpp"
#include <vulkan/vulkan.h>
#include "ISparkWindow.hpp"
#include <glfw/glfw3.h>
#include <vector>
#include <string>
#include "ISparkLogger.hpp"
#include "../shader/glsl_for_spir_feature_level_glsles10/DefaultShader.hpp"
#include "mlstl/MLBase64.hpp"

namespace spark::renderer {
    /**
    *
    */
    struct VulkanConfigData
    {
        std::vector<VkPhysicalDevice> gpus;
        std::vector<VkQueueFamilyProperties> queueFamilyProperties;
        uint32_t queueFamilyIndex;

        // createSwapChain
        std::vector<VkSurfaceFormatKHR> surfaceFormats;
        std::vector<VkPresentModeKHR> presentModes;
        std::vector<VkImage> swapChainImages;
        VkFormat format;
        VkExtent2D maxViewport;

        // Supported GLFW Window Extensions
        uint32_t windowExtensionCount;
        std::vector<const char*> windowExtensions;
    };
    /**
    *
    */
    class VulkanConfig : public spark::renderer::ISparkRendererApiConfig
    {
    public:
        VulkanConfig(spark::device::window::ISparkWindow* window, spark::log::ISparkLogger* logger);
        ~VulkanConfig();

    public:
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
        const bool ENABLE_VULKAN_DEBUGGING = false;

    private:
        spark::renderer::VulkanConfigData m_vulkanConfig = {};
    };
};
#endif
#endif
