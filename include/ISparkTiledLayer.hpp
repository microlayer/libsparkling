#ifndef __SPARK_GAME_ISPARKTILEDLAYER_HPP_INCLUDED__
#define __SPARK_GAME_ISPARKTILEDLAYER_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include <game/TiledLayer.hpp>

namespace spark {
    namespace game {
        /**
        *
        */
        class ISparkTiledLayer : public virtual SparkRefCount
        {
        public: // AbstractLayer
            virtual void setPosition(int16_t x, int16_t y) = 0;
            virtual void setRotation(real32 zAxisRotation) = 0;
            virtual real32 getRotation() = 0;
            virtual void move(int16_t dx, int16_t dy) = 0;
            virtual void paint(spark::renderer::ISparkRenderer* renderer) = 0;

        public:
            virtual spark::drawing::ISparkImage* getTilesetImage() const = 0;
            virtual uint16_t* getGIDData() const = 0;
            virtual uint16_t getLayerRows() const = 0;
            virtual uint16_t getLayerColumns() const = 0;
            virtual uint16_t getTileWidth() const = 0;
            virtual uint16_t getTileHeight() const = 0;
            virtual uint32_t getTilesetImageWidth() const = 0;
            virtual uint32_t getTilesetImageHeight() const = 0;
            //virtual spark::game::E_LAYER_TYPE getLayerType() const = 0;
        };
    }
}
#endif