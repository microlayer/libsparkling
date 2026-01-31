#ifndef __SPARK_RENDERER_VERTEXBUFFER_OGLVERTEXBUFFER_HPP_INCLUDED__
#define __SPARK_RENDERER_VERTEXBUFFER_OGLVERTEXBUFFER_HPP_INCLUDED__

#include "ISparkVertexBuffer.hpp"
#include "ISparkLogger.hpp"
#include "ISparkMesh.hpp"
#include <ISparkMaterial.hpp>
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

namespace spark::renderer::vertexbuffer {
    /**
    *
    */
    class OGLVertexBuffer : public ISparkVertexBuffer
    {
    public:
        OGLVertexBuffer(spark::log::ISparkLogger* logger, std::vector<spark::drawing::Vertex3>& vertices);
        OGLVertexBuffer(spark::log::ISparkLogger* logger, spark::geometry::mesh::ISparkMesh* mesh, spark::material::VertexLayout vertexLayout);
        ~OGLVertexBuffer();

    private:
        void buildIndexedGPULayout();
        void buildNonIndexedGPULayout();

    private:
        void allocateBuffer();
        void uploadBuffer();

    public:
        void drawPoints();
        void drawLines();
        void drawTriangles();

    private:
        GLuint m_vao, m_vbo, m_nbo, m_cbo, m_bbo, m_ibo;

        int m_bufferSizeVertices;
        int m_bufferSizeNormals;
        int m_bufferSizeColor;
        int m_bufferSizeBarycentric;
        int m_bufferSizeIndices;
        int m_verticesCount;

        std::vector<real32> m_verticesData;
        std::vector<real32> m_normalData;
        std::vector<uc8_t> m_colorData;
        std::vector<real32> m_barycentricData;
        spark::geometry::mesh::ISparkMesh* m_mesh;
        spark::material::VertexLayout m_vertexLayout = spark::material::VertexLayout::NonIndexed;
    };
}
#endif