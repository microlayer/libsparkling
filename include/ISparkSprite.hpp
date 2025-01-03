#ifndef __SPARK_GAME_ISPARKSPRITE_HPP_INCLUDED__
#define __SPARK_GAME_ISPARKSPRITE_HPP_INCLUDED__

#include "SparkRefCount.hpp"

namespace spark {
    namespace game {
        /**
        *
        */
        class ISparkSprite : public virtual SparkRefCount
        {
        public: // AbstractLayer
            virtual void setPosition(int16_t x, int16_t y) = 0;
            virtual void setRotation(real32 zAxisRotation) = 0;
            virtual real32 getRotation() = 0;
            virtual void move(int16_t dx, int16_t dy) = 0;
            virtual void paint(spark::renderer::ISparkRenderer* renderer) = 0;

        public:
            virtual void startAnimation() = 0;
            virtual void stopAnimation() = 0;
            virtual void setAnimationDetails(uint16_t delayTime, uint16_t frameWidth, uint16_t frameHeight) = 0;
        };
    }
}

#endif