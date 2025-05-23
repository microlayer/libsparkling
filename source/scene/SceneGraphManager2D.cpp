#include "scene/SceneGraphManager2D.hpp"

namespace spark {
    namespace scene {
        /**
        *
        */
        SceneGraphManager2D::SceneGraphManager2D(spark::renderer::ISparkRenderer* renderer)
        {
            b2Vec2 gravity(0.0f, -10.0f);
            m_b2World = new b2World(gravity);

            m_timer = new spark::timer::Timer();
            m_startTime = 0;
            m_timeStep = 1 / 60.0f;		// 60 Hz
            m_framePeriod = 17;			// 1/60 Hz * 1000
            m_velocityIterations = 3;
            m_positionIterations = 2;
        }

        /**
        *
        */
        SceneGraphManager2D::~SceneGraphManager2D()
        {
            if (m_b2World != NULL) delete m_b2World;
            if (m_timer != NULL) delete m_timer;
        }

        /**
        *
        */
        spark::game::Sprite* SceneGraphManager2D::addSprite(spark::drawing::ISparkImage* image)
        {
            b2BodyDef spriteBodyDef;
            spriteBodyDef.type = b2_dynamicBody;

            b2PolygonShape spriteShapeDef;
            spriteShapeDef.SetAsBox(((image->getWidth() / PTM_RATIO) / 4.0f), ((image->getHeight() / PTM_RATIO) / 4.0f));

            b2FixtureDef spriteFixtureDef;
            spriteFixtureDef.shape = &spriteShapeDef;
            spriteFixtureDef.density = 1.0f;
            spriteFixtureDef.friction = 0.9f;
            spriteFixtureDef.restitution = 0.65f;

            b2Body* body = m_b2World->CreateBody(&spriteBodyDef);

            auto sprite = std::make_unique<spark::game::Sprite>(image);
            spark::game::Sprite* ptr = sprite.get();
            m_sprites.push_back(std::move(sprite));
            return ptr;
        }

        /**
        *
        */
        spark::game::LineLayer* SceneGraphManager2D::addLineLayer(int16_t x1, int16_t y1, int16_t x2, int16_t y2, spark::drawing::Color color)
        {
            return NULL;
        }

        /**
        *
        */
        void SceneGraphManager2D::drawGraph(spark::renderer::ISparkRenderer* renderer)
        {
            uint32_t currentTimeInMilliseconds = m_timer->getTimestamp();
            int32_t stepTime = currentTimeInMilliseconds - m_startTime;

            for (const auto& sprite : m_sprites)
            {
                sprite->paint(renderer);
            }

            if ((currentTimeInMilliseconds - m_startTime) > m_framePeriod)
            {
                m_startTime = currentTimeInMilliseconds;
                m_b2World->Step(m_timeStep, m_velocityIterations, m_positionIterations);
            }
        }
    }
}