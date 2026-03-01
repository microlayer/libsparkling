#ifndef __SPARK_MATH_VECTOR3_HPP_INCLUDED__
#define __SPARK_MATH_VECTOR3_HPP_INCLUDED__

#include "spark/SparkTypes.hpp"
#include "spark/SparkLibConfig.hpp"
#include <math.h>

namespace spark::math {
    /**
    *
    */
    template <class T> class Vector3
    {
    public:
        /**
        *
        */
        Vector3() :
            m_x(0), m_y(0), m_z(0)
        {
        }

        /**
        *
        */
        Vector3(T x, T y, T z) :
            m_x(x), m_y(y), m_z(z)
        {
        }

        /**
        *
        */
        Vector3(const Vector3& v)
        {
            this->m_x = v.m_x;
            this->m_y = v.m_y;
            this->m_z = v.m_z;
        }

        /**
        *
        */
        Vector3<T> operator*(const T& scalar) const
        {
            return Vector3<T>(m_x * scalar, m_y * scalar, m_z * scalar);
        }

        /**
        *
        */
        Vector3<T> operator/(const T& scalar) const
        {
            return Vector3<T>(m_x / scalar, m_y / scalar, m_z / scalar);
        }

        /**
        *
        */
        Vector3<T> operator+(const Vector3<T>& vector) const
        {
            return Vector3<T>(m_x + vector.m_x, m_y + vector.m_y, m_z + vector.m_z);
        }

        /**
        *
        */
        Vector3<T> operator-(const Vector3<T>& vector) const
        {
            return Vector3<T>(m_x - vector.m_x, m_y - vector.m_y, m_z - vector.m_z);
        }

        /**
        *
        */
        bool operator==(const Vector3<T>& vector) const
        {
            return Equals(vector);
        }

        /**
        * @brief Returns the normalized vector of this.
        */
        Vector3<T>& normalize()
        {
            real32 length = getLength();

            if (length == 0) return *this;

            length = 1.0f / sqrt(length);

            m_x = (T)(m_x * length);
            m_y = (T)(m_y * length);
            m_z = (T)(m_z * length);

            return *this;
        }

        /**
        * @brief Returns the cross product between this and the given vector.
        */
        Vector3<T>& getCrossProduct(math::Vector3<T>& vector)
        {
            math::Vector3<T> crossProduct;
            crossProduct.m_x = m_y * vector.m_z - m_z * vector.m_y;
            crossProduct.m_y = m_z * vector.m_x - m_x * vector.m_z;
            crossProduct.m_z = m_x * vector.m_y - m_y * vector.m_x;
            return crossProduct;
        }

        /**
        * @brief Returns the dot product of this and the given vector.
        */
        real32 getDotProduct(math::Vector3<T>& vector)
        {
            real32 dotProduct = 0.0f;
            dotProduct = (this->m_x * vector.m_x) + (this->m_y * vector.m_y) + (this->m_z * vector.m_z);
            return dotProduct;
        }

        /**
        * @brief Returns the angel between this and the given vector.
        */
        real32 getAngelBetween(math::Vector3<T>& vector)
        {
            real32 pi = ML_PI;
            real32 rad = 0.0f;
            real32 grad = 0.0f;

            math::Vector3<T> self(*this);

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
        * @brief Returns the reflection vector between this and the given normal vector N as shown in this formula: a(e) = e - 2*(e dot N) * N
        */
        Vector3<T>& getReflection(math::Vector3<T>& n)
        {
            math::Vector3<T> e(*this);
            math::Vector3<T> a = n * (2 * e.getDotProduct(n)) - e;
            return a;
        }

        /**
        * @brief Projects this vector (F) in the direction of s; Fs = ((F dot s) / |s|^2) * s
        */
        Vector3<T>& getProjection(math::Vector3<T>& s)
        {
            math::Vector3<T> self(*this);

            T length = s.getLength();

            if (length == 0)
            {
                return math::Vector3<T>();
            }
            else
            {
                return (s * (self.getDotProduct(s)) / (length * length));
            }
        }

        /**
        *
        */
        bool equals(math::Vector3<T>& vector)
        {
            real32 epsilon = EPSILON;
            bool ret = (fabs(m_x - vector.m_x) < epsilon) && (fabs(m_y - vector.m_y) < epsilon) && (fabs(m_z - vector.m_z) < epsilon);
            return ret;
        }

        /**
        *
        */
        real32 getLength()
        {
            real32 length = sqrt((real32)(m_x * m_x + m_y * m_y + m_z * m_z)) * 1.0f;
            return length;
        }

    public:
        T m_x;
        T m_y;
        T m_z;
    };
    // Define a float typed Vector
    typedef Vector3<real32> Vector3f;
}
#endif

