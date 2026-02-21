#ifndef __SPARK_SCENE_ISPARKSCENEGRAPHMANAGER3D_HPP_INCLUDED__
#define __SPARK_SCENE_ISPARKSCENEGRAPHMANAGER3D_HPP_INCLUDED__

#include "ISparkRenderer.hpp"
#include "scene/SceneNode.hpp"
#include "ISparkCoordinateSystemNode.hpp"

namespace spark::scene {
    /**
    *
    */
    class ISceneGraphManager3D : public virtual spark::SparkRefCount
    {
    public:
        virtual spark::scene::ISparkSceneNode* rootNode() = 0;
        virtual void drawGraph(spark::renderer::ISparkRenderer* renderer) = 0;

    public: // Factory
        virtual spark::scene::ISparkSceneNode* createSceneNode() = 0;
        virtual spark::scene::ISparkCoordinateSystemNode* createCoordinateSystemNode() = 0;
    };
}
#endif