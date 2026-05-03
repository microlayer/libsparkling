#ifndef __SPARK_SCENE_NODES_MESHSCENENODE_HPP_INCLUDED__
#define __SPARK_SCENE_NODES_MESHSCENENODE_HPP_INCLUDED__

#include "SceneNode.hpp"
#include "ISparkMeshSceneNode.hpp"

namespace spark::scene::nodes {
    /**
    *
    */
    class MeshSceneNode : public spark::scene::nodes::SceneNode, public spark::scene::nodes::ISparkMeshSceneNode
    {
    public:
        MeshSceneNode();
        virtual ~MeshSceneNode();

    public:
        void attachMesh(spark::geometry::mesh::ISparkMesh* mesh) override;
        spark::geometry::mesh::ISparkMesh* getMesh() override;
        virtual void render(spark::renderer::ISparkRenderer* renderer) override;

    private:
        spark::geometry::mesh::ISparkMesh* m_mesh;
    };
}
#endif