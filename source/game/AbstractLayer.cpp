#include "AbstractLayer.hpp"

namespace spark {
    namespace game {
        /**
        *
        */
        AbstractLayer::AbstractLayer(b2Body* body) :
            m_x(0),
            m_y(0),
            m_zAxisRotation(0)
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

        }

        /**
        *
        */
        void AbstractLayer::setRotation(real32 zAxisRotation)
        {

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
