#ifndef __SPARK_RENDERER_VERTEXBUFFER_OGLVERTEXBUFFER_HPP_INCLUDED__
#define __SPARK_RENDERER_VERTEXBUFFER_OGLVERTEXBUFFER_HPP_INCLUDED__

#include "ISparkVertexBuffer.hpp"
#include "ISparkLogger.hpp"
#include "ISparkMesh.hpp"
#if SPARK_PLATFORM == SPARK_PLATFORM_WINDOWS || \
    SPARK_PLATFORM == SPARK_PLATFORM_LINUX   || \
    SPARK_PLATFORM == SPARK_PLATFORM_APPLE
#include <GL/glew.h>
#endif
#if SPARK_PLATFORM == SPARK_PLATFORM_WEBGL || \
    SPARK_PLATFORM == SPARK_PLATFORM_ANDROID
#include <GLES3/gl3.h>
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
                OGLVertexBuffer(spark::log::ISparkLogger* logger, spark::mesh::ISparkMesh* mesh);
                ~OGLVertexBuffer();

            public:
                void allocateBuffer();
                void uploadBuffer();

            public:
                void draw();
                void drawTriangles();

            private:
                GLuint m_vao, m_vbo, m_cbo, m_ibo;

                int m_bufferSizeVertices;
                int m_bufferSizeColor;
                int m_bufferSizeIndices;

                std::vector<real32> m_verticesData;
                std::vector<uc8_t> m_colorData;
                spark::mesh::ISparkMesh* m_mesh;
            };
        }
    }
}
#endif