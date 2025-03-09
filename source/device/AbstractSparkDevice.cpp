#include "AbstractSparkDevice.hpp"

namespace spark {
    namespace device {
        /**
        *
        */
        AbstractSparkDevice::AbstractSparkDevice(spark::renderer::E_RENDER_ENGINE rendererType) :
            m_rendererEngineType(rendererType),
            m_logger(NULL),
            m_timer(NULL),
            m_fileSystem(NULL),
            m_fontPool(NULL),
            m_window(NULL),
            m_activeCanvas(NULL),
            m_shader(NULL),
            m_renderer(NULL),
            m_rendererConfig(NULL)
        {
            m_isDeviceRunning = true;
            DeviceInstance::Instance = this;
        }

        /**
        *
        */
        AbstractSparkDevice::~AbstractSparkDevice(void)
        {
            m_timer->release();
            m_fontPool->release();
            m_texureFactory->release();
        }

        /**
        *
        */
        void AbstractSparkDevice::construct()
        {
            createLogger();
            createFileSystem();
            createSparkWindow();
            createShader();
            createTextureFactory();
            createVertexBufferFactory();
            createRenderer();
            createTimer();
            createFontPool();
        }

        /**
        *
        */
        bool AbstractSparkDevice::isDeviceRunning()
        {
            m_isDeviceRunning = m_window->isWindowActive();
            return m_isDeviceRunning;
        }

        /**
        * @Brief Callback to swap/flush the video-buffer
        */
        void AbstractSparkDevice::flush()
        {
            m_window->swapBuffers();
        }

        /**
        *
        */
        renderer::ISparkRenderer* AbstractSparkDevice::getRenderer(void) const
        {
            return m_renderer;
        }

        /**
        *
        */
        spark::renderer::E_RENDER_ENGINE AbstractSparkDevice::getRenderEngineType() const
        {
            return m_rendererEngineType;
        }

        /**
        * Gets logger for the created device
        */
        log::ISparkLogger* AbstractSparkDevice::getLogger() const
        {
            return spark::log::LogManager::getLogger();
        }

        /**
        *
        */
        spark::timer::ISparkTimer* AbstractSparkDevice::getTimer() const
        {
            return m_timer;
        }

        /**
        *
        */
        file::ISparkFileSystem* AbstractSparkDevice::getFileSystem() const
        {
            return m_fileSystem;
        }

        /**
        *
        */
        ScreenResolution AbstractSparkDevice::getScreenResolution() const
        {
            return m_window->getScreenResolution();
        }

        /**
        *
        */
        spark::font::ISparkFontPool* AbstractSparkDevice::getSparkFontPool() const
        {
            return m_fontPool;
        }

        /**
        *
        */
        spark::scene::ISceneGraphManager3D* AbstractSparkDevice::createSceneGraphManager3D()
        {
            return new spark::scene::SceneGraphManager3D(m_renderer, this->getScreenResolution());
        }

        /**
        *
        */
        spark::game::ISparkSprite* AbstractSparkDevice::createSprite(spark::drawing::ISparkImage* image)
        {
            return new spark::game::Sprite(image);
        }

        /**
        *
        */
        spark::game::ISparkTiledLayer* AbstractSparkDevice::createTiledLayer(spark::drawing::ISparkImage* tilesetImage, uint16_t layerColumns, uint16_t layerRows, uint16_t* gidData, uint16_t tileWidth, uint16_t tileHeight, uint16_t tilesetImageWidth, uint16_t tilesetImageHeight, spark::game::E_LAYER_TYPE layerType)
        {
            return new spark::game::TiledLayer(tilesetImage, layerColumns, layerRows, gidData, tileWidth, tileHeight, tilesetImageWidth, tilesetImageHeight, layerType);
        }

        /**
        *
        */
        uint64_t AbstractSparkDevice::getHeapAllocatedSize()
        {
            return 0;
        }

        /**
        *
        */
        uint64_t AbstractSparkDevice::getHeapSize()
        {
            return 0;
        }

        /**
        *
        */
        uint16 AbstractSparkDevice::getAPIVersionSDK()
        {
            return 0;
        }

        /**
        *
        */
        void AbstractSparkDevice::run(spark::app::ISparkApp* sparkApp)
        {
            m_sparkApp = sparkApp;
            m_sparkApp->onInit();
            m_activeCanvas = sparkApp->getActiveCanvas();
            if (m_activeCanvas != NULL)
            {
                m_activeCanvas->init();
#ifdef EMSCRIPTEN						
                emscripten_set_main_loop(setEmscriptenMainLoop, 0, 1);
#else
                while (isDeviceRunning())
                {
                    mainLoop();
                }
#endif 
            }
            else
            {
                m_logger->info("Canvas is not set. Please set an active canvas first");
            }
        }

        /**
        *
        */
        void AbstractSparkDevice::onKeyPressed(int key, int action)
        {
            m_logger->info("OnKeyPressed key:%i action:%i", key, action);
            if (m_activeCanvas != NULL) m_activeCanvas->onKeyPressed(key, action);
        }

        /**
        *
        */
        void AbstractSparkDevice::onMouseMove(real32 x, real32 y)
        {
            m_logger->info("OnMouseMove x:%i y:%i", x, y);
        }

        /**
        *
        */
        void AbstractSparkDevice::onMouseClick(int button, int action)
        {
            m_logger->info("OnMouseClick button:%i action:%i", button, action);
        }

        /**
        *
        */
        void AbstractSparkDevice::setEmscriptenMainLoop()
        {
            DeviceInstance::Instance->mainLoop();
        }

        /**
        *
        */
        void AbstractSparkDevice::mainLoop()
        {
            if (m_activeCanvas != m_sparkApp->getActiveCanvas())
            {
                m_activeCanvas = m_sparkApp->getActiveCanvas();
                m_activeCanvas->init();
            }

            m_renderer->beginScene();
            if (m_activeCanvas != NULL)
            {
                m_activeCanvas->paint(m_renderer);
            }
            m_renderer->endScene();
        }

        /**
        *
        */
        void AbstractSparkDevice::createTimer()
        {
            m_timer = new spark::timer::Timer();
        }

        /**
        *
        */
        void AbstractSparkDevice::createFontPool()
        {
            m_fontPool = new spark::font::FontPool();
        }

        /**
        *
        */
        void AbstractSparkDevice::createTextureFactory()
        {
            m_texureFactory = new spark::renderer::TextureFactory(m_logger);
        }

        /**
        *
        */
        void AbstractSparkDevice::createVertexBufferFactory()
        {
            m_vertexBufferFactory = new spark::renderer::VertexBufferFactory(m_logger);
        }
    } // end namespace device
} // end namespace spark
