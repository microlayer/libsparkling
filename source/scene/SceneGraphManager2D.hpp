#ifndef __SPARK_SCENE_SCENEGRAPHMANAGER2D_HPP_INCLUDED__
#define __SPARK_SCENE_SCENEGRAPHMANAGER2D_HPP_INCLUDED__

#include "ISparkRenderer.hpp"
#include "ISceneGraphManager2D.hpp"

namespace spark {
    namespace scene {

        /**
        *
        */
        class SceneGraphManager2D : public ISceneGraphManager2D
        {
        public:
            void drawGraph(spark::renderer::ISparkRenderer* renderer);
        };
    }
}
#endif