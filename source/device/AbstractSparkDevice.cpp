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
            m_canvas(NULL),
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
        void AbstractSparkDevice::run(spark::app::SparkApp* sparkApp)
        {
            m_sparkApp = sparkApp;
            m_sparkApp->onInit();
            m_canvas = sparkApp->getActiveCanvas();
            m_canvas->init();
#ifdef EMSCRIPTEN						
            emscripten_set_main_loop(setEmscriptenMainLoop, 0, 1);
#else
            while (isDeviceRunning())
            {
                mainLoop();
            }
#endif 
        }

        /**
        *
        */
        void AbstractSparkDevice::onKeyPressed(int key, int action)
        {
            m_logger->info("OnKeyPressed key:%i action:%i", key, action);
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
            if (m_sparkApp != NULL && m_sparkApp->isCanvasChanged())
            {
                m_canvas = m_sparkApp->getActiveCanvas();
                m_canvas->init();
                m_sparkApp->resetIsCanvasChanged();
            }

            m_renderer->beginScene();
            if (m_canvas != NULL)
            {
                m_canvas->paint(m_renderer);
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
    } // end namespace device
} // end namespace spark
