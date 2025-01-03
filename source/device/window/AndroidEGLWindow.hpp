#ifndef __SPARK_DEVICE_WINDOW_ANDROIDEGLWINDOW_HPP_INCLUDED__
#define __SPARK_DEVICE_WINDOW_ANDROIDEGLWINDOW_HPP_INCLUDED__
#include "spark/SparkSetup.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_ANDROID 
#include "AbstractSparkWindow.hpp"
#include "ISparkLogger.hpp"
#include <android_native_app_glue.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

namespace spark {
    namespace device {
        namespace window {
            /**
            *
            */
            class AndroidEGLWindow : public spark::device::window::AbstractSparkWindow
            {
            public:
                AndroidEGLWindow(spark::log::ISparkLogger* logger, spark::renderer::E_RENDER_ENGINE rendererEngineType, android_app* pApplication, spark::device::ISparkDevice* device);
                virtual ~AndroidEGLWindow();

            public: // AbstractSparkWindow
                int32_t init();
                int32_t createWindow();
                void terminate();
                void setWindowTitle(const char* title);
                void swapBuffers();
                bool isWindowActive();

            public: // ISparkWindow
                void* getNativeWindow();

            private:
                int32_t initWindow();
                void eventLoop();
                void setAppActive();
                void setAppInactive();
                void destroyEGL();
                void setDefaultViewport();

            private: // Event handler
                static void callbackEvent(android_app* pApplication, int32_t pCommand);

            public:
                ScreenResolution getScreenResolution();

            private:
                spark::renderer::E_RENDER_ENGINE m_rendererEngineType;
                android_app* m_androidApplication;
                EGLDisplay m_display;
                EGLSurface m_surface;
                EGLContext m_context;
                bool m_enabled;
                bool m_wantsQuit;
                bool m_isGLES2ContextAvailable;
                bool m_isWindowActive;
                int32_t m_width, m_height;
                spark::device::ISparkDevice* m_device;
            };
        } // end namespace window
    } // end namespace device
} // end namespace spark
#endif
#endif