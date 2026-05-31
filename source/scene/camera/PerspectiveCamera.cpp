#include "PerspectiveCamera.hpp"

namespace spark::scene::camera {
    /**
    *
    */
    PerspectiveCamera::PerspectiveCamera(spark::real32 aspect) :
        m_fovy(20.0),
        m_aspect(aspect),
        m_zNear(0.1),
        m_zFar(100.0),
        m_position(0, 0, 5.67),
        m_target(0, 0, 0),
        m_up(0, 1.0, 0)
    {
        updateView();
    }

    /**
    *
    */
    PerspectiveCamera::~PerspectiveCamera()
    {

    }

    /**
    *
    */
    void PerspectiveCamera::setPerspective(real32 fovy, real32 aspect, real32 zNear, real32 zFar)
    {
        m_fovy = fovy;
        m_aspect = aspect;
        m_zNear = zNear;
        m_zFar = zFar;

        updateView();
    }

    /**
    *
    */
    void PerspectiveCamera::setPosition(const math::Vector3f& position)
    {
        m_position = position;

        updateView();
    }

    /**
    *
    */
    void PerspectiveCamera::lookAt(const math::Vector3f& target, const math::Vector3f& up)
    {
        m_target = target;
        m_up = up;

        updateView();
    }

    /**
    *
    */
    spark::math::Matrix4f PerspectiveCamera::getProjectionViewMatrix() const
    {
        return m_projectionViewMatrix;
    }

    /**
    *
    */
    void PerspectiveCamera::updateView()
    {
        real32 perspectiveArray[16];
        spark::math::ProjectionMatrixf::createPerspectiveMatrix(m_fovy, m_aspect, m_zNear, m_zFar, perspectiveArray);
        memcpy(m_projectionMatrix.m_matrix, perspectiveArray, sizeof(perspectiveArray));

        real32 lookAtArray[16];
        spark::math::ProjectionMatrixf::createLookAtMatrix(
            m_position.m_x, m_position.m_y, m_position.m_z,
            m_target.m_x, m_target.m_y, m_target.m_z,
            m_up.m_x, m_up.m_y, m_up.m_z, lookAtArray);
        memcpy(m_viewMatrix.m_matrix, lookAtArray, sizeof(lookAtArray));

        m_projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
    }
}