#include "DirectionalLightNode.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    DirectionalLightNode::DirectionalLightNode()
    {
    }

    /**
    *
    */
    DirectionalLightNode::~DirectionalLightNode()
    {
    }

    /**
    *
    */
    void DirectionalLightNode::setDirection(spark::math::Vector3f lightDirection)
    {
        m_lightDirection = lightDirection;
    }

    /**
    *
    */
    spark::math::Vector3f DirectionalLightNode::getDirection()
    {
        return m_lightDirection;
    }

    /**
    *
    */
    LightType DirectionalLightNode::getLightType()
    {
        return spark::scene::nodes::LightType::Directional;
    }

    /**
    * 
    */
    spark::math::Matrix4f DirectionalLightNode::getLightViewProjectionMatrix()
    {
        float size = 5.0f;

        real32 orthoArray[16];
        spark::math::ProjectionMatrixf::createOrthofMatrix(
            -size,
            size,
            -size,
            size,
            0.5,
            50.0f,
            orthoArray);

        spark::math::Matrix4f projectionMatrix;
        memcpy(projectionMatrix.m_matrix, orthoArray, sizeof(orthoArray));


        real32 shadowDistance = 20;
        spark::math::Vector3f sceneCenter(0.0, 0.0, 0.0);
        spark::math::Vector3f lightPosition = sceneCenter - m_lightDirection * shadowDistance;

        real32 viewArray[16];
        spark::math::ProjectionMatrixf::createLookAtMatrix(
            lightPosition.m_x, lightPosition.m_y, lightPosition.m_z,
            0, 0, 0,
            0, 1, 0,
            viewArray);

        spark::math::Matrix4f viewMatrix;
        memcpy(viewMatrix.m_matrix, viewArray, sizeof(viewArray));


        spark::math::Matrix4f shadowMatrix = projectionMatrix * viewMatrix;

        return shadowMatrix;
    }

    /**
    *
    */
    bool DirectionalLightNode::castsShadows()
    {
        return true;
    }

    /**
    *
    */
    void DirectionalLightNode::render(spark::renderer::ISparkRenderer* renderer)
    {

    }
}