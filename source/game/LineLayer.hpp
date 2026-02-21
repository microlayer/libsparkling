#ifndef __SPARK_GAME_LINELAYER_HPP_INCLUDED__
#define __SPARK_GAME_LINELAYER_HPP_INCLUDED__

#include "AbstractLayer.hpp"
#include "ISparkLineLayer.hpp"

namespace spark::game {
    /**
    *
    */
    class LineLayer : public spark::game::AbstractLayer, public spark::game::ISparkLineLayer
    {
    public:
        LineLayer(int16_t x1, int16_t y1, int16_t x2, int16_t y2, spark::drawing::Color color);
        LineLayer(int16_t x1, int16_t y1, int16_t x2, int16_t y2, spark::drawing::Color color, b2Body* body);
        ~LineLayer();

    public: // AbstractLayer
        void setPosition(int16_t x, int16_t y);
        void setRotation(real32 zAxisRotation);

    public: // AbstractLayer
        void paint(spark::renderer::ISparkRenderer* renderer);

    private:
        int16_t m_x1;
        int16_t m_y1;
        int16_t m_x2;
        int16_t m_y2;
        spark::drawing::Color m_color;
    };
}
#endif