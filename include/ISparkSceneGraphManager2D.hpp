#ifndef __SPARK_SCENE_ISPARKSCENEGRAPHMANAGER2D_HPP_INCLUDED__
#define __SPARK_SCENE_ISPARKSCENEGRAPHMANAGER2D_HPP_INCLUDED__

#include "ISparkImage.hpp"
#include "ISparkSprite.hpp"
#include "ISparkLineLayer.hpp"

namespace spark {
    namespace game {
        class Sprite;
        class LineLayer;
    }
}

namespace spark {
    namespace scene {
        /**
        *
        */
        class ISceneGraphManager2D : public virtual spark::SparkRefCount
        {
        public:
            virtual spark::game::ISparkSprite* createSprite(spark::drawing::ISparkImage* image) = 0;
            virtual spark::game::ISparkLineLayer* createLineLayer(int16_t x1, int16_t y1, int16_t x2, int16_t y2, spark::drawing::Color color) = 0;
            virtual void drawGraph(spark::renderer::ISparkRenderer* renderer) = 0;
        };
    }
}
#endif