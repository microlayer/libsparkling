#ifndef __SPARK_SCENE_ISCENEGRAPHMANAGER3D_HPP_INCLUDED__
#define __SPARK_SCENE_ISCENEGRAPHMANAGER3D_HPP_INCLUDED__

#include "ISparkRenderer.hpp"
#include "scene/SceneNode.hpp"

namespace spark {
    namespace scene {
        /**
        *
        */
        class ISceneGraphManager3D : public virtual spark::SparkRefCount
        {

        public:
            virtual spark::scene::SceneNode* rootNode() = 0;
            virtual spark::scene::SceneNode* addChildSceneNode() = 0;
            virtual void drawGraph(spark::renderer::ISparkRenderer* renderer) = 0;
        };
    }
}
#endif