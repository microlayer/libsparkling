#ifndef __SPARK_SCENE_SCENEGRAPHMANAGER2D_HPP_INCLUDED__
#define __SPARK_SCENE_SCENEGRAPHMANAGER2D_HPP_INCLUDED__

#include "ISparkRenderer.hpp"
#include "ISceneGraphManager3D.hpp"
#include "scene/SceneNode.hpp"

namespace spark {
    namespace scene {
        /**
        *
        */
        class SceneGraphManager3D : public ISceneGraphManager3D
        {
        public:
            SceneGraphManager3D();
            virtual ~SceneGraphManager3D();

        public:
            spark::scene::SceneNode* rootNode();           
            void drawGraph(spark::renderer::ISparkRenderer* renderer);
        };
    }
}
#endif