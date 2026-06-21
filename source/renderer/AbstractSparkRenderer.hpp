#ifndef __SPARK_RENDERER_ABSTRACTSPARKRENDERER_HPP_INCLUDED__
#define __SPARK_RENDERER_ABSTRACTSPARKRENDERER_HPP_INCLUDED__

#include "ISparkDevice.hpp"
#include "ISparkShader.hpp"
#include "ISparkTextureFactory.hpp"
#include "ISparkVertexBufferFactory.hpp"
#include "ISparkMaterial.hpp"
#include "scene/camera/PerspectiveCamera.hpp"
#include "ISparkLightBuffer.hpp"

namespace spark::renderer {
    /**
    *
    */
    class AbstractSparkRenderer : public spark::renderer::ISparkRenderer
    {
    public:
        AbstractSparkRenderer(spark::device::ISparkDevice* device,
            spark::renderer::shader::ISparkShader* shader,
            spark::renderer::ISparkTextureFactory* textureFactory,
            spark::renderer::ISparkVertexBufferFactory* vertexBufferFactory,
            spark::renderer::lightbuffer::ISparkLightBuffer* lightBuffer);
        virtual ~AbstractSparkRenderer();

    public: // ISparkRenderer
        void beginScene();
        void endScene();

    public:
        void setDrawMode(uint32_t drawMode);

    public: // Light
        void uploadLights(
            std::vector<renderer::lightbuffer::GPUDirectionalLight> gpuDirectionalLights,
            std::vector<renderer::lightbuffer::GPUPointLight> gpuPointLights);

    public:
        virtual void onBeginScene() = 0;
        virtual void onEndScene() = 0;

    public: // Factory
        spark::material::ISparkMaterial* createMaterial(spark::material::RenderMode renderMode);
        spark::scene::camera::ISparkPerspectiveCamera* createPerspectiveCamera();

    protected:
        spark::device::ISparkDevice* m_device;
        spark::renderer::shader::ISparkShader* m_shader;
        spark::renderer::ISparkTextureFactory* m_textureFactory;
        spark::renderer::ISparkVertexBufferFactory* m_vertexBufferFactory;
        spark::log::ISparkLogger* m_logger;
        spark::renderer::lightbuffer::ISparkLightBuffer* m_lightBuffer;
    };
}
#endif