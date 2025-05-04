#ifndef __SPARK_RENDERER_ABSTRACTSPARKRENDERER_HPP_INCLUDED__
#define __SPARK_RENDERER_ABSTRACTSPARKRENDERER_HPP_INCLUDED__
#include "ISparkDevice.hpp"
#include "ISparkShader.hpp"
#include "ISparkTextureFactory.hpp"
#include "ISparkVertexBufferFactory.hpp"

namespace spark {
    namespace renderer {
        /**
        *
        */
        class AbstractSparkRenderer : public spark::renderer::ISparkRenderer
        {
        public:
            AbstractSparkRenderer(spark::device::ISparkDevice* device,
                spark::renderer::shader::ISparkShader* shader,
                spark::renderer::ISparkTextureFactory* textureFactory,
                spark::renderer::ISparkVertexBufferFactory* vertexBufferFactory);
            virtual ~AbstractSparkRenderer();

        public: // ISparkRenderer
            void beginScene();
            void endScene();

        public:
            virtual void onBeginScene() = 0;
            virtual void onEndScene() = 0;

        protected:
            spark::device::ISparkDevice* m_device;
            spark::renderer::shader::ISparkShader* m_shader;
            spark::renderer::ISparkTextureFactory* m_textureFactory;
            spark::renderer::ISparkVertexBufferFactory* m_vertexBufferFactory;
            spark::log::ISparkLogger* m_logger;
        };
    } // end namespace renderer
} // end namespace spark
#endif