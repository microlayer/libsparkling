#include "Font.hpp"
#include "embedded/Arial8.hpp"

namespace spark::font {
    /**
    *
    */
    Font::Font(spark::font::E_SYSTEM_FONT_TYPE fontType) : m_fontType(fontType), m_texture(NULL)
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
    spark::font::BitmapFontInfo Font::getBitmapFontInfo() const
    {
        if (m_fontType == spark::font::E_SYSTEM_FONT_TYPE::ESFT_ARIAL_16)
            return spark::font::embedded::font_Arial_16::BitmapFont;

        if (m_fontType == spark::font::E_SYSTEM_FONT_TYPE::ESFT_ARIAL_8)
            return spark::font::embedded::font_Arial_8::BitmapFont;

        return spark::font::embedded::font_Arial_16::BitmapFont;
    }

    /**
    *
    */
    uc8_t* Font::getFontMap() const
    {
        if (m_fontType == spark::font::E_SYSTEM_FONT_TYPE::ESFT_ARIAL_16)
            return spark::font::embedded::font_Arial_16::Image;

        if (m_fontType == spark::font::E_SYSTEM_FONT_TYPE::ESFT_ARIAL_8)
            return spark::font::embedded::font_Arial_8::Image;

        return spark::font::embedded::font_Arial_16::Image;
    }

    /**
    *
    */
    std::string Font::getFontName() const
    {
        if (m_fontType == spark::font::E_SYSTEM_FONT_TYPE::ESFT_ARIAL_16)
            return "Arial_16";

        if (m_fontType == spark::font::E_SYSTEM_FONT_TYPE::ESFT_ARIAL_8)
            return "Arial_8";

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
