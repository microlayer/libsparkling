#include "FontPool.hpp"

namespace spark::font {
    /**
    *
    */
    FontPool::FontPool() :
        m_font(NULL)
    {
        m_fonts[spark::font::E_SYSTEM_FONT_TYPE::ESFT_ARIAL_16] =
            new spark::font::Font(spark::font::E_SYSTEM_FONT_TYPE::ESFT_ARIAL_16);

        m_fonts[spark::font::E_SYSTEM_FONT_TYPE::ESFT_ARIAL_8] =
            new spark::font::Font(spark::font::E_SYSTEM_FONT_TYPE::ESFT_ARIAL_8);
    }

    /**
    *
    */
    FontPool::~FontPool()
    {
        for (auto& it : m_fonts)
        {
            if (it.second != nullptr)
            {
                it.second->release();
            }
        }

        m_fonts.clear();
    }

    /**
    *
    */
    spark::font::ISparkFont* FontPool::getFont(spark::font::E_SYSTEM_FONT_TYPE fontType)
    {
        auto it = m_fonts.find(fontType);

        if (it != m_fonts.end())
            return it->second;
        return NULL;
    }
}
