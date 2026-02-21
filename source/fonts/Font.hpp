#ifndef __SPARK_FONT_FONT_HPP
#define __SPARK_FONT_FONT_HPP

#include "ISparkFont.hpp"
#include "embedded/Arial16.hpp"
#include <string>

namespace spark::font {
    /**
    *
    */
    class Font : public ISparkFont
    {
    public:
        Font();
        ~Font();
    public:
        spark::font::BitmapFontInfo getBitmapFontInfo(uint16_t size) const;
        uc8_t* getFontMap() const;
        std::string getFontName() const;
        void setTexture(spark::renderer::ISparkTexture* texture);

    private:
        spark::renderer::ISparkTexture* m_texture;
    };
}
#endif