#include "TiledLayer.hpp"

namespace spark::game {
    /**
    *
    */
    TiledLayer::TiledLayer(spark::drawing::ISparkImage* tilesetImage, uint16_t layerColumns, uint16_t layerRows, uint16_t* gidData, uint16_t tileWidth, uint16_t tileHeight, uint16_t tilesetImageWidth, uint16_t tilesetImageHeight, E_LAYER_TYPE layerType) :
        AbstractLayer(NULL),
        m_tilesetImage(tilesetImage),
        m_layerColumns(layerColumns),
        m_layerRows(layerRows),
        m_gidData(NULL),
        m_tileWidth(tileWidth),
        m_tileHeight(tileHeight),
        m_tilesetImageWidth(tilesetImage->getWidth()),
        m_tilesetImageHeight(tilesetImage->getHeight()),
        m_layerType(layerType)
    {
        m_tilesetImage->addRef();

        if (gidData != NULL)
        {
            m_gidData = new uint16_t[layerColumns * layerRows];
            memcpy(m_gidData, gidData, layerColumns * layerRows * sizeof(uint16_t));
        }
    }

    /**
    *
    */
    TiledLayer::~TiledLayer(void)
    {
        if (m_tilesetImage != NULL)
        {
            delete m_tilesetImage;
        }
        delete[] m_gidData;
    }

    /**
    *
    */
    void TiledLayer::setPosition(int16_t x, int16_t y)
    {
        AbstractLayer::setPosition(x, y);
    }

    /**
    *
    */
    void TiledLayer::setRotation(real32 zAxisRotation)
    {
        AbstractLayer::setRotation(zAxisRotation);
    }

    /**
    *
    */
    real32 TiledLayer::getRotation()
    {
        return AbstractLayer::getRotation();
    }

    /**
    *
    */
    void TiledLayer::move(int16_t dx, int16_t dy)
    {
        AbstractLayer::move(dx, dy);
    }

    /**
    *
    */
    void TiledLayer::paint(spark::renderer::ISparkRenderer* renderer)
    {
        renderer->drawTiledLayer(this, this->m_x, this->m_y);
    }

    /**
    *
    */
    spark::drawing::ISparkImage* TiledLayer::getTilesetImage() const
    {
        return m_tilesetImage;
    }

    /**
    *
    */
    uint16_t* TiledLayer::getGIDData() const
    {
        return m_gidData;
    }

    /**
    *
    */
    uint16_t TiledLayer::getLayerRows() const
    {
        return m_layerRows;
    }

    /**
    *
    */
    uint16_t TiledLayer::getLayerColumns() const
    {
        return m_layerColumns;
    }

    /**
    *
    */
    uint16_t TiledLayer::getTileWidth() const
    {
        return m_tileWidth;
    }

    /**
    *
    */
    uint16_t TiledLayer::getTileHeight() const
    {
        return m_tileHeight;
    }

    /**
    *
    */
    uint32_t TiledLayer::getTilesetImageWidth() const
    {
        return m_tilesetImage->getWidth();
    }

    /**
    *
    */
    uint32_t TiledLayer::getTilesetImageHeight() const
    {
        return m_tilesetImage->getHeight();
    }

    /**
    *
    */
    spark::game::E_LAYER_TYPE TiledLayer::getLayerType() const
    {
        return m_layerType;
    }
}

