#include "FontPool.hpp"

namespace spark {
    namespace font {
        /**
        *
        */
        FontPool::FontPool() :
            m_font(NULL)
        {
            m_font = new spark::font::Font();
        }

        /**
        *
        */
        FontPool::~FontPool()
        {
            if (m_font != NULL)
            {
                m_font->release();
            }
        }

        /**
        *
        */
        spark::font::ISparkFont* FontPool::getFont()
        {
            return m_font;
        }
    }
}
