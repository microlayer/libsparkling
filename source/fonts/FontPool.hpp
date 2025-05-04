#ifndef __SPARK_FONTPOOL_FONT_HPP
#define __SPARK_FONTPOOL_FONT_HPP

#include "ISparkFont.hpp"
#include "fonts/Font.hpp"
#include "ISparkFontPool.hpp"

namespace spark {
    namespace font {
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

    } // end namespace font
} // end namespace spark
#endif