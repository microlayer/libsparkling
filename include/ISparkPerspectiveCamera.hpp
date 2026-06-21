#ifndef __SPARK_SCENE_CAMERA_ISPARKPERSPECTIVECAMERA_HPP_INCLUDED__
#define __SPARK_SCENE_CAMERA_ISPARKPERSPECTIVECAMERA_HPP_INCLUDED__

#include "ISparkCamera.hpp"

namespace spark::scene::camera {
    /**
    *
    */
    class ISparkPerspectiveCamera : public virtual ISparkCamera
    {
    public:
        virtual void setPerspective(real32 fovy, real32 aspect, real32 zNear, real32 zFar) = 0;

    public:
        virtual void setPosition(const math::Vector3f& position) = 0;
        virtual void lookAt(const math::Vector3f& target, const math::Vector3f& up) = 0;

    public:
        virtual spark::math::Matrix4f getViewMatrix() const = 0;
    };
}
#endif