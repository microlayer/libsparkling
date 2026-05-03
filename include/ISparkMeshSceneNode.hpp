#ifndef __SPARK_SCENE_NODES_ISPARKMESHSCENENODE_HPP_INCLUDED__
#define __SPARK_SCENE_NODES_ISPARKMESHSCENENODE_HPP_INCLUDED__

#include "ISparkSceneNode.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    class ISparkMeshSceneNode : public virtual ISparkSceneNode
    {
    public:
        virtual void attachMesh(spark::geometry::mesh::ISparkMesh* mesh) = 0;
        virtual spark::geometry::mesh::ISparkMesh* getMesh() = 0;
    };
}
#endif