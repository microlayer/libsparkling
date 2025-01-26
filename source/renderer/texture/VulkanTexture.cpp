#include "VulkanTexture.hpp"
#if SPARK_COMPILE_VULKAN == 0x1

namespace spark {
    namespace renderer {
        namespace vulkan {
            /**
            *
            */
            VulkanTexture::VulkanTexture(
                spark::log::ISparkLogger* logger,
                uc8_t* data,
                int32_t width,
                int32_t height,
                spark::drawing::E_PIXEL_FORMAT pixelFormat) :
                m_logger(logger),
                m_data(data),
                m_width(width),
                m_height(height),
                m_textureId(0)
            {
                // 
                VkDevice device{};
                VkImage image;

                // Create VkImage
                VkImageCreateInfo imageInfo = {};
                imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
                imageInfo.imageType = VK_IMAGE_TYPE_2D;
                imageInfo.extent.width = m_width;
                imageInfo.extent.height = m_height;
                imageInfo.extent.depth = 1;
                imageInfo.mipLevels = 1;
                imageInfo.arrayLayers = 1;
                imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
                imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
                imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
                imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
                imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

                vkCreateImage(device, &imageInfo, nullptr, &image);

                // Allocate and Bind Memory
                VkMemoryRequirements memRequirements;
                vkGetImageMemoryRequirements(device, image, &memRequirements);

                VkMemoryAllocateInfo allocInfo = {};
                allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
                allocInfo.allocationSize = memRequirements.size;
                allocInfo.memoryTypeIndex = 0;

                vkAllocateMemory(device, &allocInfo, nullptr, &image);
                vkBindImageMemory(device, image, image, 0);

                // Transition Image Layout and Upload Data
                //transitionImageLayout(texture.image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, device, commandPool, queue);
                //copyBufferToImage(stagingBuffer, texture.image, image.width, image.height, commandPool, queue);
                //transitionImageLayout(texture.image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, device, commandPool, queue);

                // Create Image View
                VkImageViewCreateInfo viewInfo = {};
                viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
                viewInfo.image = image;
                viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
                viewInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
                viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
                viewInfo.subresourceRange.baseMipLevel = 0;
                viewInfo.subresourceRange.levelCount = 1;
                viewInfo.subresourceRange.baseArrayLayer = 0;
                viewInfo.subresourceRange.layerCount = 1;

                //vkCreateImageView(device, &viewInfo, nullptr, &texture.imageView);

                // Create Sampler
                VkSamplerCreateInfo samplerInfo = {};
                samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
                samplerInfo.magFilter = VK_FILTER_LINEAR;
                samplerInfo.minFilter = VK_FILTER_LINEAR;
                samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
                samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
                samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
                samplerInfo.anisotropyEnable = VK_TRUE;
                samplerInfo.maxAnisotropy = 16;
                samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
                samplerInfo.unnormalizedCoordinates = VK_FALSE;

                //vkCreateSampler(device, &samplerInfo, nullptr, &texture.sampler);                
            }

            /**
            *
            */
            VulkanTexture::~VulkanTexture()
            {

            }
            /**
            *
            */
            uc8_t* VulkanTexture::getImageAsStream() const
            {
                return m_data;
            }

            /**
            *
            */
            uint32_t VulkanTexture::getWidth() const
            {
                return m_width;
            }

            /**
            *
            */
            uint32_t VulkanTexture::getHeight() const
            {
                return m_height;
            }

            /**
            *
            */
            spark::drawing::E_PIXEL_FORMAT VulkanTexture::getPixelFormat() const
            {
                return spark::drawing::E_PIXEL_FORMAT::E_GRAY8;
            }

            /**
            *
            */
            bool VulkanTexture::hasMipMaps() const
            {
                return 0;
            }

            /**
            *
            */
            void VulkanTexture::bind()
            {

            }

            /**
            *
            */
            uint32_t VulkanTexture::getHandle() const
            {
                return m_textureId;
            }
        }
    }
}
#endif
