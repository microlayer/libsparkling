#include "PointCloud.hpp"
#include "SparkRefCount.hpp"
#include "math/Vector3.hpp"
#include "math/Vector2.hpp"
#include "drawing/Color.hpp"
#include "drawing/Vertex3.hpp"
#include "ISparkVertexBuffer.hpp"
#include <vector>
#include <string>
#include <spark/SparkCompilerConfig.hpp>

namespace spark::geometry::pointcloud {

    /**
    *
    */
    PointCloud::PointCloud()
    {

    }

    /**
    *
    */
    PointCloud::~PointCloud()
    {

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
    void PointCloud::setVertexBuffer(spark::renderer::ISparkVertexBuffer* vertexBuffer)
    {

    }

    /**
    *
    */
    std::string PointCloud::getGuid() const
    {
        return "123";
    }
}
