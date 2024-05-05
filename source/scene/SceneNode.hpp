#ifndef __SPARK_SCENE_SCENENODE_HPP_INCLUDED__
#define __SPARK_SCENE_SCENENODE_HPP_INCLUDED__
#include <vector>
#include <math/Vector3.hpp>
#include <ISparkMesh.hpp>

namespace spark {
    namespace scene {
        /**
        *
        */
        class SceneNode
        {
        public:
            SceneNode();
            virtual ~SceneNode();

        public:
            SceneNode* addChildSceneNode();
            bool isRootNode();

        public:
            void setPosition(spark::math::Vector3f position);

        public:
            void attachMesh(spark::mesh::ISparkMesh* mesh);

        private:
            std::vector<SceneNode> m_children;
        };
    }
}
#endif