#include "AbstractLayer.hpp"

namespace spark {
    namespace game {

        /**
        *
        */
        AbstractLayer::AbstractLayer(b2Body* body) :
            m_x(0),
            m_y(0),
            m_zAxisRotation(0),
            m_b2Body(body)
        {

        }

        /**
        *
        */
        AbstractLayer::~AbstractLayer()
        {

        }

        /**
        *
        */
        void AbstractLayer::setPosition(int16_t x, int16_t y)
        {
            m_x = x;
            m_y = y;

            if (m_b2Body != NULL)
            {
                m_b2Body->SetTransform(b2Vec2((m_x / PTM_RATIO), (-m_y / PTM_RATIO)), m_zAxisRotation);
            }
        }

        /**
        *
        */
        void AbstractLayer::setRotation(real32 zAxisRotation)
        {
            m_zAxisRotation = zAxisRotation;

            if (m_b2Body != NULL)
            {
                m_b2Body->SetTransform(m_b2Body->GetPosition(), m_zAxisRotation);
            }
        }

        /**
        *
        */
        real32 AbstractLayer::getRotation()
        {
            return m_zAxisRotation;
        }

        /**
        *
        */
        void AbstractLayer::move(int16_t dx, int16_t dy)
        {

        }
    }
}
