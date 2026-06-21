#ifndef __SPARK_SCENE_SCENEGRAPHMANAGER3D_HPP_INCLUDED__
#define __SPARK_SCENE_SCENEGRAPHMANAGER3D_HPP_INCLUDED__

#include "ISparkSceneGraphManager3D.hpp"
#include "nodes/CoordinateSystemNode.hpp"
#include "nodes/LightNode.hpp"
#include "ISparkCoordinateSystemNode.hpp"
#include "ISparkDirectionalLightNode.hpp"
#include "nodes/DirectionalLightNode.hpp"
#include "nodes/PointLightNode.hpp"
#include "Sparkling.hpp"
#include "ISparkLightNode.hpp"
#include "ISparkMeshSceneNode.hpp"
#include "nodes/MeshSceneNode.hpp"
#include "nodes/PointCloudSceneNode.hpp"
#include "camera/PerspectiveCamera.hpp"
#include "ISparkPointLightNode.hpp"
#include "renderer/lightbuffer/GPUDirectionalLight.hpp"
#include "renderer/lightbuffer/GPUPointLight.hpp"

namespace spark::scene {
    /**
    *
    */
    class SceneGraphManager3D : public ISceneGraphManager3D
    {
    public:
        SceneGraphManager3D(spark::renderer::ISparkRenderer* renderer,
            spark::device::ScreenResolution screenResolution,
            spark::log::ISparkLogger* logger);
        virtual ~SceneGraphManager3D();

    public:
        spark::scene::nodes::ISparkSceneNode* rootNode();
        void setDefaultCamera();
        void setActiveCamera(spark::scene::camera::ISparkPerspectiveCamera* camera);
        void addLight(spark::scene::nodes::ISparkLightNode* lightNode);
        void drawGraph(spark::renderer::ISparkRenderer* renderer);

    private:
        void applyCamera();
        void applyLight();

    private:
        void onBeforeDrawGraph();
        void onAfterDrawGraph();

    public: // Factory        
        spark::scene::nodes::ISparkMeshSceneNode* createMeshSceneNode();
        spark::scene::nodes::ISparkPointCloudSceneNode* createPointCloudSceneNode();
        spark::scene::nodes::ISparkCoordinateSystemNode* createCoordinateSystemNode();

        // Light
        spark::scene::nodes::ISparkDirectionalLightNode* createDirectionalLightNode();
        spark::scene::nodes::ISparkPointLightNode* createPointLightNode();

    private:
        spark::scene::nodes::SceneNode m_rootNode;
        spark::renderer::ISparkRenderer* m_renderer;
        spark::device::ScreenResolution m_screenResolution;
        spark::log::ISparkLogger* m_logger;

        spark::scene::camera::ISparkCamera* m_activeCamera;
        spark::scene::camera::PerspectiveCamera m_defaultCamera;

        std::vector<spark::scene::nodes::ISparkLightNode*> m_lights;
    };
}
#endif