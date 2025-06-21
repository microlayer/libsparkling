#ifndef __SPARK_SCENE_SCENEGRAPHMANAGER2D_HPP_INCLUDED__
#define __SPARK_SCENE_SCENEGRAPHMANAGER2D_HPP_INCLUDED__

#include "ISparkRenderer.hpp"
#include "ISceneGraphManager2D.hpp"
#include "game/Sprite.hpp"
#include "game/LineLayer.hpp"

namespace spark {
    namespace scene {
        /**
        *
        */
        class SceneGraphManager2D : public ISceneGraphManager2D
        {
        public:
            SceneGraphManager2D(spark::renderer::ISparkRenderer* renderer, spark::log::ISparkLogger* logger);
            ~SceneGraphManager2D();

        public:
            spark::game::ISparkSprite* createSprite(spark::drawing::ISparkImage* image);
            spark::game::ISparkLineLayer* createLineLayer(int16_t x1, int16_t y1, int16_t x2, int16_t y2, spark::drawing::Color color);
            void drawGraph(spark::renderer::ISparkRenderer* renderer);

        private:
            b2World m_b2World;
            std::vector<std::unique_ptr<spark::game::AbstractLayer>> m_worldElements;
            spark::timer::ISparkTimer* m_timer;
            uint32_t m_startTime;
            uint32_t m_framePeriod;
            uint16_t m_velocityIterations;
            uint16_t m_positionIterations;
            real32 m_timeStep;
            spark::log::ISparkLogger* m_logger;
            spark::renderer::ISparkRenderer* m_renderer;
        };
    }
}
#endif