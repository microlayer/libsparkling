#ifndef __SPARK_DEVICE_ABSTRACTSPARKDEVICE_HPP_INCLUDED__
#define __SPARK_DEVICE_ABSTRACTSPARKDEVICE_HPP_INCLUDED__

#include "ISparkDevice.hpp"
#include "file/FileSystem.hpp"
#include "device/window/AbstractSparkWindow.hpp"
#include "device/window/GlfwWindow.hpp"
#include "device/DeviceInstance.hpp"
#include "ISparkShader.hpp"

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
			virtual renderer::ISparkRenderer* getRenderer(void);	
			virtual spark::renderer::E_RENDER_ENGINE getRenderEngineType();
			virtual log::ISparkLogger* getLogger();
//			virtual timer::ISparkTimer* getTimer();
			virtual file::ISparkFileSystem* getFileSystem();
			virtual ScreenResolution getScreenResolution();
//			virtual std::string getRootPath();
//			spark::font::ISparkFontPool* getSparkFontPool();
//			virtual uint64_t getHeapAllocatedSize();
//			virtual uint64_t getHeapSize();
//			virtual uint16 getAPIVersionSDK();
			virtual void run(spark::app::SparkApp* sparkApp);
			virtual void onKeyPressed(int key, int action);
			virtual void onMouseMove(real32 x, real32 y);
			virtual void onMouseClick(int button, int action);
//
//		private:
			static void setEmscriptenMainLoop();
			void mainLoop();
//
		private:
			virtual void createLogger();
//			virtual void createTimer();
			virtual void createFileSystem() = 0;
//			virtual void createFontPool();
			virtual void createSparkWindow() = 0;
            virtual void createShader() = 0;
			virtual void createRenderer() = 0;

		protected: // Device Members
			bool m_isDeviceRunning;
			spark::log::ISparkLogger* m_logger;
//			spark::timer::ISparkTimer* m_timer;
			spark::file::ISparkFileSystem* m_fileSystem;
//			spark::font::ISparkFontPool* m_fontPool;
			spark::device::window::AbstractSparkWindow* m_window;
			spark::renderer::E_RENDER_ENGINE m_rendererEngineType;
			spark::ui::AbstractCanvas* m_canvas;
            spark::renderer::shader::ISparkShader* m_shader;
			spark::renderer::ISparkRenderer* m_renderer;
		};
	} // end namespace device
} // end namespace spark
#endif
