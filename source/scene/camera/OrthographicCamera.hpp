#ifndef __SPARK_SCENE_CAMERA_ORTHOGRAPHICCAMERA_HPP_INCLUDED__
#define __SPARK_SCENE_CAMERA_ORTHOGRAPHICCAMERA_HPP_INCLUDED__

#include "ISparkOrthoCamera.hpp"

namespace spark::scene::camera {
    /**
    *
    */
    class OrthographicCamera : public ISparkOrthoCamera
    {
    public:
        OrthographicCamera();
        ~OrthographicCamera();

    public:
        spark::math::Matrix4f getProjectionViewMatrix() const;
    };
}
#endif