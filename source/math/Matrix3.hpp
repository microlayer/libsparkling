#ifndef __SPARK_MATH_MATRIX3_HPP_INCLUDED__
#define __SPARK_MATH_MATRIX3_HPP_INCLUDED__

#include "spark/SparkTypes.hpp"

namespace spark::math {
    /**
    *
    */
    template <class T> class Matrix3
    {
    public:
        /**
        *
        */
        Matrix3(void)
        {
            for (uint16_t i = 0; i < 9; i++)
            {
                if ((i % 4) == 0)
                {
                    m_matrix[i] = 1.0f;
                }
                else
                {
                    m_matrix[i] = 0.0f;
                }
            }
        }

        /**
        *
        */
        ~Matrix3(void)
        {
        }

        /**
        *
        */
        Matrix3<T> setRotation(const spark::math::Vector3f rotation)
        {
            // Attention: OpenGL matrices are Column-major
            const real32 cr = cos(rotation.X);
            const real32 sr = sin(rotation.X);
            const real32 cp = cos(rotation.Y);
            const real32 sp = sin(rotation.Y);
            const real32 cy = cos(rotation.Z);
            const real32 sy = sin(rotation.Z);

            m_matrix[0] = (T)(cp * cy);
            m_matrix[1] = (T)(cp * sy);
            m_matrix[2] = (T)(-sp);

            const real32 srsp = sr * sp;
            const real32 crsp = cr * sp;

            m_matrix[4] = (T)(srsp * cy - cr * sy);
            m_matrix[5] = (T)(srsp * sy + cr * cy);
            m_matrix[6] = (T)(sr * cp);

            m_matrix[8] = (T)(crsp * cy + sr * sy);
            m_matrix[9] = (T)(crsp * sy - sr * cy);
            m_matrix[10] = (T)(cr * cp);

            return *this;
        }

        /**
        *
        */
        Matrix3<T> setScale(const uint16_t scale)
        {
            m_matrix[0] = scale;
            m_matrix[5] = scale;
            m_matrix[10] = scale;

            return *this;
        }

        /**
        *
        */
        Matrix3<T> setScale(const real32 x, const real32 y, const real32 z)
        {
            m_matrix[0] = x;
            m_matrix[5] = y;
            m_matrix[10] = z;

            return *this;
        }

    public:
        /**
        *
        */
        const T* getPointer() const
        {
            return m_matrix;
        }

    public:	// Operators
        /**
        *
        */
        inline T& operator[](const uint32_t index)
        {
            return m_matrix[index];
        }

        /**
        *
        */
        inline T& operator()(const uint32_t row, const uint32_t col) const
        {
            return m_matrix[row * 3 + col];
        }

        /**
        * @brief Multiply this matrix with a scalar.
        */
        inline Matrix3<T> operator*(const T& scalar) const
        {
            spark::math::Matrix4<T> m;

            m[0] = m_matrix[0] * scalar;
            m[1] = m_matrix[1] * scalar;
            m[2] = m_matrix[2] * scalar;
            m[3] = m_matrix[3] * scalar;
            m[4] = m_matrix[4] * scalar;
            m[5] = m_matrix[5] * scalar;
            m[6] = m_matrix[6] * scalar;
            m[7] = m_matrix[7] * scalar;
            m[8] = m_matrix[8] * scalar;

            return m;
        }

    public: // The matrix data
        T m_matrix[9];
    };

    // Define a float typed Matrix3
    typedef Matrix3<real32> Matrix3f;
}
#endif