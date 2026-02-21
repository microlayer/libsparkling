#ifndef __SPARK_FONTPOOL_FONT_HPP
#define __SPARK_FONTPOOL_FONT_HPP

#include "ISparkFont.hpp"
#include "fonts/Font.hpp"
#include "ISparkFontPool.hpp"

namespace spark::font {
    /**
    *
    */
    class FontPool : public ISparkFontPool
    {
    public:
        FontPool();
        ~FontPool();

    public:
        spark::font::ISparkFont* getFont();

    private:
        spark::font::ISparkFont* m_font;
    };
}
#endif