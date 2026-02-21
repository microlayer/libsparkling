#ifndef __SPARK_PERSPECTIVE_ORTHOGRAPHICPROJECTION_HPP_INCLUDED__
#define __SPARK_PERSPECTIVE_ORTHOGRAPHICPROJECTION_HPP_INCLUDED__

#include "perspective/VirtualResolution.hpp"

namespace spark::perspective {
    /**
    *
    */
    class OrthographicProjection
    {
    public:
        OrthographicProjection(uint16_t screenWidth, uint16_t screenHeight);
        virtual ~OrthographicProjection(void);

    public:
        void pan();
        void zoom();
        void rotate();

    public:
        spark::perspective::Viewport getViewport();
        spark::perspective::ViewportTransformationParameter getViewportTransformationParameter();
        void setVirtualResolution(uint16_t virtualWidth, uint16_t virtualHeight, spark::perspective::VirtualResolution::E_VIRTUAL_RESOLUTION_TYPE virtualResolutionType);
        spark::perspective::VirtualResolution* getVirtualResolution();
        spark::perspective::VirtualResolution::E_VIRTUAL_RESOLUTION_TYPE getVirtualResolutionType();

    private:
        spark::perspective::VirtualResolution* m_virtualResolution;
    };
}
#endif
