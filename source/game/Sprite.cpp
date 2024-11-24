#include "Sprite.hpp"

namespace spark {
    namespace game {

        /**
        *
        */
        Sprite::Sprite(spark::renderer::ISparkTexture* texture, b2Body* body) :
            AbstractLayer(body),
            m_texture(texture)
        {

        }

        /**
        *
        */
        Sprite::~Sprite()
        {

        }

        /**
        *
        */
        void Sprite::paint(spark::renderer::ISparkRenderer* renderer)
        {

        }

        /**
        *
        */
        spark::drawing::ISparkImage* Sprite::getSpriteImage()
        {
            return NULL;
        }

        /**
        *
        */
        void Sprite::setStaticBodyType(bool flag)
        {

        }

        /**
        *
        */
        void Sprite::startAnimation()
        {

        }

        /**
        *
        */
        void Sprite::stopAnimation()
        {

        }

        /**
        *
        */
        void Sprite::setAnimationDetails(uint16_t delayTime, uint16_t frameWidth, uint16_t frameHeight)
        {

        }
    }
}