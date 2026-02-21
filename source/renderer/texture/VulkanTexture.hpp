#ifndef __SPARK_RENDERER_VULKAN_VULKANTEXTURE_HPP_INCLUDED__
#define __SPARK_RENDERER_VULKAN_VULKANTEXTURE_HPP_INCLUDED__
#include "spark/SparkSetup.hpp"
#if SPARK_COMPILE_VULKAN == 0x1
#include <vulkan/vulkan.h>
#include "ISparkTexture.hpp"
#include "ISparkLogger.hpp"

namespace spark::renderer::vulkan {
    /**
    *
    */
    struct VulkanTextureData
    {
        VkImage image;             // The texture image              
        VkSampler sampler;         // Defines how the texture is sampled (e.g., filtering, wrapping)
    };

    /**
    *
    */
    class VulkanTexture : public ISparkTexture
    {
    public:
        VulkanTexture(
            spark::log::ISparkLogger* logger,
            uc8_t* data,
            int32_t width,
            int32_t height,
            spark::drawing::E_PIXEL_FORMAT pixelFormat);
        ~VulkanTexture();

    public: // ISparkTexture
        uc8_t* getImageAsStream() const;
        uint32_t getWidth() const;
        uint32_t getHeight() const;
        spark::drawing::E_PIXEL_FORMAT getPixelFormat() const;
        bool hasMipMaps() const;
        void bind();
        uint32_t getHandle() const;

    private:
        spark::log::ISparkLogger* m_logger;
        int m_textureId;
        uc8_t* m_data;
        uint32_t m_width;
        uint32_t m_height;
    };
}
#endif
#endif