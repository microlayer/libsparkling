#ifndef __SPARK_GAME_TILEDLAYER_HPP_INCLUDED__
#define __SPARK_GAME_TILEDLAYER_HPP_INCLUDED__

#include "AbstractLayer.hpp"
#include "ISparkTiledLayer.hpp"

namespace spark {
    namespace game {
        /**
        *
        */
        enum E_LAYER_TYPE
        {
            ELT_ORTHOGONAL = 0,
            ELT_ISOMETRIC,
            ELT_HEXAGONAL
        };
        /**
        *
        */
        class TiledLayer : public spark::game::AbstractLayer, public spark::game::ISparkTiledLayer
        {
        public:
            TiledLayer(spark::drawing::ISparkImage* tilesetImage, uint16_t layerColumns, uint16_t layerRows, uint16_t* gidData, uint16_t tileWidth, uint16_t tileHeight, uint16_t tilesetImageWidth, uint16_t tilesetImageHeight, E_LAYER_TYPE layerType);
            virtual ~TiledLayer(void);

        public: // AbstractLayer
            void setPosition(int16_t x, int16_t y);
            void setRotation(real32 zAxisRotation);
            real32 getRotation();
            void move(int16_t dx, int16_t dy);

        public: // AbstractLayer
            void paint(spark::renderer::ISparkRenderer* renderer);

        public:
            spark::drawing::ISparkImage* getTilesetImage() const;
            uint16_t* getGIDData() const;
            uint16_t getLayerRows() const;
            uint16_t getLayerColumns() const;
            uint16_t getTileWidth() const;
            uint16_t getTileHeight() const;
            uint32_t getTilesetImageWidth() const;
            uint32_t getTilesetImageHeight() const;
            spark::game::E_LAYER_TYPE getLayerType() const;

        private:
            spark::drawing::ISparkImage* m_tilesetImage;
            uint16_t m_layerColumns;
            uint16_t m_layerRows;
            uint16_t* m_gidData;
            uint16_t m_tileWidth;
            uint16_t m_tileHeight;
            uint16_t m_tilesetImageWidth;
            uint16_t m_tilesetImageHeight;
            E_LAYER_TYPE m_layerType;
        };
    } // end namespace game
} // end namespace spark
#endif

