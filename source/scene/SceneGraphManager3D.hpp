#ifndef __SPARK_SCENE_SCENEGRAPHMANAGER3D_HPP_INCLUDED__
#define __SPARK_SCENE_SCENEGRAPHMANAGER3D_HPP_INCLUDED__

#include "ISceneGraphManager3D.hpp"
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

        private:
            spark::scene::SceneNode m_rootNode;
            spark::renderer::ISparkRenderer* m_renderer;
            spark::device::ScreenResolution m_screenResolution;
            spark::log::ISparkLogger* m_logger;
        };
    }
}
#endif