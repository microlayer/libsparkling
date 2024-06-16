#ifndef __SPARK_SCENE_SCENENODE_HPP_INCLUDED__
#define __SPARK_SCENE_SCENENODE_HPP_INCLUDED__

#include <vector>
#include <math/Vector3.hpp>
#include <ISparkMesh.hpp>
#include <ISparkSceneNode.hpp>

namespace spark {
    namespace scene {
        /**
        *
        */
        class SceneNode : public spark::scene::ISparkSceneNode
        {
        public:
            SceneNode();
            virtual ~SceneNode();

        public:
            void addChildSceneNode(spark::scene::ISparkSceneNode* node);
            bool isRootNode();
            std::vector<ISparkSceneNode*> getChildren();

        public:
            spark::mesh::ISparkMesh* getMesh();

        public:
            void setPosition(spark::math::Vector3f position);

        public:
            void attachMesh(spark::mesh::ISparkMesh* mesh);

        private:
            std::vector<ISparkSceneNode*> m_children;
            spark::math::Vector3f m_position;
            spark::mesh::ISparkMesh* m_mesh;
        };
    }
}
#endif