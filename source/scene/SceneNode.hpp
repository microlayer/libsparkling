#ifndef __SPARK_SCENE_SCENENODE_HPP_INCLUDED__
#define __SPARK_SCENE_SCENENODE_HPP_INCLUDED__

#include "ISparkSceneNode.hpp"
#include <material/MaterialLibrary.hpp>

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
            bool isRootNode();
            void addChildSceneNode(spark::scene::ISparkSceneNode* node);
            std::vector<ISparkSceneNode*> getChildren();

        public:
            void setPosition(spark::math::Vector3f position);
            void setRotation(spark::math::Vector3f rotation);

        public:
            void attachMesh(spark::mesh::ISparkMesh* mesh);
            spark::mesh::ISparkMesh* getMesh();
            void addAnimator(spark::animator::ISparkNodeAnimator* nodeAnimator);

        public:
            void render(spark::renderer::ISparkRenderer* renderer);

        private:
            void animate();

        public:
            void setMaterial(spark::material::ISparkMaterial* material);

        private:
            std::vector<ISparkSceneNode*> m_children;
            spark::math::Vector3f m_position;
            spark::math::Vector3f m_rotation;
            spark::mesh::ISparkMesh* m_mesh;
            spark::math::Matrix4f m_modelTransformationMatrix;
            spark::animator::ISparkNodeAnimator* m_nodeAnimator;
            spark::material::ISparkMaterial* m_material;
        };
    }
}
#endif