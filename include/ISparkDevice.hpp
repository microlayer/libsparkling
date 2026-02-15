#ifndef __SPARK_DEVICE_ISPARKDEVICE_HPP_INCLUDED__
#define __SPARK_DEVICE_ISPARKDEVICE_HPP_INCLUDED__

#include "ISparkLogger.hpp"
#include "ISparkTimer.hpp"
#include "ISparkRenderer.hpp"
#include "ISparkFileSystem.hpp"
#include "ISparkSceneGraphManager3D.hpp"
#include "ISparkSceneGraphManager2D.hpp"
#include "ISparkFontPool.hpp"
#include <string>
#include "ISparkApp.hpp"
#include "ISparkSprite.hpp"
#include "ISparkTiledLayer.hpp"
#include <ISparkHttpClient.hpp>

namespace spark::device {
    /**
    * @Brief Holds the physical display information of the device
    */
    struct ScreenResolution
    {
        uint32_t m_width;
        uint32_t m_height;
        real32 m_ratio;
    };

    /**
    * @Brief Acts as a container.
    */
    class ISparkDevice : public virtual spark::SparkRefCount
    {
    public:
        virtual bool isDeviceRunning() = 0;
        virtual void flush() = 0; // Callback to swap/flush the video-buffer

    public:
        virtual spark::renderer::ISparkRenderer* getRenderer() const = 0;
        virtual spark::renderer::E_RENDER_ENGINE getRenderEngineType() const = 0;
        virtual spark::log::ISparkLogger* getLogger() const = 0;
        virtual spark::timer::ISparkTimer* getTimer() const = 0;
        virtual spark::file::ISparkFileSystem* getFileSystem() const = 0;
        virtual ScreenResolution getScreenResolution() const = 0;
        virtual spark::font::ISparkFontPool* getSparkFontPool() const = 0;

    public: // Factory
        virtual spark::scene::ISceneGraphManager3D* createSceneGraphManager3D() = 0;
        virtual spark::scene::ISceneGraphManager2D* createSceneGraphManager2D() = 0;
        virtual spark::game::ISparkSprite* createSprite(spark::drawing::ISparkImage* image) = 0;
        virtual spark::game::ISparkTiledLayer* createTiledLayer(spark::drawing::ISparkImage* tilesetImage, uint16_t layerColumns, uint16_t layerRows, uint16_t* gidData, uint16_t tileWidth, uint16_t tileHeight, uint16_t tilesetImageWidth, uint16_t tilesetImageHeight, spark::game::E_LAYER_TYPE layerType) = 0;
        virtual spark::network::ISparkHttpClient* createHttpClient() = 0;

    public:
        virtual uint64_t getHeapAllocatedSize() = 0;
        virtual uint64_t getHeapSize() = 0;
        virtual uint16 getAPIVersionSDK() = 0;

    public: // MainLoop infrastructure
        virtual void run(spark::app::ISparkApp* sparkApp) = 0;

    public: // Event handler
        virtual void onKeyPressed(int key, int action) = 0;
        virtual void onMouseMove(real32 x, real32 y) = 0;
        virtual void onMouseClick(int button, int action) = 0;
    };
}
#endif