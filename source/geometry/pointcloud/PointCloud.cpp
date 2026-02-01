#include "PointCloud.hpp"

namespace spark::geometry::pointcloud {

    /**
    *
    */
    PointCloud::PointCloud()
    {
        if (m_guid.empty())
        {
            m_guid = spark::mlstl::guid::MLGuid::createGuid();
        }
    }

    /**
    *
    */
    PointCloud::~PointCloud()
    {
        if (m_vertexBuffer != NULL) m_vertexBuffer->release();
    }

    /**
    *
    */
    std::vector<drawing::Vertex3> PointCloud::getPoints()
    {
        return m_vertices;
    }

    /**
    *
    */
    uint32_t PointCloud::getPointCount() const
    {
        return 0;
    }

    /**
    *
    */
    std::vector<drawing::Color> PointCloud::getColors()
    {
        return m_colors;
    }

    /**
    *
    */
    uint32_t PointCloud::getColorCount() const
    {
        return 0;
    }

    /**
    *
    */
    void PointCloud::setColor(spark::drawing::Color color)
    {

    }

    /**
    *
    */
    void PointCloud::setPointSize(real32 size)
    {

    }

    /**
    *
    */
    real32 PointCloud::getPointSize() const
    {
        return 1.0;
    }

    /**
    *
    */
    void PointCloud::addVertex(drawing::Vertex3 vertex)
    {
        m_vertices.push_back(vertex);
    }

    /**
    *
    */
    void PointCloud::setVertexBuffer(spark::renderer::ISparkVertexBuffer* vertexBuffer)
    {
        m_vertexBuffer = vertexBuffer;
    }

    /**
    *
    */
    std::string PointCloud::getGuid() const
    {
        return m_guid;
    }
}
