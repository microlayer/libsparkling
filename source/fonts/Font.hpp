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
        Font(spark::font::E_SYSTEM_FONT_TYPE fontType);
        ~Font();
    public:
        spark::font::BitmapFontInfo getBitmapFontInfo() const;
        uc8_t* getFontMap() const;
        std::string getFontName() const;
        void setTexture(spark::renderer::ISparkTexture* texture);

    private:
        spark::renderer::ISparkTexture* m_texture;
        spark::font::E_SYSTEM_FONT_TYPE m_fontType;
    };
}
#endif