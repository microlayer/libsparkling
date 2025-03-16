#ifndef __SPARK_RENDERER_VERTEXBUFFER_OGLVERTEXBUFFER_HPP_INCLUDED__
#define __SPARK_RENDERER_VERTEXBUFFER_OGLVERTEXBUFFER_HPP_INCLUDED__

#include "ISparkVertexBuffer.hpp"
#include "ISparkLogger.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS || \
    SPARK_PLATFORM == SPARK_PLATFORM_LINUX   || \
    SPARK_PLATFORM == SPARK_PLATFORM_APPLE
#include <GL/glew.h>
#endif
#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL || \
    SPARK_PLATFORM == SPARK_PLATFORM_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif
#include <vector>

namespace spark {
    namespace renderer {
        namespace vertexbuffer {
            /**
            *
            */
            class OGLVertexBuffer : public ISparkVertexBuffer
            {
            public:
                OGLVertexBuffer(spark::log::ISparkLogger* logger, std::vector<spark::drawing::Vertex3>& vertices);
                ~OGLVertexBuffer();

            public:
                void allocateBuffer();
                void uploadBuffer();

            public:
                void draw();

            private:
                GLuint m_vao, m_vbo, m_cbo;
                std::vector<spark::drawing::Vertex3>& m_vertices;
            };
        }
    }
}
#endif