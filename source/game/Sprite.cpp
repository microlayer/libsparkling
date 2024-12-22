#include "Sprite.hpp"

namespace spark {
    namespace game {
        /**
        *
        */
        Sprite::Sprite(spark::drawing::ISparkImage* image) :
            AbstractLayer(NULL),
            m_image(image),
            m_frameWidth(0),
            m_frameHeight(0),
            m_delayTime(0),
            m_currentFrame(0),
            m_startTime(0),
            m_ptmOffsetInfo(0),
            m_animationActivated(false)
        {

        }

        /**
        *
        */
        Sprite::Sprite(spark::drawing::ISparkImage* image, b2Body* body) :
            AbstractLayer(body),
            m_image(image),
            m_frameWidth(0),
            m_frameHeight(0),
            m_delayTime(0),
            m_currentFrame(0),
            m_startTime(0),
            m_ptmOffsetInfo(0),
            m_animationActivated(false)
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
            spark::drawing::ClippingRectangle clipRect;
            uint32_t currentTimeInMilliseconds = m_timer.getTimestamp();

            if (m_animationActivated)
            {
                clipRect.m_x = m_frameWidth * m_currentFrame;
                clipRect.m_y = 0;
                clipRect.m_width = m_frameWidth;
                clipRect.m_height = m_frameHeight;

                uint16_t frames = m_image->getWidth() / m_frameWidth;
                if ((currentTimeInMilliseconds - m_startTime) > m_delayTime)
                {
                    m_currentFrame = m_currentFrame % frames;
                    m_startTime = currentTimeInMilliseconds;
                    m_currentFrame++;
                }
            }
            else
            {
                clipRect.m_x = 0;
                clipRect.m_y = 0;
                clipRect.m_width = m_image->getWidth();
                clipRect.m_height = m_image->getHeight();
            }
            renderer->draw2DBitmap(m_image, m_x, m_y, clipRect);
        }

        /**
        *
        */
        spark::drawing::ISparkImage* Sprite::getSpriteImage()
        {
            return m_image;
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
            m_animationActivated = true;
        }

        /**
        *
        */
        void Sprite::stopAnimation()
        {
            m_animationActivated = false;
        }

        /**
        *
        */
        void Sprite::setAnimationDetails(uint16_t delayTime, uint16_t frameWidth, uint16_t frameHeight)
        {
            m_delayTime = delayTime;
            m_frameWidth = frameWidth;
            m_frameHeight = frameHeight;
        }
    }
}