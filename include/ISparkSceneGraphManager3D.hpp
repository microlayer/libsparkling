#ifndef __SPARK_SCENE_ISPARKSCENEGRAPHMANAGER3D_HPP_INCLUDED__
#define __SPARK_SCENE_ISPARKSCENEGRAPHMANAGER3D_HPP_INCLUDED__

#include "ISparkRenderer.hpp"
#include "scene/nodes/SceneNode.hpp"
#include "ISparkCoordinateSystemNode.hpp"
#include "ISparkDirectionalLightNode.hpp"
#include "ISparkMeshSceneNode.hpp"
#include "ISparkPointCloudSceneNode.hpp"
#include "ISparkPerspectiveCamera.hpp"

namespace spark::scene {
    /**
    *
    */
    class ISceneGraphManager3D : public virtual spark::SparkRefCount
    {
    public:
        virtual spark::scene::nodes::ISparkSceneNode* rootNode() = 0;
        virtual void setActiveCamera(spark::scene::camera::ISparkPerspectiveCamera* camera) = 0;
        virtual void drawGraph(spark::renderer::ISparkRenderer* renderer) = 0;

    public: // Factory
        virtual spark::scene::camera::ISparkPerspectiveCamera* createPerspectiveCamera() = 0;
        virtual spark::scene::nodes::ISparkMeshSceneNode* createMeshSceneNode() = 0;
        virtual spark::scene::nodes::ISparkPointCloudSceneNode* createPointCloudSceneNode() = 0;
        virtual spark::scene::nodes::ISparkCoordinateSystemNode* createCoordinateSystemNode() = 0;
        virtual spark::scene::nodes::ISparkDirectionalLightNode* createDirectionalLightNode() = 0;
    };
}
#endif