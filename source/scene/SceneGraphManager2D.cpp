#include "scene/SceneGraphManager2D.hpp"

namespace spark {
    namespace scene {
        /**
        *
        */
        SceneGraphManager2D::SceneGraphManager2D()
        {
            b2Vec2 gravity(0.0f, -10.0f);
            //m_b2World = new b2World(gravity);
        }
        
        /**
        *
        */
        SceneGraphManager2D::~SceneGraphManager2D()
        {

        }

        /**
        *
        */
        spark::game::Sprite* SceneGraphManager2D::addSprite(spark::drawing::ISparkImage* image)
        {
            return NULL;
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

        }
    }
}