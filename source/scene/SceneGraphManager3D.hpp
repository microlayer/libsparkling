#ifndef __SPARK_SCENE_SCENEGRAPHMANAGER3D_HPP_INCLUDED__
#define __SPARK_SCENE_SCENEGRAPHMANAGER3D_HPP_INCLUDED__

#include "ISparkSceneGraphManager3D.hpp"
#include "CoordinateSystemNode.hpp"
#include "ISparkCoordinateSystemNode.hpp"
#include "ISparkDirectionalLightNode.hpp"
#include <Sparkling.hpp>
#include <ISparkLightNode.hpp>
#include "LightNode.hpp"

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
        spark::scene::ISparkSceneNode* rootNode();
        void setDefaultCamera();
        void setActiveCamera();
        void drawGraph(spark::renderer::ISparkRenderer* renderer);

    private:
        void onBeforeDrawGraph();
        void onAfterDrawGraph();

    public: // Factory
        spark::scene::ISparkSceneNode* createSceneNode();
        spark::scene::ISparkCoordinateSystemNode* createCoordinateSystemNode();
        spark::scene::ISparkDirectionalLightNode* createDirectionalLightNode();

    private:
        spark::scene::SceneNode m_rootNode;
        spark::renderer::ISparkRenderer* m_renderer;
        spark::device::ScreenResolution m_screenResolution;
        spark::log::ISparkLogger* m_logger;
    };
}
#endif