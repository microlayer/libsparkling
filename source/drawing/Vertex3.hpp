#ifndef __SPARK_DRAWING_VERTEX3_HPP_INCLUDED__
#define __SPARK_DRAWING_VERTEX3_HPP_INCLUDED__

#include "drawing/Color.hpp"
#include "math/Vector2.hpp"
#include "math/Vector3.hpp"

namespace spark::drawing {
    /**
    *
    */
    struct Vertex3
    {
        /**
        * Initializes a white vertex - Position, Normal, TextureCoord is set to 0
        */
        Vertex3() : m_x(0.0f), m_y(0.0f), m_z(0.0f),
            m_color(255, 255, 255, 255)
        {
            m_textureCoord = math::Vector2f(0.0f, 0.0f);
            m_normal = math::Vector3f(0.0f, 0.0f, 0.0f);
            m_position = math::Vector3f(0.0f, 0.0f, 0.0f);
        }

        /**
        * Initializes a white vertex at the specified position - Normal, TextureCoord is set to 0
        */
        Vertex3(real32 x, real32 y, real32 z) : m_x(x), m_y(y), m_z(z),
            m_color(255, 255, 255, 255)
        {
            m_textureCoord = math::Vector2f(0.0f, 0.0f);
            m_normal = math::Vector3f(0.0f, 0.0f, 0.0f);
            m_position = math::Vector3f(x, y, z);
        }

        /**
        * Initializes a vertex at the specified position and textureCoord - Color, Normal, is set to 0
        */
        Vertex3(real32 x, real32 y, real32 z, math::Vector2f textureCoord) : m_x(x), m_y(y), m_z(z),
            m_textureCoord(textureCoord)
        {
            m_color = spark::drawing::Color(255, 255, 255, 255);
            m_normal = math::Vector3f(0.0f, 0.0f, 0.0f);
            m_position = math::Vector3f(x, y, z);
        }

        /**
        * Initializes a vertex at the specified position and color - Normal, TextureCoord is set to 0
        */
        Vertex3(real32 x, real32 y, real32 z, drawing::Color color) : m_x(x), m_y(y), m_z(z),
            m_color(color)
        {
            m_textureCoord = math::Vector2f(0.0f, 0.0f);
            m_normal = math::Vector3f(0.0f, 0.0f, 0.0f);
            m_position = math::Vector3f(x, y, z);
        }

        /**
        * Initializes a vertex at the specified position, color and normal - TextureCoord is set to 0
        */
        Vertex3(real32 x, real32 y, real32 z, drawing::Color color, math::Vector3f normal) : m_x(x), m_y(y), m_z(z),
            m_color(color),
            m_normal(normal)
        {
            m_textureCoord = math::Vector2f(0.0f, 0.0f);
            m_position = math::Vector3f(x, y, z);
        }

        /**
        * Initializes a vertex at the specified position, color, normal and textureCoord
        */
        Vertex3(real32 x, real32 y, real32 z, drawing::Color color, math::Vector3f normal, math::Vector2f textureCoord) : m_x(x), m_y(y), m_z(z),
            m_color(color),
            m_normal(normal),
            m_textureCoord(textureCoord)
        {
            m_position = math::Vector3f(x, y, z);
        }

    public:
        // Do not change this order - This guarantees the correct memory layout 
        real32 m_x;
        real32 m_y;
        real32 m_z;
        spark::drawing::Color m_color;
        math::Vector3f m_normal;
        math::Vector2f m_textureCoord;
        math::Vector3f m_position;
    };
}
#endif