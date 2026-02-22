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
#include "scene/SceneGraphManager2D.hpp"
#include "ISparkTextureFactory.hpp"
#include "ISparkVertexBufferFactory.hpp"
#include "renderer/common/TextureFactory.hpp"
#include "renderer/common/VertexBufferFactory.hpp"
#include "game/Sprite.hpp"
#include "game/TiledLayer.hpp"
#include "network/HttpClient.hpp"

#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL
#include <emscripten/emscripten.h>
#endif

namespace spark::device {
    /**
    *
    */
    class AbstractSparkDevice : public ISparkDevice
    {
    public:
        AbstractSparkDevice(spark::renderer::E_RENDER_ENGINE rendererType, uint32_t screenWidth, uint32_t screenHeight);
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
        virtual spark::network::ISparkHttpClient* getHttpClient() const;
        virtual asset::ISparkAssetManager* getAssetManager() const;
        virtual ScreenResolution getScreenResolution() const;
        virtual spark::font::ISparkFontPool* getSparkFontPool() const;

    public: // Factory
        spark::scene::ISceneGraphManager3D* createSceneGraphManager3D();
        spark::scene::ISceneGraphManager2D* createSceneGraphManager2D();
        spark::game::ISparkSprite* createSprite(spark::drawing::ISparkImage* image);
        spark::game::ISparkTiledLayer* createTiledLayer(spark::drawing::ISparkImage* tilesetImage, uint16_t layerColumns, uint16_t layerRows, uint16_t* gidData, uint16_t tileWidth, uint16_t tileHeight, uint16_t tilesetImageWidth, uint16_t tilesetImageHeight, spark::game::E_LAYER_TYPE layerType);


    public:
        virtual uint64_t getHeapAllocatedSize();
        virtual uint64_t getHeapSize();
        virtual uint16 getAPIVersionSDK();

    public:
        virtual void run(spark::app::ISparkApp* sparkApp);

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
        virtual void createVertexBufferFactory();
        virtual void createHttpClient();

    private:
        virtual void createLogger() = 0;
        virtual void createFileSystem() = 0;
        virtual void createAssetManager() = 0;
        virtual void createSparkWindow() = 0;
        virtual void createShader() = 0;
        virtual void createRenderer() = 0;

    protected:
        spark::timer::ISparkTimer* m_timer;
        spark::font::ISparkFontPool* m_fontPool;
        spark::log::ISparkLogger* m_logger;
        spark::file::ISparkFileSystem* m_fileSystem;
        spark::network::ISparkHttpClient* m_httpClient;
        spark::asset::ISparkAssetManager* m_assetManager;
        spark::device::window::AbstractSparkWindow* m_window;
        spark::renderer::shader::ISparkShader* m_shader;
        spark::renderer::ISparkRenderer* m_renderer;
        spark::renderer::E_RENDER_ENGINE m_rendererEngineType;
        spark::renderer::ISparkRendererApiConfig* m_rendererConfig;
        spark::renderer::ISparkTextureFactory* m_texureFactory;
        spark::renderer::ISparkVertexBufferFactory* m_vertexBufferFactory;
        spark::ui::AbstractCanvas* m_activeCanvas;
        spark::app::ISparkApp* m_sparkApp;
        uint32_t m_screenWidth;
        uint32_t m_screenHeight;
        bool m_isDeviceRunning;
    };
}
#endif
