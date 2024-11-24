#ifndef __SPARK_GAME_SPRITE_HPP_INCLUDED__
#define __SPARK_GAME_SPRITE_HPP_INCLUDED__

#include "AbstractLayer.hpp"
#include "ISparkTexture.hpp"
#include "ISparkLogger.hpp"
#include "PixelToMeterOffsetInfo.hpp"

namespace spark {
    namespace game {
        /**
        *
        */
        class Sprite : public spark::game::AbstractLayer
        {
        public:
            Sprite(spark::renderer::ISparkTexture* texture, b2Body* body);
            virtual ~Sprite(void);

        public: // AbstractLayer
            void paint(spark::renderer::ISparkRenderer* renderer);

        public:
            spark::drawing::ISparkImage* getSpriteImage();
            void setStaticBodyType(bool flag);
            void startAnimation();
            void stopAnimation();
            void setAnimationDetails(uint16_t delayTime, uint16_t frameWidth, uint16_t frameHeight);

        private:
            spark::renderer::ISparkTexture* m_texture;
            bool m_animationActivated;
            uint16_t m_delayTime;
            uint16_t m_frameWidth;
            uint16_t m_frameHeight;
            uint16_t m_currentFrame;
            uint32_t m_startTime;
            spark::log::ISparkLogger* m_logger;
            spark::game::PixelToMeterOffsetInfo* m_ptmOffsetInfo;
        };

    } // end namespace game
} // end namespace spark
#endif