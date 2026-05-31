#ifndef __SPARK_SCENE_CAMERA_ISPARKCAMERA_HPP_INCLUDED__
#define __SPARK_SCENE_CAMERA_ISPARKCAMERA_HPP_INCLUDED__

#include "math/Matrix4.hpp"
#include "SparkRefCount.hpp"

namespace spark::scene::camera {
    /**
    *
    */
    class ISparkCamera : public virtual SparkRefCount
    {
    public:
        virtual spark::math::Matrix4f getProjectionViewMatrix() const = 0;
    };
}
#endif