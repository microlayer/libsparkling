#include "Font.hpp"

namespace spark::font {
    /**
    *
    */
    Font::Font()
    {

    }

    /**
    *
    */
    Font::~Font()
    {
        if (m_texture != NULL) m_texture->release();
    }

    /**
    *
    */
    spark::font::BitmapFontInfo Font::getBitmapFontInfo(uint16_t size) const
    {
        return spark::font::embedded::font_Arial_16::BitmapFont;
    }

    /**
    *
    */
    uc8_t* Font::getFontMap() const
    {
        return spark::font::embedded::font_Arial_16::Image;
    }

    /**
    *
    */
    std::string Font::getFontName() const
    {
        return "Arial_16";
    }

    /**
    *
    */
    void Font::setTexture(spark::renderer::ISparkTexture* texture)
    {

        m_texture = texture;
    }
}
