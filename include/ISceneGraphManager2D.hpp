#ifndef __SPARK_SCENE_ISCENEGRAPHMANAGER2D_HPP_INCLUDED__
#define __SPARK_SCENE_ISCENEGRAPHMANAGER2D_HPP_INCLUDED__

#include "ISparkRenderer.hpp"
#include "scene/SceneNode.hpp"
#include "game/Sprite.hpp"
#include "game/LineLayer.hpp"

namespace spark {
    namespace scene {
        /**
        *
        */
        class ISceneGraphManager2D : public virtual spark::SparkRefCount
        {
        public:
            virtual spark::game::Sprite* addSprite(spark::drawing::ISparkImage* image) = 0;
            virtual spark::game::LineLayer* addLineLayer(int16_t x1, int16_t y1, int16_t x2, int16_t y2, spark::drawing::Color color) = 0;
            virtual void drawGraph(spark::renderer::ISparkRenderer* renderer) = 0;
        };
    }
}
#endif