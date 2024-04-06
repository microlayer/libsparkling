#ifndef __SPARK_SCENE_ISCENEGRAPHMANAGER2D_HPP_INCLUDED__
#define __SPARK_SCENE_ISCENEGRAPHMANAGER2D_HPP_INCLUDED__

#include "ISparkRenderer.hpp"
#include "scene/SceneNode.hpp"

namespace spark {
    namespace scene {
        /**
        *
        */
        class ISceneGraphManager2D : public virtual spark::SparkRefCount
        {
        public:
            virtual void drawGraph(spark::renderer::ISparkRenderer* renderer) = 0;
        };
    }
}
#endif