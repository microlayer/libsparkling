#ifndef __SPARK_RENDERER_ABSTRACTSPARKRENDERER_HPP_INCLUDED__
#define __SPARK_RENDERER_ABSTRACTSPARKRENDERER_HPP_INCLUDED__
#include "ISparkDevice.hpp"
#include "ISparkShader.hpp"
#include "ISparkTextureFactory.hpp"

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
                spark::renderer::ISparkTextureFactory* textureFactory);
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
            spark::log::ISparkLogger* m_logger;
        };
    } // end namespace renderer
} // end namespace spark
#endif