#include "Vulkan13Renderer.hpp"
#if SPARK_COMPILE_VULKAN == 0x1

namespace spark {
    namespace renderer {
        /**
        *
        */
        Vulkan13Renderer::Vulkan13Renderer(spark::device::ISparkDevice* device, spark::renderer::shader::ISparkShader* shader) :
            VulkanRenderer(device, shader),
            m_vkInstance(NULL)
        {
            VkApplicationInfo appInfo{};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = "libsparkling";
            appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.pEngineName = "libspakling";
            appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.apiVersion = VK_API_VERSION_1_0;

            VkInstanceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pApplicationInfo = &appInfo;
            //createInfo.enabledExtensionCount = glfwExtensionCount;
            //createInfo.ppEnabledExtensionNames = glfwExtensions;
            createInfo.enabledLayerCount = 0;

            VkResult result = vkCreateInstance(&createInfo, nullptr, &m_vkInstance);
        }

        /**
        *
        */
        Vulkan13Renderer::~Vulkan13Renderer()
        {

        }

        /**
        *
        */
        void Vulkan13Renderer::onInit()
        {

        }
    } // end namespace renderer
} // end namespace spark
#endif