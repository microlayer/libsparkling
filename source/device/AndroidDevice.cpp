#include "AndroidDevice.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_ANDROID
namespace spark {
    namespace device {
        /**
        *
        */
        AndroidDevice::AndroidDevice(spark::renderer::E_RENDER_ENGINE rendererType, android_app* pApplication) :
            AbstractSparkDevice(rendererType),
            m_androidApplication(pApplication)
        {
            AbstractSparkDevice::construct();

            copyAssetToExternalStorage();
        }

        /**
        *
        */
        AndroidDevice::~AndroidDevice()
        {
            m_logger->release();
            m_fileSystem->release();
            m_window->release();
            m_shader->release();
            m_renderer->release();
        }

        /**
        *
        */
        void AndroidDevice::createLogger()
        {
            m_logger = new spark::log::AndroidLogger();
            if (m_logger != NULL)
            {
                spark::log::LogManager::setLogger(m_logger);
            }
            m_logger->info("Logger successful created for Android device");
        }

        /**
        *
        */
        void AndroidDevice::createFileSystem()
        {
            m_fileSystem = new spark::file::FileSystem(m_logger, getRootPath());
        }

        /**
        *
        */
        void AndroidDevice::createSparkWindow()
        {
            if (m_rendererEngineType == spark::renderer::ERE_OGLES2 ||
                m_rendererEngineType == spark::renderer::ERE_VULKAN13)
            {
                m_window = new spark::device::window::AndroidEGLWindow(m_logger, m_rendererEngineType, m_androidApplication, this);
            }

            // Initialize
            if (!m_window->init())
            {
                exit(EXIT_FAILURE);
            }

            if (!m_window->createWindow())
            {
                m_window->terminate();
                exit(EXIT_FAILURE);
            }
            m_window->setWindowTitle("Microlayer - Sparkling");
        }

        /**
        *
        */
        void AndroidDevice::createShader()
        {
            m_shader = new spark::renderer::shader::OpenGLShaderProgram(m_logger, m_rendererEngineType);
        }

        /**
        *
        */
        void AndroidDevice::createRenderer()
        {
            m_renderer = new spark::renderer::OpenGLES2Renderer(this, m_shader, m_texureFactory, m_vertexBufferFactory);
            m_renderer->onInit();
        }

        /**
        *
        */
        std::string AndroidDevice::getRootPath()
        {
            return "/";
        }

        /**
        * Copies the file to external storage private to the app, no special permissions needed on Android 10+.
        */
        void AndroidDevice::copyAssetToExternalStorage()
        {
            JNIEnv* env = m_androidApplication->activity->env;
            AAssetManager* assetManager = m_androidApplication->activity->assetManager;

            jclass activityClass = env->GetObjectClass(m_androidApplication->activity->clazz);
            jmethodID getExternalFilesDir = env->GetMethodID(activityClass, "getExternalFilesDir", "(Ljava/lang/String;)Ljava/io/File;");
            jobject fileObj = env->CallObjectMethod(m_androidApplication->activity->clazz, getExternalFilesDir, nullptr);

            jclass fileClass = env->GetObjectClass(fileObj);
            jmethodID getPath = env->GetMethodID(fileClass, "getAbsolutePath", "()Ljava/lang/String;");
            jstring pathString = (jstring)env->CallObjectMethod(fileObj, getPath);

            const char* path = env->GetStringUTFChars(pathString, 0);

            // Copy asset
            std::string assetName = "test.dat";

            // Create full output path
            char fullDestPath[1024];
            snprintf(fullDestPath, sizeof(fullDestPath), "%s/%s", path, assetName.c_str());
            m_logger->info("Saving asset to: %s", fullDestPath);

            // Open asset            
            AAsset* asset = AAssetManager_open(assetManager, assetName.c_str(), AASSET_MODE_STREAMING);
            if (!asset)
            {
                m_logger->error("Failed to open asset: %s", assetName.c_str());
                return;
            }
        }
    } // end namespace device
} // end namespace spark
#endif
