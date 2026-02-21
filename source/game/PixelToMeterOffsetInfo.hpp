#ifndef __SPARK_GAME_PIXELTOMETEROFFSETINFO_HPP_INCLUDED__
#define __SPARK_GAME_PIXELTOMETEROFFSETINFO_HPP_INCLUDED__

namespace spark::game {
    /**
    *
    */
    struct PixelToMeterOffsetInfo
    {
        /**
        *
        */
        PixelToMeterOffsetInfo()
        {


        }

        /**
        *
        */
        PixelToMeterOffsetInfo(const PixelToMeterOffsetInfo* pixelToMeterOffsetInfo)
        {
            m_xOffsetPixel = pixelToMeterOffsetInfo->m_xOffsetPixel;
            m_yOffsetPixel = pixelToMeterOffsetInfo->m_yOffsetPixel;
            m_xOffsetMeter = pixelToMeterOffsetInfo->m_xOffsetMeter;
            m_yOffsetMeter = pixelToMeterOffsetInfo->m_yOffsetMeter;
        }

        int32_t m_xOffsetPixel;
        int32_t m_yOffsetPixel;
        real32 m_xOffsetMeter;
        real32 m_yOffsetMeter;
    };
}
#endif