#include "GlfwWindow.hpp"

#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS ||  \
	SPARK_PLATFORM == SPARK_PLATFORM_WEBGL

namespace spark {
    namespace device {
        namespace window {
            // Static instance of GlfwWindow
            GlfwWindow* GlfwWindow::Instance;

            /**
            *
            */
            GlfwWindow::GlfwWindow(spark::log::ISparkLogger* logger, spark::renderer::E_RENDER_ENGINE rendererEngineType) :
                AbstractSparkWindow(logger),
                m_window(NULL),
                m_rendererEngineType(rendererEngineType)
            {
                m_landscape = true;
            }

            /**
            *
            */
            GlfwWindow::~GlfwWindow(void)
            {
                terminate();
            }

            /**
            *
            */
            int32_t GlfwWindow::init()
            {
                int32_t ret = glfwInit();
                if (ret != GL_TRUE)
                {
                    glfwTerminate();
                }
                return ret;
            }

            /**
            *
            */
            int32_t GlfwWindow::createWindow(int32_t width, int32_t height)
            {
                Instance = this;
                glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
                // By default GLFW creates OpenGL window context. 
                // To use GLFW with vulkan GLFW_CLIENT_API and GLFW_NO_API needs to be set
                if (m_rendererEngineType == spark::renderer::ERE_VULKAN13)
                {
                    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
                }
                m_window = glfwCreateWindow(width, height, "", NULL, NULL);

                glfwSetKeyCallback(m_window, onKeyPressed);
                glfwSetCursorPosCallback(m_window, onMouseMove);
                glfwSetMouseButtonCallback(m_window, onMouseClick);

                glfwMakeContextCurrent(m_window);

                setDefaultViewport();
                return 1;
            }

            /**
            *
            */
            void GlfwWindow::terminate()
            {
                glfwDestroyWindow(m_window);
                glfwTerminate();
            }

            /**
            *
            */
            void GlfwWindow::setWindowTitle(const char* title)
            {
                glfwSetWindowTitle(m_window, title);
            }

            /**
            * Switch the back buffer and the front buffer
            */
            void GlfwWindow::swapBuffers()
            {
                glfwPollEvents();
                glfwSwapInterval(1);
                glfwSwapBuffers(m_window);
            }

            /**
            *
            */
            bool GlfwWindow::isWindowActive()
            {
                int32_t flag = glfwWindowShouldClose(m_window);
                return flag == 0 ? true : false;
            }

            /**
            * @Brief Hardcoded Screen Resolution for this win32 Device. Equal to Android
            */
            ScreenResolution GlfwWindow::getScreenResolution()
            {
                if (!m_landscape)
                {
                    ScreenResolution sr = { 720, 1184, (720.0f / 1184.0f) };	//ratio:0.608
                    return sr;
                }
                else
                {
                    ScreenResolution sr = { 1196, 720, (1196.0f / 720.0f) };	//ratio:1.66
                    return sr;
                }
            }

            /**
            *
            */
            void* GlfwWindow::getNativeWindow()
            {
                return m_window;
            }

            /**
            *
            */
            void GlfwWindow::setDefaultViewport()
            {
                glViewport(0, 0, this->getScreenResolution().m_width, this->getScreenResolution().m_height);
            }

            /**
            *
            */
            void GlfwWindow::onKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                //Instance->getDevice()->onKeyPressed(key, action);
            }

            /**
            *
            */
            void GlfwWindow::onMouseMove(GLFWwindow* window, double x, double y)
            {
                //Instance->getDevice()->onMouseMove((real32)x, (real32)y);
            }

            /**
            *
            */
            void GlfwWindow::onMouseClick(GLFWwindow* window, int button, int action, int mods)
            {
                //Instance->getDevice()->onMouseClick(button, action);
            }

        } // end namespace window	
    } // end namespace device
} // end namespace spark
#endif
