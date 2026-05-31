#ifndef __SPARK_SCENE_CAMERA_PERSPECTIVECAMERA_HPP_INCLUDED__
#define __SPARK_SCENE_CAMERA_PERSPECTIVECAMERA_HPP_INCLUDED__

#include "ISparkPerspectiveCamera.hpp"
#include "math/ProjectionMatrix.hpp"

namespace spark::scene::camera {
    /**
    *
    */
    class PerspectiveCamera : public ISparkPerspectiveCamera
    {
    public:
        PerspectiveCamera(spark::real32 aspect);
        ~PerspectiveCamera();

    public:
        void setPerspective(real32 fovy, real32 aspect, real32 zNear, real32 zFar);
        void setPosition(const math::Vector3f& position);
        void lookAt(const math::Vector3f& target, const math::Vector3f& up);

    public:
        spark::math::Matrix4f getProjectionViewMatrix() const;

    private:
        void updateView();

    private:
        real32 m_fovy;
        real32 m_aspect;
        real32 m_zNear;
        real32 m_zFar;

        math::Vector3f m_position;
        math::Vector3f m_target;
        math::Vector3f m_up;

        math::Matrix4f m_viewMatrix;
        math::Matrix4f m_projectionMatrix;
        math::Matrix4f m_projectionViewMatrix;
    };
}
#endif