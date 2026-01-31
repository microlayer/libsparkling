#ifndef __SPARK_POINTCLOUD_POINTCLOUD_HPP_INCLUDED__
#define __SPARK_POINTCLOUD_POINTCLOUD_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "math/Vector3.hpp"
#include "math/Vector2.hpp"
#include "drawing/Color.hpp"
#include "drawing/Vertex3.hpp"
#include "ISparkVertexBuffer.hpp"
#include <vector>
#include <string>
#include "ISparkPointCloud.hpp"

namespace spark {
    namespace pointcloud {

        /**
        *
        */
        class PointCloud : public ISparkPointCloud
        {
        public:
            PointCloud();
            ~PointCloud();

        public:
            std::vector<drawing::Vertex3> getPoints();
            uint32_t getPointCount() const;
            std::vector<drawing::Color> getColors();
            uint32_t getColorCount() const;
            void setColor(spark::drawing::Color color);
            void setPointSize(real32 size);
            real32 getPointSize() const;
            void setVertexBuffer(spark::renderer::ISparkVertexBuffer* vertexBuffer);
            std::string getGuid() const;

        private:
            std::vector<drawing::Vertex3> m_vertices;
            std::vector<drawing::Color> m_colors;
        };
    } // end namespace pointcloud
} // end namespace spark
#endif