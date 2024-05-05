#ifndef __SPARK_SCENE_SCENENODE_HPP_INCLUDED__
#define __SPARK_SCENE_SCENENODE_HPP_INCLUDED__
#include <vector>
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

        private:
            std::vector<SceneNode> m_children;
        };
    }
}
#endif