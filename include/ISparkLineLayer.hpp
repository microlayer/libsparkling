#ifndef __SPARK_GAME_ISPARKLINELAYER_HPP_INCLUDED__
#define __SPARK_GAME_ISPARKLINELAYER_HPP_INCLUDED__

#include "SparkRefCount.hpp"

namespace spark {
    namespace game {
        /**
        *
        */
        class ISparkLineLayer : public virtual SparkRefCount
        {
        public: // AbstractLayer                        
            virtual void setPosition(int16_t x, int16_t y) = 0;
            virtual void setRotation(real32 zAxisRotation) = 0;
            virtual void paint(spark::renderer::ISparkRenderer* renderer) = 0;
        };
    }
}
#endif