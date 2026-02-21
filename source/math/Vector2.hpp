#ifndef __SPARK_MATH_VECTOR2_HPP_INCLUDED__
#define __SPARK_MATH_VECTOR2_HPP_INCLUDED__

#include "spark/SparkTypes.hpp"
#include "spark/SparkLibConfig.hpp"
#include <math.h>

namespace spark::math {
    /**
    *
    */
    template <class T> class Vector2
    {
    public:
        /**
        *
        */
        Vector2() :
            m_x(0), m_y(0)
        {
        }

        /**
        *
        */
        Vector2(T x, T y) :
            m_x(x), m_y(y)
        {
        }

        /**
        *
        */
        Vector2(const Vector2& v)
        {
            this->m_x = v.m_x;
            this->m_y = v.m_y;
        }

        /**
        *
        */
        Vector2<T> operator*(const T scalar) const
        {
            return Vector2<T>(m_x * scalar, m_y * scalar);
        }

        /**
        *
        */
        Vector2<T> operator/(const T scalar) const
        {
            return Vector2<T>(m_x / scalar, m_y / scalar);
        }

        /**
        *
        */
        Vector2<T> operator+(const Vector2<T>& vector) const
        {
            return Vector2<T>(m_x + vector.m_x, m_y + vector.m_y);
        }

        /**
        *
        */
        Vector2<T> operator-(const Vector2<T>& vector) const
        {
            return Vector2<T>(m_x - vector.m_x, m_y - vector.m_y);
        }

        /**
        *
        */
        Vector2<T> operator==(const Vector2<T>& vector) const
        {
            return equals(vector);
        }

        /**
        * @Brief Returns the normalized vector of this.
        */
        Vector2<T>& normalize()
        {
            real32 length = getLength();

            if (length == 0)
            {
                return *this;
            }

            length = 1.0f / sqrt(length);

            m_x = (T)(m_x * length);
            m_y = (T)(m_y * length);

            return *this;
        }

        /**
        * @Brief Returns the dot product of this and the given vector.
        */
        real32 getDotProduct(math::Vector2<T>& vector)
        {
            real32 dotProduct = 0.0f;
            dotProduct = (this->m_x * vector.m_x) + (this->m_y * vector.m_y);
            return dotProduct;
        }

        /**
        * @Brief Returns the angel between this and the given vector.
        */
        real32 GetAngelBetween(math::Vector2<T>& vector)
        {
            real32 pi = ML_PI;
            real32 rad = 0.0f;
            real32 grad = 0.0f;

            math::Vector2<T> self(*this);

            real32 denominator = this->getLength() * vector.getLength();
            if (denominator == 0)
            {
                grad = 0.0f;
            }
            else
            {
                rad = acos((self.getDotProduct(vector) / (denominator)));
                grad = (360.0 / (2.0f * pi)) * rad;
            }

            return grad;
        }

        /**
        * @Brief Returns the reflection vector between this and the given normal vector N as shown in this formula: a(e) = e - 2*(e dot N) * N
        */
        Vector2<T>& getReflection(math::Vector2<T>& n)
        {
            math::Vector2<T> e(*this);
            math::Vector2<T> a = n * (2 * e.getDotProduct(n)) - e;
            return a;
        }

        /**
        * @Brief Projects this vector (F) in the direction of s; Fs = ((F dot s) / |s|^2) * s
        */
        Vector2<T>& getProjection(math::Vector2<T>& s)
        {
            math::Vector2<T> self(*this);

            T length = s.getLength();

            if (length == 0)
            {
                return math::Vector2<T>();
            }
            else
            {
                return (s * (self.getDotProduct(s)) / (length * length));
            }
        }

        /**
        *
        */
        bool equals(math::Vector2<T>& vector)
        {
            real32 epsilon = EPSILON;
            bool ret = (fabs(m_x - vector.m_x) < epsilon) && (fabs(m_y - vector.m_y) < epsilon);
            return ret;
        }

        /**
        *
        */
        real32 getLength()
        {
            real32 length = sqrt((real32)(m_x * m_x + m_y * m_y)) * 1.0f;
            return length;
        }

    public:
        T m_x;
        T m_y;

    };
    // Define a float typed Vector
    typedef Vector2<real32> Vector2f;
}
#endif