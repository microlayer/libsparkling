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
            m_logger = device->getLogger();
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
            createInstance();
            createDebugCallback();
            createWindowSurface();
            findPhysicalDevice();
            findQueueFamilies();
            createLogicalDevice();
            createPipeline();
        }

        /**
        *
        */
        void Vulkan13Renderer::createInstance()
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
        void Vulkan13Renderer::createDebugCallback()
        {
            VkDebugReportCallbackCreateInfoEXT createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
            createInfo.pfnCallback = (PFN_vkDebugReportCallbackEXT)debugCallback;
            createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
            PFN_vkCreateDebugReportCallbackEXT CreateDebugReportCallback = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(m_vkInstance, "vkCreateDebugReportCallbackEXT");
        }

        /**
        *
        */
        void Vulkan13Renderer::createWindowSurface()
        {
            //if (glfwCreateWindowSurface(m_vkInstance, window, NULL, &m_windowSurface) != VK_SUCCESS) 
            //{                
            //}
        }

        /**
        *
        */
        void Vulkan13Renderer::findPhysicalDevice()
        {
            uint32_t deviceCount = 0;
            if (vkEnumeratePhysicalDevices(m_vkInstance, &deviceCount, nullptr) != VK_SUCCESS || deviceCount == 0)
            {
                m_logger->error("Failed to get number of physical devices!");
                exit(1);
            }

            deviceCount = 1;
            VkResult res = vkEnumeratePhysicalDevices(m_vkInstance, &deviceCount, &m_physicalDevice);
            if (res != VK_SUCCESS && res != VK_INCOMPLETE) {
                m_logger->error("Enumerating physical devices failed!");
                exit(1);
            }

            if (deviceCount == 0) {
                m_logger->info("No physical devices that supports vulkan found!");
                exit(1);
            }
        }

        /**
        *
        */
        void Vulkan13Renderer::findQueueFamilies()
        {
            uint32_t queueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, nullptr);
        }

        /**
        * Greate one graphics queue
        */
        void Vulkan13Renderer::createLogicalDevice()
        {
            float queuePriority = 1.0f;

            VkDeviceQueueCreateInfo queueCreateInfo[2] = {};

            queueCreateInfo[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo[0].queueFamilyIndex = m_graphicsQueueFamily;
            queueCreateInfo[0].queueCount = 1;
            queueCreateInfo[0].pQueuePriorities = &queuePriority;

            queueCreateInfo[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo[1].queueFamilyIndex = m_graphicsQueueFamily;
            queueCreateInfo[1].queueCount = 1;
            queueCreateInfo[1].pQueuePriorities = &queuePriority;

            // Create logical device from physical device
            // Note: there are separate instance and device extensions!
            VkDeviceCreateInfo deviceCreateInfo = {};
            deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            deviceCreateInfo.pQueueCreateInfos = queueCreateInfo;

            if (m_graphicsQueueFamily == m_presentQueueFamily)
            {
                deviceCreateInfo.queueCreateInfoCount = 1;
            }
            else
            {
                deviceCreateInfo.queueCreateInfoCount = 2;
            }

            // Necessary for shader (for some reason)
            VkPhysicalDeviceFeatures enabledFeatures = {};
            enabledFeatures.shaderClipDistance = VK_TRUE;
            enabledFeatures.shaderCullDistance = VK_TRUE;

            const char* deviceExtensions = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
            deviceCreateInfo.enabledExtensionCount = 1;
            deviceCreateInfo.ppEnabledExtensionNames = &deviceExtensions;
            deviceCreateInfo.pEnabledFeatures = &enabledFeatures;

            if (ENABLE_DEBUGGING) {
                deviceCreateInfo.enabledLayerCount = 1;
                deviceCreateInfo.ppEnabledLayerNames = &DEBUG_LAYER;
            }

            if (vkCreateDevice(m_physicalDevice, &deviceCreateInfo, nullptr, &m_device) != VK_SUCCESS) {
                m_logger->info("Failed to create logical device");
                exit(1);
            }

            m_logger->info("Logical device created");

            // Get graphics and presentation queues (which may be the same)
            vkGetDeviceQueue(m_device, m_graphicsQueueFamily, 0, &m_graphicsQueue);
            vkGetDeviceQueue(m_device, m_presentQueueFamily, 0, &m_graphicsQueue);

            m_logger->info("Acquired graphics and presentation queues");

            vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &m_physicalDeviceMemoryProperties);
        }

        void Vulkan13Renderer::createCommandPool()
        {
            // Create graphics command pool
            VkCommandPoolCreateInfo poolCreateInfo = {};
            poolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
            poolCreateInfo.queueFamilyIndex = m_graphicsQueueFamily;

            if (vkCreateCommandPool(m_device, &poolCreateInfo, nullptr, &m_commandPool) != VK_SUCCESS)
            {
                std::cerr << "failed to create command queue for graphics queue family" << std::endl;
                exit(1);
            }
            else {
                std::cout << "created command pool for graphics queue family" << std::endl;
            }
        }

        /**
        *
        */
        void Vulkan13Renderer::createPipeline()
        {
            spark::renderer::shader::glsl_for_spir_feature_level_glsles10::DefaultShader defaultShader;
            std::vector<uc8_t> vertexShaderStream = spark::mlstl::base64::MLBase64::Decode(defaultShader.getVertexShader());
            std::vector<uc8_t> fragmentShaderStream = spark::mlstl::base64::MLBase64::Decode(defaultShader.getFragmentShader());

            VkShaderModuleCreateInfo vertexShaderCreateInfo = {};
            vertexShaderCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
            vertexShaderCreateInfo.codeSize = vertexShaderStream.size();
            vertexShaderCreateInfo.pCode = (uint32_t*)vertexShaderStream.data();

            VkShaderModuleCreateInfo fragmentShaderCreateInfo = {};
            fragmentShaderCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
            fragmentShaderCreateInfo.codeSize = fragmentShaderStream.size();
            fragmentShaderCreateInfo.pCode = (uint32_t*)fragmentShaderStream.data();

            VkShaderModule vertexShaderModule;
            if (vkCreateShaderModule(m_device, &vertexShaderCreateInfo, nullptr, &vertexShaderModule) != VK_SUCCESS)
            {
                m_logger->info("Failed to create vertex shader module");
                exit(1);
            }
            m_logger->info("Vertex shader modul successfully created");

            VkShaderModule fragmentShaderModule;
            if (vkCreateShaderModule(m_device, &vertexShaderCreateInfo, nullptr, &fragmentShaderModule) != VK_SUCCESS)
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
            vertexInputCreateInfo.vertexAttributeDescriptionCount = 2;
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
            viewport.width = 640;
            viewport.height = 480;
            viewport.minDepth = 0.0f;
            viewport.maxDepth = 1.0f;

            // Describe scissor
            VkRect2D scissor = {};
            scissor.offset.x = 0;
            scissor.offset.y = 0;
            scissor.extent.width = 640;
            scissor.extent.height = 480;

            VkPipelineViewportStateCreateInfo viewportCreateInfo = {};
            viewportCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
            viewportCreateInfo.viewportCount = 1;
            viewportCreateInfo.pViewports = &viewport;
            viewportCreateInfo.scissorCount = 1;
            viewportCreateInfo.pScissors = &scissor;

            // Describe rasterization
            // Note: depth bias and using polygon modes other than fill require changes to logical device creation (device features)
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
            // Note: using multisampling also requires turning on device features
            VkPipelineMultisampleStateCreateInfo multisampleCreateInfo = {};
            multisampleCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
            multisampleCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
            multisampleCreateInfo.sampleShadingEnable = VK_FALSE;
            multisampleCreateInfo.minSampleShading = 1.0f;
            multisampleCreateInfo.alphaToCoverageEnable = VK_FALSE;
            multisampleCreateInfo.alphaToOneEnable = VK_FALSE;

            // Describing color blending
            // Note: all paramaters except blendEnable and colorWriteMask are irrelevant here
            VkPipelineColorBlendAttachmentState colorBlendAttachmentState = {};
            colorBlendAttachmentState.blendEnable = VK_FALSE;
            colorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
            colorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
            colorBlendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;
            colorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
            colorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
            colorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;
            colorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

            // Note: all attachments must have the same values unless a device feature is enabled
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
            // Note: this describes the mapping between memory and shader resources (descriptor sets)
            // This is for uniform buffers and samplers
            VkDescriptorSetLayoutBinding layoutBinding = {};
            layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            layoutBinding.descriptorCount = 1;
            layoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

            VkDescriptorSetLayoutCreateInfo descriptorLayoutCreateInfo = {};
            descriptorLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
            descriptorLayoutCreateInfo.bindingCount = 1;
            descriptorLayoutCreateInfo.pBindings = &layoutBinding;

            if (vkCreateDescriptorSetLayout(m_device, &descriptorLayoutCreateInfo, nullptr, &m_descriptorSetLayout) != VK_SUCCESS)
            {
                m_logger->info("Failed to create descriptor layout");
                exit(1);
            }
            else
            {
                m_logger->info("Descriptor layout created successfully");
            }

            VkPipelineLayoutCreateInfo layoutCreateInfo = {};
            layoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
            layoutCreateInfo.setLayoutCount = 1;
            layoutCreateInfo.pSetLayouts = &m_descriptorSetLayout;

            if (vkCreatePipelineLayout(m_device, &layoutCreateInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS)
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
            //pipelineCreateInfo.renderPass = renderPass;
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
        VkBool32 Vulkan13Renderer::debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t srcObject, size_t location, int32_t msgCode, const char* pLayerPrefix, const char* pMsg, void* pUserData)
        {
            return true;
        }
    } // end namespace renderer
} // end namespace spark
#endif