#ifndef __SPARK_GAME_TILEDLAYER_HPP_INCLUDED__
#define __SPARK_GAME_TILEDLAYER_HPP_INCLUDED__

#include "AbstractLayer.hpp"

namespace spark {
    namespace game {

        /**
        *
        */
        class TiledLayer : public spark::game::AbstractLayer
        {
        public:
            enum E_LAYER_TYPE
            {
                ELT_ORTHOGONAL = 0,
                ELT_ISOMETRIC,
                ELT_HEXAGONAL
            };

        public:
            TiledLayer(spark::drawing::ISparkImage* tilesetImage, uint16_t layerColumns, uint16_t layerRows, uint16_t* gidData, uint16_t tileWidth, uint16_t tileHeight, uint16_t tilesetImageTileWidth, uint16_t tilesetImageTileHeight, E_LAYER_TYPE layerType);
            virtual ~TiledLayer(void);

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
            uint32_t getTilesetImageTileWidth() const;
            uint32_t getTilesetImageTileHeight() const;
            E_LAYER_TYPE getLayerType() const;

        private:
            spark::drawing::ISparkImage* m_tilesetImage;
            uint16_t m_layerColumns;
            uint16_t m_layerRows;
            uint16_t* m_gidData;
            uint16_t m_tileWidth;
            uint16_t m_tileHeight;
            uint16_t m_tilesetImageWidth;
            uint16_t m_tilesetImageHeight;
            uint16_t m_tilesetImageTileWidth;
            uint16_t m_tilesetImageTileHeight;
            E_LAYER_TYPE m_layerType;
        };
    } // end namespace game
} // end namespace spark
#endif

