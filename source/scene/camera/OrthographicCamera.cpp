#include "OrthographicCamera.hpp"

namespace spark::scene::camera {
    /**
    *
    */
    OrthographicCamera::OrthographicCamera()
    {

    }

    /**
    *
    */
    OrthographicCamera::~OrthographicCamera()
    {

    }

    /**
    *
    */
    spark::math::Matrix4f OrthographicCamera::getProjectionViewMatrix() const
    {
        spark::math::Matrix4f m;
        return m;
    }
}