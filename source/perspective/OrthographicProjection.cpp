#include "OrthographicProjection.hpp"

namespace spark {
    namespace perspective {

        /**
        *
        */
        OrthographicProjection::OrthographicProjection(uint16_t screenWidth, uint16_t screenHeight)
        {
            m_virtualResolution = new spark::perspective::VirtualResolution(screenWidth, screenHeight);
        }

        /**
        *
        */
        OrthographicProjection::~OrthographicProjection(void)
        {
            if (m_virtualResolution != NULL)
            {
                delete m_virtualResolution;
                m_virtualResolution = NULL;
            }
        }

        /**
        *
        */
        void OrthographicProjection::pan()
        {
        }

        /**
        *
        */
        void OrthographicProjection::zoom()
        {
        }

        /**
        *
        */
        void OrthographicProjection::rotate()
        {
        }

        /**
        * Viewport is full size if no custom viewport is set
        */
        spark::perspective::Viewport OrthographicProjection::getViewport()
        {
            return m_virtualResolution->getViewport();
        }

        /**
        *
        */
        spark::perspective::ViewportTransformationParameter OrthographicProjection::getViewportTransformationParameter()
        {
            return m_virtualResolution->getViewportTransformationParameter();
        }

        /**
        *
        */
        void OrthographicProjection::setVirtualResolution(uint16_t virtualWidth, uint16_t virtualHeight, spark::perspective::VirtualResolution::E_VIRTUAL_RESOLUTION_TYPE virtualResolutionType)
        {
            m_virtualResolution->setVirtualResolution(virtualWidth, virtualHeight, virtualResolutionType);
        }

        /**
        *
        */
        spark::perspective::VirtualResolution* OrthographicProjection::getVirtualResolution()
        {
            return m_virtualResolution;
        }

        /**
        *
        */
        spark::perspective::VirtualResolution::E_VIRTUAL_RESOLUTION_TYPE OrthographicProjection::getVirtualResolutionType()
        {
            return m_virtualResolution->getVirtualResolutionType();
        }
    } // end namespace perspective
} // end namespace spark