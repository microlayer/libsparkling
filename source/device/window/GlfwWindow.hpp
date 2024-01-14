#ifndef __SPARK_DEVICE_WINDOW_GLFWWINDOW_HPP_INCLUDED__
#define __SPARK_DEVICE_WINDOW_GLFWWINDOW_HPP_INCLUDED__
#include "spark/SparkSetup.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS ||  \
	SPARK_PLATFORM == SPARK_PLATFORM_WEBGL	 ||	 \
	SPARK_PLATFORM == SPARK_PLATFORM_LINUX

#include "AbstractSparkWindow.hpp"
#include "ISparkLogger.hpp"
#include <glfw/glfw3.h>

namespace spark {
    namespace device {
        namespace window {
            /**
            *
            */
            class GlfwWindow : public spark::device::window::AbstractSparkWindow
            {
            public:
                GlfwWindow(spark::log::ISparkLogger* logger, spark::renderer::E_RENDER_ENGINE rendererEngineType);
                virtual ~GlfwWindow(void);

            public: // AbstractSparkWindow
                int32_t init();
                int32_t createWindow(int32_t width, int32_t height);
                void terminate();
                void setWindowTitle(const char* title);
                void swapBuffers();
                bool isWindowActive();
                ScreenResolution getScreenResolution();

            public: // ISparkWindow
                void* getNativeWindow();

            private:
                void setDefaultViewport();

            private: // Event handler
                static void onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
                static void onMouseMove(GLFWwindow* window, double x, double y);
                static void onMouseClick(GLFWwindow* window, int button, int action, int mods);

            public:
                static GlfwWindow* Instance;
                GLFWwindow* m_window;
                spark::renderer::E_RENDER_ENGINE m_rendererEngineType;

            };
        } // end namespace windowc
    } // end namespace device
} // end namespace spark
#endif
#endif
