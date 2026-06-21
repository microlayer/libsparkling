#ifndef __SPARK_MATH_MATRIX3_HPP_INCLUDED__
#define __SPARK_MATH_MATRIX3_HPP_INCLUDED__

#include "spark/SparkTypes.hpp"

namespace spark::math {
    /**
    * @brief Hint: OpenGL matrices are Column-major
    */
    template <class T> class Matrix3
    {
    public:
        /**
        * @brief Init matrix3 with a Identity matrix.
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
            const real32 cr = cos(rotation.m_x);
            const real32 sr = sin(rotation.m_x);
            const real32 cp = cos(rotation.m_y);
            const real32 sp = sin(rotation.m_y);
            const real32 cy = cos(rotation.m_z);
            const real32 sy = sin(rotation.m_z);

            const real32 srsp = sr * sp;
            const real32 crsp = cr * sp;

            m_matrix[0] = cp * cy;
            m_matrix[1] = cp * sy;
            m_matrix[2] = -sp;

            m_matrix[3] = srsp * cy - cr * sy;
            m_matrix[4] = srsp * sy + cr * cy;
            m_matrix[5] = sr * cp;

            m_matrix[6] = crsp * cy + sr * sy;
            m_matrix[7] = crsp * sy - sr * cy;
            m_matrix[8] = cr * cp;

            return *this;
        }

        /**
        *
        */
        Matrix3<T> setScale(const uint16_t scale)
        {
            m_matrix[0] = scale;
            m_matrix[4] = scale;
            m_matrix[8] = scale;

            return *this;
        }

        /**
        *
        */
        Matrix3<T> setScale(const real32 x, const real32 y, const real32 z)
        {
            m_matrix[0] = x;
            m_matrix[4] = y;
            m_matrix[8] = z;

            return *this;
        }

        /**
        *
        */
        Matrix3<T> getInverseMatrix() const
        {
            Matrix3<T> r;

            // Transpose 
            r.m_matrix[0] = m_matrix[0];
            r.m_matrix[1] = m_matrix[3];
            r.m_matrix[2] = m_matrix[6];

            r.m_matrix[3] = m_matrix[1];
            r.m_matrix[4] = m_matrix[4];
            r.m_matrix[5] = m_matrix[7];

            r.m_matrix[6] = m_matrix[2];
            r.m_matrix[7] = m_matrix[5];
            r.m_matrix[8] = m_matrix[8];

            return r;
        }

        /**
        *
        */
        Matrix3<T> getTransposedMatrix() const
        {
            Matrix3<T> r;

            r.m_matrix[0] = m_matrix[0];
            r.m_matrix[1] = m_matrix[3];
            r.m_matrix[2] = m_matrix[6];

            r.m_matrix[3] = m_matrix[1];
            r.m_matrix[4] = m_matrix[4];
            r.m_matrix[5] = m_matrix[7];

            r.m_matrix[6] = m_matrix[2];
            r.m_matrix[7] = m_matrix[5];
            r.m_matrix[8] = m_matrix[8];

            return r;
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
            spark::math::Matrix3<T> m;

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

        /**
        * @brief Multiply this matrix with another matrix.
        */
        inline Matrix3<T> operator*(const Matrix3<T>& matrix) const
        {
            const T* m1 = m_matrix;
            const T* m2 = matrix.m_matrix;

            Matrix3<T> result;

            // Column 0
            result[0] = m1[0] * m2[0] + m1[3] * m2[1] + m1[6] * m2[2];
            result[1] = m1[1] * m2[0] + m1[4] * m2[1] + m1[7] * m2[2];
            result[2] = m1[2] * m2[0] + m1[5] * m2[1] + m1[8] * m2[2];

            // Column 1
            result[3] = m1[0] * m2[3] + m1[3] * m2[4] + m1[6] * m2[5];
            result[4] = m1[1] * m2[3] + m1[4] * m2[4] + m1[7] * m2[5];
            result[5] = m1[2] * m2[3] + m1[5] * m2[4] + m1[8] * m2[5];

            // Column 2
            result[6] = m1[0] * m2[6] + m1[3] * m2[7] + m1[6] * m2[8];
            result[7] = m1[1] * m2[6] + m1[4] * m2[7] + m1[7] * m2[8];
            result[8] = m1[2] * m2[6] + m1[5] * m2[7] + m1[8] * m2[8];

            return result;
        }

        /**
        * @brief Multiply this matrix with an vector
        */
        inline math::Vector3<T> operator*(const math::Vector3<T>& vector) const
        {
            const T* m = m_matrix;
            math::Vector3<T> result;

            result.m_x = m[0] * vector.m_x + m[3] * vector.m_y + m[6] * vector.m_z;
            result.m_y = m[1] * vector.m_x + m[4] * vector.m_y + m[7] * vector.m_z;
            result.m_z = m[2] * vector.m_x + m[5] * vector.m_y + m[8] * vector.m_z;

            return result;
        }

        /**
        *
        */
        inline Matrix3<T>& operator=(const Matrix3<T>& matrix)
        {
            if (this == &matrix)
            {
                return *this;
            }

            memcpy(m_matrix, matrix.m_matrix, 9 * sizeof(T));

            return *this;
        }

    public: // The matrix data
        T m_matrix[9];
    };

    // Define a float typed Matrix3
    typedef Matrix3<real32> Matrix3f;
}
#endif