#include "AbstractSparkDevice.hpp"

namespace spark {
    namespace device {
        /**
        *
        */
        AbstractSparkDevice::AbstractSparkDevice(spark::renderer::E_RENDER_ENGINE rendererType) :
            m_rendererEngineType(rendererType),
            m_logger(NULL)
            //m_timer(NULL),
            //m_fileSystem(NULL)
        {
            m_isDeviceRunning = true;
            //m_canvas = NULL;			
        }

        /**
        *
        */
        AbstractSparkDevice::~AbstractSparkDevice(void)
        {

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
            createRenderer();
            //createTimer();	
            //createFontPool();
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
        renderer::ISparkRenderer* AbstractSparkDevice::getRenderer(void)
        {
            return m_renderer;
        }

        /**
        *
        */
        spark::renderer::E_RENDER_ENGINE AbstractSparkDevice::getRenderEngineType()
        {
            return m_rendererEngineType;
        }

        /**
        * Gets logger for the created device
        */
        log::ISparkLogger* AbstractSparkDevice::getLogger()
        {
            return spark::log::LogManager::getLogger();
        }

        /**
        *
        */
        //timer::ISparkTimer* AbstractSparkDevice::getTimer()
        //{
        //	return m_timer;
        //}

        /**
        *
        */
        file::ISparkFileSystem* AbstractSparkDevice::getFileSystem()
        {
        	return m_fileSystem;
        }

        /**
        *
        */
        ScreenResolution AbstractSparkDevice::getScreenResolution()
        {
            return m_window->getScreenResolution();
        }

        /**
        *
        */
        //std::string AbstractSparkDevice::getRootPath()
        //{
        //	return "/";
        //}

        /**
        *
        */
        //spark::font::ISparkFontPool* AbstractSparkDevice::getSparkFontPool()
        //{
        //	return m_fontPool;
        //}

        /**
        *
        */
        //uint64_t AbstractSparkDevice::getHeapAllocatedSize()
        //{
        //	return 0;
        //}

        /**
        *
        */
        //uint64_t AbstractSparkDevice::getHeapSize()
        //{
        //	return 0;
        //}

        /**
        *
        */
        //uint16 AbstractSparkDevice::getAPIVersionSDK()
        //{
        //	return 0;
        //}

        /**
        *
        */
        void AbstractSparkDevice::run(spark::app::SparkApp* sparkApp)
        {
            DeviceInstance::Instance = this;
            sparkApp->onInit();
            m_canvas = sparkApp->getActiveCanvas();
#ifdef EMSCRIPTEN						
            emscripten_set_main_loop(setEmscriptenMainLoop, 0, 1);
#else
            while (isDeviceRunning())
            {
                //				if (sparkApp->isCanvasChanged())
                //				{
                //                  m_canvas = sparkApp->getActiveCanvas();
                //					sparkApp->resetIsCanvasChanged();
                //				}
                mainLoop();
            }
#endif 
        }

        /**
        *
        */
        void AbstractSparkDevice::onKeyPressed(int key, int action)
        {
            //	m_logger->info("OnKeyPressed key:%i action:%i", key, action);
            //	
            //	if (m_canvas != NULL)
            //	{
            //		// UP
            //		if (key == 265)
            //		{
            //			m_canvas->processMoveEvent(spark::math::Vector2f(0, -1), 1);
            //		}
            //		// Down
            //		if (key == 264)
            //		{
            //			m_canvas->processMoveEvent(spark::math::Vector2f(0, 1), 1);
            //		}
            //		// Left
            //		if (key == 263)
            //		{
            //			m_canvas->processMoveEvent(spark::math::Vector2f(-1, 0), 1);
            //		}
            //		// Right
            //		if (key == 262)
            //		{
            //			m_canvas->processMoveEvent(spark::math::Vector2f(1, 0), 1);
            //		}
            //		if (key == 32)
            //		{
            //			m_canvas->eventAction(spark::ui::Event::EET_COMMAND, spark::ui::Command::ECT_HOME);
            //		}
            //	}
        }

        /**
        *
        */
        void AbstractSparkDevice::onMouseMove(real32 x, real32 y)
        {
            //	m_logger->info("OnMouseMove x:%i y:%i", x, y);
            //	
            //	if (m_canvas != NULL)
            //	{
            //		m_canvas->processMoveEvent(spark::math::Vector2f(1, 0), 1);
            //	}
        }

        /**
        *
        */
        void AbstractSparkDevice::onMouseClick(int button, int action)
        {
            //	m_logger->info("OnMouseClick button:%i action:%i", button, action);
            //	
            //	if (m_canvas != NULL)
            //	{
            //		//iCanvas->EventAction();
            //	}
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
        void AbstractSparkDevice::createLogger()
        {
        }

        /**
        *
        */
        //void AbstractSparkDevice::createTimer()
        //{
        //	m_timer = new timer::Timer();
        //}

        /**
        *
        */
        //void AbstractSparkDevice::createFileSystem()
        //{
        //	m_fileSystem = new file::FileSystem(this);
        //}

        /**
        *
        */
        //void AbstractSparkDevice::createFontPool()
        //{
        //	m_fontPool = new spark::font::FontPool(this);
        //}

        /**
        *
        */
        //void AbstractSparkDevice::createSparkWindow()
        //{

        //}

    } // end namespace device
} // end namespace spark
