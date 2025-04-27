#include "VertexBufferFactory.hpp"
#include "renderer/vertexbuffer/OGLVertexBuffer.hpp"

namespace spark {
    namespace renderer {
        /**
        *
        */
        VertexBufferFactory::VertexBufferFactory(spark::log::ISparkLogger* logger)
        {

        }

        /**
        *
        */
        VertexBufferFactory::~VertexBufferFactory()
        {
            for (auto pair : m_vertexBufferMap)
            {
                delete pair.second;
            }
        }

        /**
        *
        */
        spark::renderer::ISparkVertexBuffer* VertexBufferFactory::createOrUpdate(std::string id, std::vector<spark::drawing::Vertex3>& vertices)
        {
            if (m_vertexBufferMap.find(id) == m_vertexBufferMap.end())
            {
                spark::renderer::vertexbuffer::OGLVertexBuffer* vertexBuffer = new spark::renderer::vertexbuffer::OGLVertexBuffer(m_logger, vertices);
                m_vertexBufferMap[id] = vertexBuffer;
                return vertexBuffer;
            }
            else
            {
                return m_vertexBufferMap[id];
            }
        }

        /**
        *
        */
        spark::renderer::ISparkVertexBuffer* VertexBufferFactory::createOrUpdate(std::string id, spark::mesh::ISparkMesh* mesh)
        {
            if (m_vertexBufferMap.find(id) == m_vertexBufferMap.end())
            {
                spark::renderer::vertexbuffer::OGLVertexBuffer* vertexBuffer = new spark::renderer::vertexbuffer::OGLVertexBuffer(m_logger, mesh);
                m_vertexBufferMap[id] = vertexBuffer;
                return vertexBuffer;
            }
            else
            {
                return m_vertexBufferMap[id];
            }
        }
    }
}
