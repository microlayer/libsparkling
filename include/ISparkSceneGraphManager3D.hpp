#ifndef __SPARK_SCENE_ISPARKSCENEGRAPHMANAGER3D_HPP_INCLUDED__
#define __SPARK_SCENE_ISPARKSCENEGRAPHMANAGER3D_HPP_INCLUDED__

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
            virtual spark::scene::ISparkSceneNode* rootNode() = 0;
            virtual void drawGraph(spark::renderer::ISparkRenderer* renderer) = 0;
        };
    }
}
#endif