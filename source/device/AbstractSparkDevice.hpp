#ifndef __SPARK_DEVICE_ABSTRACTSPARKDEVICE_HPP_INCLUDED__
#define __SPARK_DEVICE_ABSTRACTSPARKDEVICE_HPP_INCLUDED__

#include "ISparkDevice.hpp"
#include "file/FileSystem.hpp"
#include "device/window/AbstractSparkWindow.hpp"
#include "device/window/GlfwWindow.hpp"
#include "device/DeviceInstance.hpp"
#include "ISparkShader.hpp"
#include "ISparkRendererApiConfig.hpp"
#include "timer/Timer.hpp"
#include "fonts/FontPool.hpp"
#include "scene/SceneGraphManager3D.hpp"
#include "ISparkTextureFactory.hpp"
#include "renderer/common/TextureFactory.hpp"

#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
#include <emscripten/emscripten.h>
#endif

namespace spark {
    namespace device {
        /**
        *
        */
        class AbstractSparkDevice : public ISparkDevice
        {
        public:
            AbstractSparkDevice(spark::renderer::E_RENDER_ENGINE rendererType);
            virtual ~AbstractSparkDevice(void);
            void construct();

        public: // ISparkDevice			
            virtual bool isDeviceRunning();
            virtual void flush();
            virtual renderer::ISparkRenderer* getRenderer(void) const;
            virtual spark::renderer::E_RENDER_ENGINE getRenderEngineType() const;
            virtual log::ISparkLogger* getLogger() const;
            virtual timer::ISparkTimer* getTimer() const;
            virtual file::ISparkFileSystem* getFileSystem() const;
            virtual ScreenResolution getScreenResolution() const;
            virtual spark::font::ISparkFontPool* getSparkFontPool() const;

        public:
            spark::scene::ISceneGraphManager3D* createSceneGraphManager3D();

        public:
            virtual uint64_t getHeapAllocatedSize();
            virtual uint64_t getHeapSize();
            virtual uint16 getAPIVersionSDK();

        public:
            virtual void run(spark::app::SparkApp* sparkApp);

        public:
            virtual void onKeyPressed(int key, int action);
            virtual void onMouseMove(real32 x, real32 y);
            virtual void onMouseClick(int button, int action);

        private:
            static void setEmscriptenMainLoop();
            void mainLoop();

        private:
            virtual void createTimer();
            virtual void createFontPool();
            virtual void createTextureFactory();

        private:
            virtual void createLogger() = 0;
            virtual void createFileSystem() = 0;
            virtual void createSparkWindow() = 0;
            virtual void createShader() = 0;
            virtual void createRenderer() = 0;

        protected:
            spark::timer::ISparkTimer* m_timer;
            spark::font::ISparkFontPool* m_fontPool;
            spark::log::ISparkLogger* m_logger;
            spark::file::ISparkFileSystem* m_fileSystem;
            spark::device::window::AbstractSparkWindow* m_window;
            spark::renderer::shader::ISparkShader* m_shader;
            spark::renderer::ISparkRenderer* m_renderer;
            spark::renderer::E_RENDER_ENGINE m_rendererEngineType;
            spark::renderer::ISparkRendererApiConfig* m_rendererConfig;
            spark::renderer::ISparkTextureFactory* m_texureFactory;
            spark::ui::AbstractCanvas* m_canvas;
            bool m_isDeviceRunning;
        };
    } // end namespace device
} // end namespace spark
#endif
