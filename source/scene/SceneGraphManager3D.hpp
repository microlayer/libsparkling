#ifndef __SPARK_SCENE_SCENEGRAPHMANAGER2D_HPP_INCLUDED__
#define __SPARK_SCENE_SCENEGRAPHMANAGER2D_HPP_INCLUDED__

#include "ISceneGraphManager3D.hpp"

namespace spark {
    namespace scene {
        /**
        *
        */
        class SceneGraphManager3D : public ISceneGraphManager3D
        {
        public:
            SceneGraphManager3D(spark::renderer::ISparkRenderer* renderer);
            virtual ~SceneGraphManager3D();

        public:
            spark::scene::ISparkSceneNode* rootNode();
            void setDefaultCamera();
            void setActiveCamera();
            void drawGraph(spark::renderer::ISparkRenderer* renderer);

        private:
            spark::scene::SceneNode m_rootNode;
            spark::renderer::ISparkRenderer* m_renderer;
        };
    }
}
#endif