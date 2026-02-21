#ifndef __SPARK_PERSPECTIVE_VIRTUALRESOLUTION_HPP_INCLUDED__
#define __SPARK_PERSPECTIVE_VIRTUALRESOLUTION_HPP_INCLUDED__

#include "spark/SparkTypes.hpp"
#include "perspective/Viewport.hpp"

namespace spark::perspective {
    /**
    * Holds the virtual display information
    */
    struct VirtualScreenResolution
    {
        uint16_t m_virtualWidth;
        uint16_t m_virtualHeight;
        real32 m_ratio;
    };

    /**
     * Holds scale factor for width and height used for the orthographic perspective and the ratio used for the perspective projection.
     */
    struct ViewportTransformationParameter
    {
    public:
        /**
        *
        */
        ViewportTransformationParameter()
        {
        }

        /**
        *
        */
        ViewportTransformationParameter(real32 scaleWidth, real32 scaleHeight, real32 ratio) : m_scaleWidth(scaleWidth), m_scaleHeight(scaleHeight), m_viewportRatio(ratio)
        {
        }

        real32 m_scaleWidth;
        real32 m_scaleHeight;
        real32 m_viewportRatio;
    };

    /**
    *
    */
    class VirtualResolution
    {
    public:
        /**
        * E_NONE:					Turns off dynamic content scaling.
        * E_LETTER_OR_PILLARBOX:	Scales content up as much as possible, while still showing all content on the screen.
        * E_ZOOM_EVEN:			    Uniformly scales up content to fill screen, while preserving aspect ratio.
        */
        enum E_VIRTUAL_RESOLUTION_TYPE
        {
            E_NONE = 0,
            E_LETTER_OR_PILLARBOX,
            E_ZOOM_EVEN
        };

    public:
        /**
        *
        */
        VirtualResolution(uint16_t screenWidth, uint16_t screenHeight)
        {
            m_screenWidth = screenWidth;
            m_screenHeight = screenHeight;

            setVirtualResolution(m_screenWidth, m_screenHeight, VirtualResolution::E_LETTER_OR_PILLARBOX);
        }

        /**
        *
        */
        virtual ~VirtualResolution(void)
        {
        }

    public:
        /**
        *
        */
        void setVirtualResolution(uint16_t virtualWidth, uint16_t virtualHeight, E_VIRTUAL_RESOLUTION_TYPE virtualResolutionType)
        {
            m_virtualScreenResolution.m_virtualWidth = virtualWidth;
            m_virtualScreenResolution.m_virtualHeight = virtualHeight;
            m_virtualScreenResolution.m_ratio = (virtualWidth * 1.0f / virtualHeight);
            m_virtualResolutionType = virtualResolutionType;

            // e.g.rounding float to nearest integer
            // (int)(330 / 1.3f) = 253.846 + 0.0f = > 253.846 = > (cast to int) = > 253 rounding not correct (should be 254)
            // (int)(330 / 1.3f) = 253.846 + 0.5f = > 254.346 = > (cast to int) = > 254 rounding correct
            if (VirtualResolution::E_NONE != virtualResolutionType)
            {
                // Find the max size of the viewport which matches the target aspect ratio => letterbox
                uint16_t vp_width = m_screenWidth;
                uint16_t vp_height = (uint16_t)(m_screenWidth / m_virtualScreenResolution.m_ratio + 0.5f);
                int16_t vp_x = 0;
                int16_t vp_y = 0;

                if (vp_height > m_screenHeight) // Viewport height is higher than the device's physical height
                {
                    // Find the max size of the viewport which matches the target aspect ratio => pillarbox 
                    vp_height = m_screenHeight;
                    vp_width = (uint16_t)(m_screenHeight * m_virtualScreenResolution.m_ratio + 0.5f);
                }

                if (VirtualResolution::E_LETTER_OR_PILLARBOX == virtualResolutionType)
                {
                    // Calculate the viewport
                    vp_x = (m_screenWidth / 2) - (vp_width / 2);
                    vp_y = (m_screenHeight / 2) - (vp_height / 2);
                }
                else if (VirtualResolution::E_ZOOM_EVEN == virtualResolutionType)
                {
                    // oversize width
                    vp_width = m_screenWidth;
                    vp_height = (uint16_t)(m_screenWidth / m_virtualScreenResolution.m_ratio + 0.5f);

                    if (vp_height < m_screenHeight)
                    {
                        vp_height = m_screenHeight;
                        vp_width = (uint16_t)(m_screenHeight * m_virtualScreenResolution.m_ratio + 0.5f);
                    }

                    // Calculate the viewport
                    vp_x = (m_screenWidth / 2) - (vp_width / 2);
                    vp_y = (m_screenHeight / 2) - (vp_height / 2);
                }

                real32 scale_x = (real32)((real32)(m_screenWidth) / (real32)m_virtualScreenResolution.m_virtualWidth);
                real32 scale_y = (real32)((real32)(m_screenHeight) / (real32)m_virtualScreenResolution.m_virtualHeight);

                m_viewport = spark::perspective::Viewport(vp_x, vp_y, vp_width, vp_height);
                m_viewportTransformationParameter = ViewportTransformationParameter(scale_x, scale_y, vp_width * 1.0f / vp_height);
            }
            else
            {
                m_viewport = spark::perspective::Viewport(0, 0, m_screenWidth, m_screenHeight);
            }
        }

        /**
        *
        */
        const E_VIRTUAL_RESOLUTION_TYPE getVirtualResolutionType() const
        {
            return m_virtualResolutionType;
        }

        /**
        *
        */
        const VirtualScreenResolution getVirtualScreenResolution() const
        {
            return m_virtualScreenResolution;
        }

        /**
        *
        */
        const spark::perspective::Viewport getViewport() const
        {
            return m_viewport;
        }

        /**
        *
        */
        const ViewportTransformationParameter getViewportTransformationParameter() const
        {
            return m_viewportTransformationParameter;
        }

    private:
        E_VIRTUAL_RESOLUTION_TYPE m_virtualResolutionType;
        spark::perspective::Viewport m_viewport;
        ViewportTransformationParameter m_viewportTransformationParameter;
        VirtualScreenResolution m_virtualScreenResolution;
        uint16_t m_screenWidth;
        uint16_t m_screenHeight;
    };
}
#endif