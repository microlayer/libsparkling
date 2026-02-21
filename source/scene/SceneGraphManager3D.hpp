#ifndef __SPARK_SCENE_SCENEGRAPHMANAGER3D_HPP_INCLUDED__
#define __SPARK_SCENE_SCENEGRAPHMANAGER3D_HPP_INCLUDED__

#include "ISparkSceneGraphManager3D.hpp"
#include "CoordinateSystemNode.hpp"
#include "ISparkCoordinateSystemNode.hpp"
#include <Sparkling.hpp>

namespace spark {
    namespace scene {
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

        private:
            spark::scene::SceneNode m_rootNode;
            spark::renderer::ISparkRenderer* m_renderer;
            spark::device::ScreenResolution m_screenResolution;
            spark::log::ISparkLogger* m_logger;
        };
    }
}
#endif