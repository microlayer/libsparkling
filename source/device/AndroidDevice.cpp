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
            copyAssetToExternalStorage();
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
            return m_rootPath;
        }

        /**
        * Copies the assets to external storage private to the app, no special permissions needed on Android 10+.
        */
        void AndroidDevice::copyAssetToExternalStorage()
        {
            m_logger->info("Start to copy assets to local file system");

            JavaVM* javaVM = m_androidApplication->activity->vm;
            JNIEnv* env;
            javaVM->AttachCurrentThread(&env, NULL);

            AAssetManager* assetManager = m_androidApplication->activity->assetManager;

            // Get external filesystem location
            jclass activityClass = env->GetObjectClass(m_androidApplication->activity->clazz);
            jmethodID getExternalFilesDir = env->GetMethodID(activityClass, "getExternalFilesDir", "(Ljava/lang/String;)Ljava/io/File;");
            jobject fileObj = env->CallObjectMethod(m_androidApplication->activity->clazz, getExternalFilesDir, NULL);

            jclass fileClass = env->GetObjectClass(fileObj);
            jmethodID getPath = env->GetMethodID(fileClass, "getAbsolutePath", "()Ljava/lang/String;");
            jstring pathString = (jstring)env->CallObjectMethod(fileObj, getPath);

            const char* path = env->GetStringUTFChars(pathString, 0);
            m_logger->info("Path in external filesystem is %s", path);

            AAssetDir* assetDir = AAssetManager_openDir(assetManager, ""); // "" will open root location 'src/main/assets'

            if (assetDir != NULL)
            {
                m_logger->info("AAssetDir opened successfully");

                // List assets 
                std::vector<std::string> fileNames;
                const char* fileName;
                while ((fileName = AAssetDir_getNextFileName(assetDir)) != NULL)
                {
                    m_logger->info("File: %s%s", "/assets/", fileName);
                    fileNames.push_back(fileName);
                }
                m_logger->info("Found %i files in assets folder", fileNames.size());

                // Copy asset to external filesystem location
                for (std::string fileName : fileNames)
                {
                    AAsset* asset = AAssetManager_open(assetManager, fileName.c_str(), AASSET_MODE_STREAMING);
                    if (!asset)
                    {
                        m_logger->error("Failed to open asset: %s", fileName.c_str());
                    }
                    else
                    {
                        std::string filePath = std::string(path) + "/" + fileName;
                        FILE* outFile = fopen(filePath.c_str(), "wb");
                        if (!outFile)
                        {
                            m_logger->error("Failed to open destination file: %s\n", path);
                        }
                        else
                        {
                            // check if file exeeds size
                            const size_t bufferSize = 500000;
                            c8_t buffer[bufferSize];
                            int32_t bytesRead;

                            while ((bytesRead = AAsset_read(asset, buffer, bufferSize)) > 0)
                            {
                                fwrite(buffer, 1, bytesRead, outFile);
                            }
                            m_logger->info("Copy of file %s to %s was successful", fileName.c_str(), path);
                            fclose(outFile);
                            AAsset_close(asset);
                        }
                    }
                }

                AAssetDir_close(assetDir);
            }
            else
            {
                m_logger->error("Failed to open AAssetDir");
            }

            m_rootPath = std::string(path) + std::string("/");
            m_logger->info("Setting root path to %s", m_rootPath.c_str());
        }
    } // end namespace device
} // end namespace spark
#endif
