#ifndef __SPARK_DEVICE_ISPARKDEVICE_HPP_INCLUDED__
#define __SPARK_DEVICE_ISPARKDEVICE_HPP_INCLUDED__

#include "ISparkLogger.hpp"
//#include "ISparkTimer.hpp"
#include "ISparkRenderer.hpp"
#include "ISparkFileSystem.hpp"
#include <string>
#include "app/SparkApp.hpp"

namespace spark {
    namespace device {
        /**
        * @Brief Holds the physical display information of the device
        */
        struct ScreenResolution
        {
            int32_t m_width;
            int32_t m_height;
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
            virtual spark::renderer::ISparkRenderer* getRenderer() = 0;
            virtual spark::renderer::E_RENDER_ENGINE getRenderEngineType() = 0;
            virtual spark::log::ISparkLogger* getLogger() = 0;
            //virtual spark::timer::ISparkTimer* getTimer() = 0;
            virtual spark::file::ISparkFileSystem* getFileSystem() = 0;
            virtual ScreenResolution getScreenResolution() = 0;
            //virtual std::string getRootPath() = 0;
            //virtual spark::font::ISparkFontPool* getSparkFontPool() = 0;

        public:
            //virtual uint64_t getHeapAllocatedSize() = 0;
            //virtual uint64_t getHeapSize() = 0;
            //virtual uint16 getAPIVersionSDK() = 0;

        public: // MainLoop infrastructure
            virtual void run(spark::app::SparkApp* sparkApp) = 0;

        public: // Event handler
            virtual void onKeyPressed(int key, int action) = 0;
            virtual void onMouseMove(real32 x, real32 y) = 0;
            virtual void onMouseClick(int button, int action) = 0;
        };
    } // end namespace device
} // end namespace spark
#endif