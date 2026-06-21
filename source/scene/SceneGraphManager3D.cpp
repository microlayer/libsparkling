#include "scene/SceneGraphManager3D.hpp"

namespace spark::scene {
    /**
    *
    */
    SceneGraphManager3D::SceneGraphManager3D(
        spark::renderer::ISparkRenderer* renderer,
        spark::device::ScreenResolution screenResolution,
        spark::log::ISparkLogger* logger) : m_renderer(renderer),
        m_screenResolution(screenResolution),
        m_logger(logger),
        m_activeCamera(NULL),
        m_defaultCamera(screenResolution.m_ratio)
    {
        m_renderer->setDrawMode(0);
    }

    /**
    *
    */
    SceneGraphManager3D::~SceneGraphManager3D()
    {
        for (auto& light : m_lights)
        {
            light->release();
        }
        m_lights.clear();
    }

    /**
    *
    */
    spark::scene::nodes::ISparkSceneNode* SceneGraphManager3D::rootNode()
    {
        return &m_rootNode;
    }

    /**
    *
    */
    void SceneGraphManager3D::setDefaultCamera()
    {
        m_renderer->setViewMatrix(m_defaultCamera.getViewMatrix());
        m_renderer->setPerspectiveProjectionMatrix(m_defaultCamera.getProjectionViewMatrix());
    }

    /**
    *
    */
    void SceneGraphManager3D::setActiveCamera(spark::scene::camera::ISparkPerspectiveCamera* camera)
    {
        m_activeCamera = camera;
    }

    /**
    *
    */
    void SceneGraphManager3D::addLight(spark::scene::nodes::ISparkLightNode* lightNode)
    {
        lightNode->addRef();
        m_lights.push_back(lightNode);
    }

    /**
    *
    */
    void SceneGraphManager3D::drawGraph(spark::renderer::ISparkRenderer* renderer)
    {
        applyCamera();
        applyLight();

        onBeforeDrawGraph();

        if (!m_rootNode.getChildren().empty())
        {
            for (spark::scene::nodes::ISparkSceneNode* node : m_rootNode.getChildren())
            {
                if (node)
                {
                    node->render(renderer);
                }
            }
        }

        onAfterDrawGraph();
    }

    /**
    *
    */
    void SceneGraphManager3D::applyCamera()
    {
        if (m_activeCamera == NULL)
        {
            setDefaultCamera();
        }
        else
        {
            auto projectionViewMatrix = m_activeCamera->getProjectionViewMatrix();
            m_renderer->setViewMatrix(m_defaultCamera.getViewMatrix());
            m_renderer->setPerspectiveProjectionMatrix(projectionViewMatrix);
        }
    }

    /**
    *
    */
    void SceneGraphManager3D::applyLight()
    {
        if (m_lights.size() > 0)
        {
            std::vector<renderer::lightbuffer::GPUDirectionalLight> gpuDirectionalLights;
            std::vector<renderer::lightbuffer::GPUPointLight> gpuPointLights;

            for (auto* light : m_lights)
            {
                switch (light->getLightType())
                {
                case spark::scene::nodes::LightType::Directional:
                {
                    renderer::lightbuffer::GPUDirectionalLight gpuDirectionalLight;
                    spark::scene::nodes::ISparkDirectionalLightNode* l = dynamic_cast<spark::scene::nodes::ISparkDirectionalLightNode*>(light);
                    gpuDirectionalLight.color = l->getLightColor();
                    gpuDirectionalLight.direction = l->getDirection();
                    gpuDirectionalLight.intensity = l->getIntesity();

                    gpuDirectionalLights.push_back(gpuDirectionalLight);
                    break;
                }
                case spark::scene::nodes::LightType::Point:
                {
                    renderer::lightbuffer::GPUPointLight gpuPointLight;
                    spark::scene::nodes::ISparkPointLightNode* l = dynamic_cast<spark::scene::nodes::ISparkPointLightNode*>(light);
                    gpuPointLight.position = l->getPosition();
                    gpuPointLight.color = l->getLightColor();
                    gpuPointLight.intensity = l->getIntesity();
                    gpuPointLight.range = l->getRange();

                    gpuPointLights.push_back(gpuPointLight);
                    break;
                }
                }
            }

            m_renderer->uploadLights(gpuDirectionalLights, gpuPointLights);
        }
    }

    /**
    *
    */
    void SceneGraphManager3D::onBeforeDrawGraph()
    {
        m_renderer->activateDepthTest(true);
    }

    /**
    *
    */
    void SceneGraphManager3D::onAfterDrawGraph()
    {
        m_renderer->flush3DLines();

        m_renderer->activateDepthTest(false);
        m_renderer->setDrawMode(0);
    }

    /**
    *
    */
    spark::scene::nodes::ISparkMeshSceneNode* SceneGraphManager3D::createMeshSceneNode()
    {
        return new spark::scene::nodes::MeshSceneNode();
    }

    /**
    *
    */
    spark::scene::nodes::ISparkPointCloudSceneNode* SceneGraphManager3D::createPointCloudSceneNode()
    {
        return new spark::scene::nodes::PointCloudSceneNode();
    }

    /**
    *
    */
    spark::scene::nodes::ISparkCoordinateSystemNode* SceneGraphManager3D::createCoordinateSystemNode()
    {
        return new spark::scene::nodes::CoordinateSystemNode();
    }

    /**
    *
    */
    spark::scene::nodes::ISparkDirectionalLightNode* SceneGraphManager3D::createDirectionalLightNode()
    {
        return new spark::scene::nodes::DirectionalLightNode();
    }

    /**
    *
    */
    spark::scene::nodes::ISparkPointLightNode* SceneGraphManager3D::createPointLightNode()
    {
        return new spark::scene::nodes::PointLightNode();
    }
}