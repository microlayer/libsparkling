#ifndef __SPARK_POINTCLOUD_ISPARKPOINTCLOUD_HPP_INCLUDED__
#define __SPARK_POINTCLOUD_ISPARKPOINTCLOUD_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "drawing/Color.hpp"
#include "drawing/Vertex3.hpp"
#include "ISparkVertexBuffer.hpp"
#include <vector>
#include <string>

namespace spark {
    namespace pointcloud {

        /**
        *
        */
        class ISparkPointCloud : public virtual spark::SparkRefCount
        {

        public:
            /**
            * Returns all points in the cloud
            */
            virtual std::vector<drawing::Vertex3> getPoints() = 0;

            /**
            * Returns the number of points
            */
            virtual uint32_t getPointCount() const = 0;

            /**
            * Returns colors
            */
            virtual std::vector<drawing::Color> getColors() = 0;

            /**
            * Returns number of colors (pointCount*4)
            */
            virtual uint32_t getColorCount() const = 0;

            /**
            * Set a uniform color for all points
            */
            virtual void setColor(spark::drawing::Color color) = 0;

            /**
            * Set point size in pixels
            */
            virtual void setPointSize(real32 size) = 0;

            /**
            * Returns point size
            */
            virtual real32 getPointSize() const = 0;

            /**
            * Assign VertexBuffer
            */
            virtual void setVertexBuffer(spark::renderer::ISparkVertexBuffer* vertexBuffer) = 0;

            /**
            * Gets the unique ID of the pointcloud
            */
            virtual std::string getGuid() const = 0;
        };
    } // end namespace pointcloud
} // end namespace spark
#endif