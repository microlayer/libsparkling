#include "AndroidEGLWindow.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_ANDROID 
namespace spark {
    namespace device {
        namespace window {
            /**
            *
            */
            AndroidEGLWindow::AndroidEGLWindow(spark::log::ISparkLogger* logger, spark::renderer::E_RENDER_ENGINE rendererEngineType, android_app* pApplication) :
                AbstractSparkWindow(logger),
                m_rendererEngineType(rendererEngineType),
                m_androidApplication(pApplication),
                m_width(0),
                m_height(0),
                m_enabled(false),
                m_wantsQuit(false),
                m_display(EGL_NO_DISPLAY),
                m_surface(EGL_NO_CONTEXT),
                m_context(EGL_NO_SURFACE)
            {
                m_androidApplication->userData = this;
                m_androidApplication->onAppCmd = callbackEvent;
            }

            /**
            *
            */
            AndroidEGLWindow::~AndroidEGLWindow()
            {

            }

            /**
            *
            */
            int32_t AndroidEGLWindow::init()
            {
                m_isGLES2ContextAvailable = false;
                m_isWindowActive = true;
                return 1;
            }

            /**
            *
            */
            int32_t AndroidEGLWindow::createWindow(int32_t width, int32_t height)
            {
                m_width = width;
                m_height = height;
                while (!m_isGLES2ContextAvailable)
                {
                    eventLoop();
                }
                return 1;
            }

            /**
            *
            */
            void AndroidEGLWindow::terminate()
            {
            }

            /**
            *
            */
            void AndroidEGLWindow::setWindowTitle(const char* title)
            {
            }

            /**
            *
            */
            void AndroidEGLWindow::swapBuffers()
            {
                if (m_isGLES2ContextAvailable)
                {
                    if (eglSwapBuffers(m_display, m_surface) != EGL_TRUE)
                    {
                        m_logger->error("AndroidEGLWindow::SwapBuffers - Error %d swapping buffers.", eglGetError());
                    }
                }
            }

            /**
            *
            */
            bool AndroidEGLWindow::isWindowActive()
            {
                eventLoop();
                return m_isWindowActive;
            }

            /**
            *
            */
            void* AndroidEGLWindow::getNativeWindow()
            {
                return m_androidApplication->window;
            }

            /**
            *
            */
            void AndroidEGLWindow::setDefaultViewport()
            {
                glViewport(0, 0, m_width, m_height);
            }

            /**
            *
            */
            int32_t AndroidEGLWindow::initWindow()
            {
                const EGLint* lAttributes;
                EGLint lFormat, lNumConfigs, lErrorResult;
                EGLConfig lConfig;

                // Defines display requirements RGBX_8888_ATTRIBS
                const EGLint RGBX_8888_ATTRIBUTES[] =
                {
                    EGL_RENDERABLE_TYPE,
                    EGL_OPENGL_ES2_BIT,
                    EGL_SURFACE_TYPE,
                    EGL_WINDOW_BIT,
                    EGL_RED_SIZE, 8,
                    EGL_GREEN_SIZE, 8,
                    EGL_BLUE_SIZE, 8,
                    EGL_DEPTH_SIZE, 8,
                    EGL_NONE
                };

                // Defines display requirements RGB_565_ATTRIBS
                const EGLint RGB_565_ATTRIBUTES[] =
                {
                    EGL_RENDERABLE_TYPE,
                    EGL_OPENGL_ES2_BIT,
                    EGL_SURFACE_TYPE,
                    EGL_WINDOW_BIT,
                    EGL_RED_SIZE, 5,
                    EGL_GREEN_SIZE, 6,
                    EGL_BLUE_SIZE, 5,
                    EGL_DEPTH_SIZE, 8,
                    EGL_NONE
                };

                int32_t windowFormat = ANativeWindow_getFormat(m_androidApplication->window);
                if ((windowFormat == WINDOW_FORMAT_RGBA_8888) || (windowFormat == WINDOW_FORMAT_RGBX_8888))
                {
                    lAttributes = RGBX_8888_ATTRIBUTES;
                }
                else
                {
                    lAttributes = RGB_565_ATTRIBUTES;
                }


                // Defines the client version
                EGLint lEGLClients[] =
                {
                    EGL_CONTEXT_CLIENT_VERSION, 2,
                    EGL_NONE
                };


                // Retrieves a display connection and initializes it.
                m_logger->info("AndroidEGLWindow::createWindow - Connecting to the display");
                m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
                if (m_display == EGL_NO_DISPLAY)
                {
                    goto ERROR;
                }

                if (!eglInitialize(m_display, NULL, NULL))
                {
                    goto ERROR;
                }

                // Selects the first OpenGL configuration found.
                m_logger->info("AndroidEGLWindow::createWindow - Requesting framebuffer configurations");
                if (!eglChooseConfig(m_display, lAttributes, &lConfig, 1, &lNumConfigs) || (lNumConfigs <= 0))
                {
                    goto ERROR;
                }

                m_logger->info("AndroidEGLWindow::createWindow - Framebuffer configurations found: %i", lNumConfigs);

                if (!eglGetConfigAttrib(m_display, lConfig, EGL_NATIVE_VISUAL_ID, &lFormat))
                {
                    goto ERROR;
                }

                ANativeWindow_setBuffersGeometry(m_androidApplication->window, 0, 0, lFormat);

                m_logger->info("AndroidEGLWindow::createWindow - Create the display surface.");
                m_surface = eglCreateWindowSurface(m_display, lConfig, m_androidApplication->window, NULL);
                if (m_surface == EGL_NO_SURFACE)
                {
                    goto ERROR;
                }

                m_context = eglCreateContext(m_display, lConfig, NULL, lEGLClients);

                if (m_context == EGL_NO_CONTEXT)
                {
                    goto ERROR;
                }

                m_logger->info("AndroidEGLWindow::createWindow - Activates the display surface.");
                if (!eglMakeCurrent(m_display, m_surface, m_surface, m_context)
                    || !eglQuerySurface(m_display, m_surface, EGL_WIDTH, &m_width)
                    || !eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &m_height)
                    || (m_width <= 0) || (m_height <= 0))
                {
                    goto ERROR;
                }

                setDefaultViewport();

                int32_t depth;
                glGetIntegerv(GL_DEPTH_BITS, &depth);

                // Displays information about OpenGL.
                m_logger->info("Starting GraphicsService");
                m_logger->info("Version		: %s", glGetString(GL_VERSION));
                m_logger->info("Extensions	: %s", glGetString(GL_EXTENSIONS));
                m_logger->info("Vendor		: %s", glGetString(GL_VENDOR));
                m_logger->info("Renderer	: %s", glGetString(GL_RENDERER));
                m_logger->info("Viewport	: %i x %i", m_width, m_height);
                m_logger->info("Depth Bits	: %i", depth);

                m_enabled = true;
                m_wantsQuit = false;
                m_isGLES2ContextAvailable = true;

                return 1;
            ERROR:
                m_logger->error("AndroidEGLWindow::CreateWindow - Error while creating GLES context");
                return 0;
            }

            /**
            *
            */
            void AndroidEGLWindow::eventLoop()
            {
                int32_t lResult;
                int32_t lEvents;
                android_poll_source* lSource;
                while ((lResult = ALooper_pollAll(m_enabled ? 0 : -1, NULL, &lEvents, (void**)&lSource)) >= 0)
                {
                    if (lSource != NULL)
                    {
                        m_logger->info("AndroidEGLWindow::EventLoop - Processing an event");
                        lSource->process(m_androidApplication, lSource);
                    }
                    if (m_androidApplication->destroyRequested)
                    {
                        m_logger->info("AndroidEGLWindow::EventLoop - Start exiting event loop ");
                        m_logger->info("AndroidEGLWindow::EventLoop - Setting IsWindowActive to false");
                        m_isWindowActive = false;
                        return;
                    }
                }
            }

            /**
            *
            */
            void AndroidEGLWindow::setAppActive()
            {
                m_isGLES2ContextAvailable = true;
                if ((!m_enabled) && (m_androidApplication->window != NULL))
                {
                    m_wantsQuit = false;
                    m_enabled = true;

                    m_wantsQuit = true;
                    setAppInactive();
                    ANativeActivity_finish(m_androidApplication->activity);
                }
            }

            /**
            *
            */
            void AndroidEGLWindow::setAppInactive()
            {
                m_isGLES2ContextAvailable = false;
                m_enabled = false;

            }

            /**
            *
            */
            void AndroidEGLWindow::destroyEGL()
            {
                m_logger->info("AndroidEGLWindow::DestroyOpenGLESContext - Start");
                // Destroys OpenGL context.
                if (m_display != EGL_NO_DISPLAY)
                {
                    eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
                    if (m_context != EGL_NO_CONTEXT)
                    {
                        eglDestroyContext(m_display, m_context);
                        m_context = EGL_NO_CONTEXT;
                    }
                    if (m_surface != EGL_NO_SURFACE)
                    {
                        eglDestroySurface(m_display, m_surface);
                        m_surface = EGL_NO_SURFACE;
                    }
                    eglTerminate(m_display);
                    m_display = EGL_NO_DISPLAY;
                }
                m_logger->info("AndroidEGLWindow::DestroyOpenGLESContext - End");
            }

            /**
            *
            */
            void AndroidEGLWindow::callbackEvent(android_app* pApplication, int32_t pCommand)
            {
                AndroidEGLWindow* androidEGLWindow = (AndroidEGLWindow*)pApplication->userData;
                androidEGLWindow->m_logger->info("Processing an event");
                switch (pCommand)
                {
                case APP_CMD_INIT_WINDOW:
                    androidEGLWindow->initWindow();
                    break;
                case APP_CMD_GAINED_FOCUS:
                    androidEGLWindow->setAppActive();
                    break;
                case APP_CMD_TERM_WINDOW:
                    androidEGLWindow->setAppInactive();
                    androidEGLWindow->destroyEGL();
                    break;
                }
            }
        } // end namespace window	
    } // end namespace device
} // end namespace spark
#endif