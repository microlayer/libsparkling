#ifndef __SPARK_FONTPOOL_FONT_HPP
#define __SPARK_FONTPOOL_FONT_HPP

#include "ISparkFont.hpp"
#include "fonts/Font.hpp"
#include "ISparkFontPool.hpp"
#include <unordered_map>

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
        spark::font::ISparkFont* getFont(spark::font::E_SYSTEM_FONT_TYPE fontType);

    private:
        std::unordered_map<spark::font::E_SYSTEM_FONT_TYPE, spark::font::ISparkFont*> m_fonts;
        spark::font::ISparkFont* m_font;
    };
}
#endif