#include "LineLayer.hpp"

namespace spark {
    namespace game {
        /**
        *
        */
        LineLayer::LineLayer(int16_t x1, int16_t y1, int16_t x2, int16_t y2, spark::drawing::Color color) :
            AbstractLayer(NULL),
            m_x1(x1),
            m_y1(y1),
            m_x2(x2),
            m_y2(y2),
            m_color(color)
        {

        }

        /**
        *
        */
        LineLayer::LineLayer(int16_t x1, int16_t y1, int16_t x2, int16_t y2, spark::drawing::Color color, b2Body* body) :
            AbstractLayer(body),
            m_x1(x1),
            m_y1(y1),
            m_x2(x2),
            m_y2(y2),
            m_color(color)
        {

        }

        /**
        *
        */
        LineLayer::~LineLayer()
        {

        }

        /**
        *
        */
        void LineLayer::setPosition(int16_t x, int16_t y)
        {
            spark::game::AbstractLayer::setPosition(x, y);
        }

        /**
        *
        */
        void LineLayer::setRotation(real32 zAxisRotation)
        {

        }

        /**
        *
        */
        void LineLayer::paint(spark::renderer::ISparkRenderer* renderer)
        {
            renderer->draw2DLine(m_x1, m_y1, m_x2, m_y2, m_color);
        }
    }
}