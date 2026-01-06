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
            GlfwWindow::GlfwWindow(spark::log::ISparkLogger* logger, spark::renderer::E_RENDER_ENGINE rendererEngineType, spark::device::ISparkDevice* device) :
                AbstractSparkWindow(logger),
                m_window(NULL),
                m_rendererEngineType(rendererEngineType),
                m_device(device)
            {
                
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
            int32_t GlfwWindow::createWindow(uint32_t screenWidth, uint32_t screenHeight)
            {
                Instance = this;
                
                m_screenResolution = { screenWidth, screenHeight, m_screenResolution.m_ratio = (real32)screenWidth/screenHeight };

                glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
                
                // Multisample Anti-Aliasing (MSAA) 
                glfwWindowHint(GLFW_SAMPLES, 4);  // 4x MSAA

                // Set OpenGL version and profile
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // GLFW_OPENGL_CORE_PROFILE

                // By default GLFW creates OpenGL window context. 
                // To use GLFW with vulkan GLFW_CLIENT_API and GLFW_NO_API needs to be set
                if (m_rendererEngineType == spark::renderer::ERE_VULKAN13)
                {
                    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
                }
                m_window = glfwCreateWindow(this->getScreenResolution().m_width, this->getScreenResolution().m_height, "", NULL, NULL);

                glfwSetKeyCallback(m_window, onKeyPressed);
                glfwSetCursorPosCallback(m_window, onMouseMove);
                glfwSetMouseButtonCallback(m_window, onMouseClick);

                glfwMakeContextCurrent(m_window);
                glfwSwapInterval(1); // Enable V-Sync

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
                glfwSwapBuffers(m_window);
                glfwPollEvents();
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

                Instance->m_device->onKeyPressed(key, action);
            }

            /**
            *
            */
            void GlfwWindow::onMouseMove(GLFWwindow* window, double x, double y)
            {
                Instance->m_device->onMouseMove((real32)x, (real32)y);
            }

            /**
            *
            */
            void GlfwWindow::onMouseClick(GLFWwindow* window, int button, int action, int mods)
            {
                Instance->m_device->onMouseClick(button, action);
            }

        } // end namespace window	
    } // end namespace device
} // end namespace spark
#endif
