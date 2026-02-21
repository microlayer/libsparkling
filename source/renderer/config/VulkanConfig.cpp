#include "VulkanConfig.hpp"
#if SPARK_COMPILE_VULKAN == 0x1

namespace spark::renderer {
    /**
    *
    */
    VulkanConfig::VulkanConfig(spark::device::window::ISparkWindow* window, spark::log::ISparkLogger* logger) :
        m_window(window),
        m_logger(logger),
        m_vkInstance(NULL)
    {
        onInit();
    }

    /**
    *
    */
    VulkanConfig::~VulkanConfig()
    {
        vkDestroyDevice(m_device, NULL);
        vkDestroyInstance(m_vkInstance, NULL);
    }

    void VulkanConfig::onInit()
    {
        createInstance();
        createDebugCallback();
        createWindowSurface();
        findPhysicalDevices();
        createLogicalDevice();
        createCommandBuffer();
        isSwapChainSupportAvailable();
        createSwapChain();
        createRenderPass();
        createPipeline();
    }

    /**
    *
    */
    void VulkanConfig::createInstance()
    {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "libsparkling";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "libspakling";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        // Get required instance extensions
        glfwGetRequiredInstanceExtensions(&m_vulkanConfig.windowExtensionCount);
        const char** glwfExtension = glfwGetRequiredInstanceExtensions(&m_vulkanConfig.windowExtensionCount);
        for (uint32_t i = 0; i < m_vulkanConfig.windowExtensionCount; ++i)
        {
            m_vulkanConfig.windowExtensions.push_back(glwfExtension[i]);
        }

        // Enumerate available Layers
        uint32_t instanceLayerCount = 0;
        if (vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr) != VK_SUCCESS)
        {
            m_logger->error("Failed to get instance layers count");
        }

        std::vector<VkLayerProperties> availableInstanceLayers(instanceLayerCount);
        if (vkEnumerateInstanceLayerProperties(&instanceLayerCount, availableInstanceLayers.data()) != VK_SUCCESS)
        {
            m_logger->error("Failed to enumerate instance layers");
        }

        std::vector<const char*> layerNames;
        m_logger->info("Available layers:");
        for (auto& layer : availableInstanceLayers)
        {
            m_logger->info(layer.layerName);
            layerNames.push_back(layer.layerName);
        }

        std::vector<const char*> enabledLayers;
        if (ENABLE_VULKAN_DEBUGGING)
        {
            enabledLayers.push_back("VK_LAYER_KHRONOS_validation");
        }

        // Enumerate available instance Extensions
        uint32_t extensionPropertiesCount = 0;
        if (vkEnumerateInstanceExtensionProperties(nullptr, &extensionPropertiesCount, nullptr) != VK_SUCCESS)
        {
            m_logger->error("Failed to get count of instance extension prperties");
        }

        std::vector<VkExtensionProperties> extensionProperties(extensionPropertiesCount);
        if (vkEnumerateInstanceExtensionProperties(nullptr, &extensionPropertiesCount, extensionProperties.data()) != VK_SUCCESS)
        {
            m_logger->error("Failed to enumerate instance extension prperties");
        }
        m_logger->info("Available instance extensions:");
        for (auto& extension : extensionProperties)
        {
            m_logger->info(extension.extensionName);
        }

        VkInstanceCreateInfo instanceCreateInfo{};
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pApplicationInfo = &appInfo;
        instanceCreateInfo.enabledExtensionCount = m_vulkanConfig.windowExtensionCount;
        instanceCreateInfo.ppEnabledExtensionNames = m_vulkanConfig.windowExtensions.data();
        instanceCreateInfo.enabledLayerCount = enabledLayers.size();
        instanceCreateInfo.ppEnabledLayerNames = enabledLayers.data();
        VkResult ret = vkCreateInstance(&instanceCreateInfo, nullptr, &m_vkInstance);
        if (ret != VK_SUCCESS)
        {
            m_logger->error("Failed to create vulkan instance!");
            if (ret == VK_ERROR_INCOMPATIBLE_DRIVER)
            {
                m_logger->error("Cannot find a compatible Vulkan ICD!");
                exit(1);
            }
        }
        else
        {
            m_logger->info("Vulkan instance successfully created");
        }
    }

    /**
    *
    */
    void VulkanConfig::createDebugCallback()
    {
        VkDebugReportCallbackCreateInfoEXT debugReportCallbackCreateInfo = {};
        debugReportCallbackCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
        debugReportCallbackCreateInfo.pfnCallback = (PFN_vkDebugReportCallbackEXT)debugCallback;
        debugReportCallbackCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
        PFN_vkCreateDebugReportCallbackEXT CreateDebugReportCallback = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(m_vkInstance, "vkCreateDebugReportCallbackEXT");
    }

    /**
    *
    */
    void VulkanConfig::createWindowSurface()
    {
        GLFWwindow* wnd = reinterpret_cast<GLFWwindow*>(m_window->getNativeWindow());
        if (glfwCreateWindowSurface(m_vkInstance, wnd, NULL, &m_windowSurface) != VK_SUCCESS)
        {
            m_logger->error("Failed to create window surface!");
        }
        m_logger->info("Window surface successfully created");
    }

    /**
    *
    */
    void VulkanConfig::findPhysicalDevices()
    {
        uint32_t deviceCount = 0;
        if (vkEnumeratePhysicalDevices(m_vkInstance, &deviceCount, nullptr) != VK_SUCCESS || deviceCount == 0)
        {
            m_logger->error("Failed to get number of physical devices!");
            exit(1);
        }

        m_vulkanConfig.gpus.resize(deviceCount);
        VkResult res = vkEnumeratePhysicalDevices(m_vkInstance, &deviceCount, m_vulkanConfig.gpus.data());
        if (res != VK_SUCCESS && res != VK_INCOMPLETE)
        {
            m_logger->error("Enumerating physical devices failed!");
            exit(1);
        }

        for (uint32_t i = 0; i < deviceCount; ++i)
        {
            VkPhysicalDeviceProperties deviceProperties;
            vkGetPhysicalDeviceProperties(m_vulkanConfig.gpus[i], &deviceProperties);
            m_logger->info((std::string("Device name: ") + std::string(deviceProperties.deviceName)).c_str());
        }
    }

    /**
    * Create logical device
    */
    void VulkanConfig::createLogicalDevice()
    {
        uint32_t queueFamilyCount = 0;
        const float priorities[]{ 1.0f };
        vkGetPhysicalDeviceQueueFamilyProperties(m_vulkanConfig.gpus[0], &queueFamilyCount, nullptr);

        m_vulkanConfig.queueFamilyProperties.resize(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(m_vulkanConfig.gpus[0], &queueFamilyCount, m_vulkanConfig.queueFamilyProperties.data());

        VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};
        deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        deviceQueueCreateInfo.pQueuePriorities = priorities;
        deviceQueueCreateInfo.queueCount = 1;
        for (uint32_t i = 0; i < queueFamilyCount; i++)
        {
            if (m_vulkanConfig.queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                deviceQueueCreateInfo.queueFamilyIndex = i;
                m_vulkanConfig.queueFamilyIndex = i;
            }
        }

        // Device Extensions                  
        std::vector<const char*> deviceExtensions;
        deviceExtensions.push_back(VK_KHR_DRIVER_PROPERTIES_EXTENSION_NAME);
        deviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

        // device features
        VkPhysicalDeviceFeatures deviceFeatures = {};
        deviceFeatures.shaderClipDistance = VK_TRUE;
        deviceFeatures.shaderCullDistance = VK_TRUE;

        VkDeviceCreateInfo deviceCreateInfo = {};
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.pNext = NULL;
        deviceCreateInfo.queueCreateInfoCount = 1;
        deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
        deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();
        deviceCreateInfo.enabledLayerCount = 0;
        deviceCreateInfo.ppEnabledLayerNames = NULL;
        deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
        if (vkCreateDevice(m_vulkanConfig.gpus[0], &deviceCreateInfo, NULL, &m_device) != VK_SUCCESS)
        {
            m_logger->error("Failed to create device!");
        }
        else
        {
            m_logger->info("Logical device successfully created");
        }
    }

    /**
    *
    */
    void VulkanConfig::createCommandBuffer()
    {
        // Create graphics command pool
        VkCommandPoolCreateInfo poolCreateInfo = {};
        poolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolCreateInfo.queueFamilyIndex = m_vulkanConfig.queueFamilyIndex;

        if (vkCreateCommandPool(m_device, &poolCreateInfo, nullptr, &m_commandPool) != VK_SUCCESS)
        {
            m_logger->error("Failed to create command buffer queue for graphics queue family!");
            exit(1);
        }
        else
        {
            m_logger->info("Command buffer for graphics queue family successfully created");
        }
    }

    /**
    *
    */
    void VulkanConfig::isSwapChainSupportAvailable()
    {
        uint32_t deviceExtensionCount = 0;
        vkEnumerateDeviceExtensionProperties(m_vulkanConfig.gpus[0], nullptr, &deviceExtensionCount, nullptr);

        if (deviceExtensionCount == 0)
        {
            m_logger->error("Physical device doesn't support any extensions");
            exit(1);
        }

        std::vector<VkExtensionProperties> deviceExtensions(deviceExtensionCount);
        vkEnumerateDeviceExtensionProperties(m_vulkanConfig.gpus[0], nullptr, &deviceExtensionCount, deviceExtensions.data());

        for (const auto& extension : deviceExtensions)
        {
            if (strcmp(extension.extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME) == 0)
            {
                m_logger->info("Physical device supports swap chains");
            }
        }
    }

    /**
    *
    */
    void VulkanConfig::createSwapChain()
    {
        // Find surface capabilities
        VkSurfaceCapabilitiesKHR surfaceCapabilities;
        if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_vulkanConfig.gpus[0], m_windowSurface, &surfaceCapabilities) != VK_SUCCESS)
        {
            m_logger->error("Failed to acquire presentation surface capabilities");
            exit(1);
        }

        // Find supported surface formats
        uint32_t formatCount;
        if (vkGetPhysicalDeviceSurfaceFormatsKHR(m_vulkanConfig.gpus[0], m_windowSurface, &formatCount, nullptr) != VK_SUCCESS || formatCount == 0)
        {
            m_logger->error("Failed to get number of supported surface formats");
            exit(1);
        }

        m_vulkanConfig.surfaceFormats.resize(formatCount);
        if (vkGetPhysicalDeviceSurfaceFormatsKHR(m_vulkanConfig.gpus[0], m_windowSurface, &formatCount, m_vulkanConfig.surfaceFormats.data()) != VK_SUCCESS)
        {
            m_logger->error("Failed to get supported surface formats");
            exit(1);
        }

        // Set format to VK_FORMAT_B8G8R8A8_UNORM
        m_vulkanConfig.format = VK_FORMAT_B8G8R8A8_UNORM;

        // Find supported present modes
        uint32_t presentModeCount;
        if (vkGetPhysicalDeviceSurfacePresentModesKHR(m_vulkanConfig.gpus[0], m_windowSurface, &presentModeCount, nullptr) != VK_SUCCESS || presentModeCount == 0)
        {
            m_logger->error("Failed to get number of supported presentation modes");
            exit(1);
        }

        m_vulkanConfig.presentModes.resize(presentModeCount);
        if (vkGetPhysicalDeviceSurfacePresentModesKHR(m_vulkanConfig.gpus[0], m_windowSurface, &presentModeCount, m_vulkanConfig.presentModes.data()) != VK_SUCCESS)
        {
            m_logger->error("Failed to get supported presentation modes");
            exit(1);
        }

        // First check if queue family has at least 1 queue in that family (could have no queues)
        // Check if Queue Family supports presentation
        for (const auto& queueFamily : m_vulkanConfig.queueFamilyProperties)
        {
            VkBool32 presentationSupport = false;
            VkResult result = vkGetPhysicalDeviceSurfaceSupportKHR(m_vulkanConfig.gpus[0], 0, m_windowSurface, &presentationSupport);
            if (queueFamily.queueCount > 0 && presentationSupport)
            {
                m_logger->info("Queue Family supports presentation");
            }
        }

        uint32_t imageCount = surfaceCapabilities.minImageCount;
        m_logger->info((std::string("Using ") + std::to_string(imageCount) + std::string(" images for swap chain")).c_str());

        // Select standard format - if available
        VkSurfaceFormatKHR surfaceFormat = {};
        for (const auto& availableSurfaceFormat : m_vulkanConfig.surfaceFormats)
        {
            if (availableSurfaceFormat.format == VK_FORMAT_B8G8R8A8_UNORM)
            {
                surfaceFormat = availableSurfaceFormat;
            }
        }

        // Select swap chain size
        VkExtent2D swapChainExtent = surfaceCapabilities.currentExtent;
        m_vulkanConfig.maxViewport = surfaceCapabilities.currentExtent;

        // Determine transformation to use (preferring no transform)
        VkSurfaceTransformFlagBitsKHR surfaceTransform;
        if (surfaceCapabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
        {
            surfaceTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
        }
        else
        {
            surfaceTransform = surfaceCapabilities.currentTransform;
        }

        // Choose presentation mode (preferring MAILBOX ~= triple buffering)
        VkPresentModeKHR presentMode = VK_PRESENT_MODE_MAILBOX_KHR;

        // Finally, create the swap chain
        VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
        swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchainCreateInfo.pNext = nullptr;
        swapchainCreateInfo.surface = m_windowSurface;
        swapchainCreateInfo.minImageCount = imageCount;
        swapchainCreateInfo.imageFormat = m_vulkanConfig.format;
        swapchainCreateInfo.imageColorSpace = surfaceFormat.colorSpace;
        swapchainCreateInfo.imageExtent = swapChainExtent;
        swapchainCreateInfo.imageArrayLayers = 1;
        swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapchainCreateInfo.queueFamilyIndexCount = 0;
        swapchainCreateInfo.pQueueFamilyIndices = nullptr;
        swapchainCreateInfo.preTransform = surfaceTransform;
        swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapchainCreateInfo.presentMode = presentMode;
        swapchainCreateInfo.clipped = VK_TRUE;
        swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;
        if (vkCreateSwapchainKHR(m_device, &swapchainCreateInfo, nullptr, &m_swapChain) != VK_SUCCESS)
        {
            m_logger->error("Failed to create swap chain");
            exit(1);
        }
        else
        {
            m_logger->info("Swap chain successfully created");
        }

        // Get the images used by the swap chain            
        uint32_t actualImageCount = 0;
        if (vkGetSwapchainImagesKHR(m_device, m_swapChain, &actualImageCount, nullptr) != VK_SUCCESS || actualImageCount == 0)
        {
            m_logger->error("Failed to acquire number of swap chain images");
            exit(1);
        }

        if (vkGetSwapchainImagesKHR(m_device, m_swapChain, &actualImageCount, m_vulkanConfig.swapChainImages.data()) != VK_SUCCESS)
        {
            m_logger->error("Failed to acquire swap chain images");
            exit(1);
        }
        m_logger->info("Swap chain images successfully acquired");
    }

    /**
    *
    */
    void VulkanConfig::createRenderPass()
    {
        VkAttachmentDescription attachmentDescription = {};
        attachmentDescription.format = m_vulkanConfig.surfaceFormats[0].format;
        attachmentDescription.samples = VK_SAMPLE_COUNT_1_BIT;
        attachmentDescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        attachmentDescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        attachmentDescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        attachmentDescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachmentDescription.initialLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        attachmentDescription.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        // Note: hardware will automatically transition attachment to the specified layout
        // Note: index refers to attachment descriptions array
        VkAttachmentReference colorAttachmentReference = {};
        colorAttachmentReference.attachment = 0;
        colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        // Note: this is a description of how the attachments of the render pass will be used in this sub pass
        // e.g. if they will be read in shaders and/or drawn to
        VkSubpassDescription subPassDescription = {};
        subPassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subPassDescription.colorAttachmentCount = 1;
        subPassDescription.pColorAttachments = &colorAttachmentReference;

        // Create the render pass
        VkRenderPassCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        createInfo.attachmentCount = 1;
        createInfo.pAttachments = &attachmentDescription;
        createInfo.subpassCount = 1;
        createInfo.pSubpasses = &subPassDescription;

        if (vkCreateRenderPass(m_device, &createInfo, nullptr, &m_renderPass) != VK_SUCCESS)
        {
            m_logger->error("Failed to create render pass");
            exit(1);
        }
        else {
            m_logger->info("Render pass successfully created");
        }
    }

    /**
    *
    */
    void VulkanConfig::createPipeline()
    {
        spark::renderer::shader::glsl_for_spir_feature_level_glsles10::DefaultShader defaultShader;
        std::vector<uc8_t> vertexShaderStream = spark::mlstl::base64::MLBase64::decode(defaultShader.getVertexShader());
        std::vector<uc8_t> fragmentShaderStream = spark::mlstl::base64::MLBase64::decode(defaultShader.getFragmentShader());

        VkShaderModuleCreateInfo vertexShaderCreateInfo = {};
        vertexShaderCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        vertexShaderCreateInfo.codeSize = 4 * (uint32_t)vertexShaderStream.size();      // SPIR-V code, codeSize must be a multiple of 4
        vertexShaderCreateInfo.pCode = (uint32_t*)vertexShaderStream.data();

        VkShaderModuleCreateInfo fragmentShaderCreateInfo = {};
        fragmentShaderCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        fragmentShaderCreateInfo.codeSize = 4 * (uint32_t)fragmentShaderStream.size();  // SPIR-V code, codeSize must be a multiple of 4
        fragmentShaderCreateInfo.pCode = (uint32_t*)fragmentShaderStream.data();

        VkShaderModule vertexShaderModule = {};
        if (vkCreateShaderModule(m_device, &vertexShaderCreateInfo, nullptr, &vertexShaderModule) != VK_SUCCESS)
        {
            m_logger->info("Failed to create vertex shader module");
            exit(1);
        }
        m_logger->info("Vertex shader modul successfully created");

        VkShaderModule fragmentShaderModule = {};
        if (vkCreateShaderModule(m_device, &fragmentShaderCreateInfo, nullptr, &fragmentShaderModule) != VK_SUCCESS)
        {
            m_logger->info("Failed to create fragment shader module");
            exit(1);
        }
        m_logger->info("Fragment shader modul successfully created");

        VkPipelineShaderStageCreateInfo vertexShaderStageCreateInfo = {};
        vertexShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertexShaderStageCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertexShaderStageCreateInfo.module = vertexShaderModule;
        vertexShaderStageCreateInfo.pName = "main";

        VkPipelineShaderStageCreateInfo fragmentShaderStageCreateInfo = {};
        fragmentShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragmentShaderStageCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragmentShaderStageCreateInfo.module = fragmentShaderModule;
        fragmentShaderStageCreateInfo.pName = "main";

        VkPipelineShaderStageCreateInfo shaderStages[] = { vertexShaderStageCreateInfo, fragmentShaderStageCreateInfo };

        // Describe vertex input
        VkPipelineVertexInputStateCreateInfo vertexInputCreateInfo = {};
        vertexInputCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertexInputCreateInfo.vertexBindingDescriptionCount = 1;
        vertexInputCreateInfo.pVertexBindingDescriptions = &m_vertexBindingDescription;
        vertexInputCreateInfo.vertexAttributeDescriptionCount = m_vertexAttributeDescriptions.size();
        vertexInputCreateInfo.pVertexAttributeDescriptions = m_vertexAttributeDescriptions.data();

        // Describe input assembly
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyCreateInfo = {};
        inputAssemblyCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssemblyCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssemblyCreateInfo.primitiveRestartEnable = VK_FALSE;

        // Describe viewport
        VkViewport viewport = {};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)m_vulkanConfig.maxViewport.width;
        viewport.height = (float)m_vulkanConfig.maxViewport.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        // Describe scissor
        VkRect2D scissor = {};
        scissor.offset.x = 0;
        scissor.offset.y = 0;
        scissor.extent.width = m_vulkanConfig.maxViewport.width;
        scissor.extent.height = m_vulkanConfig.maxViewport.height;

        VkPipelineViewportStateCreateInfo viewportCreateInfo = {};
        viewportCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportCreateInfo.viewportCount = 1;
        viewportCreateInfo.pViewports = &viewport;
        viewportCreateInfo.scissorCount = 1;
        viewportCreateInfo.pScissors = &scissor;

        // Describe rasterization            
        VkPipelineRasterizationStateCreateInfo rasterizationCreateInfo = {};
        rasterizationCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizationCreateInfo.depthClampEnable = VK_FALSE;
        rasterizationCreateInfo.rasterizerDiscardEnable = VK_FALSE;
        rasterizationCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizationCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterizationCreateInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        rasterizationCreateInfo.depthBiasEnable = VK_FALSE;
        rasterizationCreateInfo.depthBiasConstantFactor = 0.0f;
        rasterizationCreateInfo.depthBiasClamp = 0.0f;
        rasterizationCreateInfo.depthBiasSlopeFactor = 0.0f;
        rasterizationCreateInfo.lineWidth = 1.0f;

        // Describe multisampling            
        VkPipelineMultisampleStateCreateInfo multisampleCreateInfo = {};
        multisampleCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampleCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        multisampleCreateInfo.sampleShadingEnable = VK_FALSE;
        multisampleCreateInfo.minSampleShading = 1.0f;
        multisampleCreateInfo.alphaToCoverageEnable = VK_FALSE;
        multisampleCreateInfo.alphaToOneEnable = VK_FALSE;

        // Describing color blending            
        VkPipelineColorBlendAttachmentState colorBlendAttachmentState = {};
        colorBlendAttachmentState.blendEnable = VK_FALSE;
        colorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
        colorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
        colorBlendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;
        colorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        colorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        colorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;
        colorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

        VkPipelineColorBlendStateCreateInfo colorBlendCreateInfo = {};
        colorBlendCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlendCreateInfo.logicOpEnable = VK_FALSE;
        colorBlendCreateInfo.logicOp = VK_LOGIC_OP_COPY;
        colorBlendCreateInfo.attachmentCount = 1;
        colorBlendCreateInfo.pAttachments = &colorBlendAttachmentState;
        colorBlendCreateInfo.blendConstants[0] = 0.0f;
        colorBlendCreateInfo.blendConstants[1] = 0.0f;
        colorBlendCreateInfo.blendConstants[2] = 0.0f;
        colorBlendCreateInfo.blendConstants[3] = 0.0f;

        // Describe pipeline layout           
        VkDescriptorSetLayoutBinding descriptorLayoutBinding = {};
        descriptorLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorLayoutBinding.descriptorCount = 1;
        descriptorLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutCreateInfo descriptorLayoutCreateInfo = {};
        descriptorLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        descriptorLayoutCreateInfo.bindingCount = 1;
        descriptorLayoutCreateInfo.pBindings = &descriptorLayoutBinding;
        if (vkCreateDescriptorSetLayout(m_device, &descriptorLayoutCreateInfo, nullptr, &m_descriptorSetLayout) != VK_SUCCESS)
        {
            m_logger->info("Failed to create descriptor layout");
            exit(1);
        }
        else
        {
            m_logger->info("Descriptor layout created successfully");
        }

        VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
        pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutCreateInfo.setLayoutCount = 1;
        pipelineLayoutCreateInfo.pSetLayouts = &m_descriptorSetLayout;
        if (vkCreatePipelineLayout(m_device, &pipelineLayoutCreateInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS)
        {
            m_logger->info("Failed to create pipeline layout");
            exit(1);
        }
        else
        {
            m_logger->info("Pipeline layout created");
        }

        // Create the graphics pipeline
        VkGraphicsPipelineCreateInfo pipelineCreateInfo = {};
        pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineCreateInfo.stageCount = 2;
        pipelineCreateInfo.pStages = shaderStages;
        pipelineCreateInfo.pVertexInputState = &vertexInputCreateInfo;
        pipelineCreateInfo.pInputAssemblyState = &inputAssemblyCreateInfo;
        pipelineCreateInfo.pViewportState = &viewportCreateInfo;
        pipelineCreateInfo.pRasterizationState = &rasterizationCreateInfo;
        pipelineCreateInfo.pMultisampleState = &multisampleCreateInfo;
        pipelineCreateInfo.pColorBlendState = &colorBlendCreateInfo;
        pipelineCreateInfo.layout = m_pipelineLayout;
        pipelineCreateInfo.renderPass = m_renderPass;
        pipelineCreateInfo.subpass = 0;
        pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
        pipelineCreateInfo.basePipelineIndex = -1;
        if (vkCreateGraphicsPipelines(m_device, VK_NULL_HANDLE, 1, &pipelineCreateInfo, nullptr, &m_graphicsPipeline) != VK_SUCCESS)
        {
            m_logger->info("Failed to create graphics pipeline");
            exit(1);
        }
        else
        {
            m_logger->info("Graphics pipeline created successful");
        }
    }

    /**
    *
    */
    VkBool32 VulkanConfig::debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t srcObject, size_t location, int32_t msgCode, const char* pLayerPrefix, const char* pMsg, void* pUserData)
    {
        return true;
    }
}
#endif