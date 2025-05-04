#include "Font.hpp"

namespace spark {
    namespace font {
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
    }
}
