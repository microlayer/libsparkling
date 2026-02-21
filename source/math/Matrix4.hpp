#ifndef __SPARK_MATH_MATRIX4_HPP_INCLUDED__
#define __SPARK_MATH_MATRIX4_HPP_INCLUDED__

#include "spark/SparkTypes.hpp"
#include "math/Vector3.hpp"
#include <math.h>

namespace spark::math {
    template <class T> class Matrix4
    {
    public:
        /**
        * @Brief Init matrix4 with a Identity matrix.
        */
        Matrix4(void)
        {
            for (uint16_t i = 0; i < 16; i++)
            {
                if ((i % 5) == 0)
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
        ~Matrix4(void)
        {
        }

        /**
        *
        */
        Matrix4<T> setRotation(const spark::math::Vector3f rotation)
        {
            // Attention: OpenGL matrices are Column-major
            const real32 cr = cos(rotation.m_x);
            const real32 sr = sin(rotation.m_x);
            const real32 cp = cos(rotation.m_y);
            const real32 sp = sin(rotation.m_y);
            const real32 cy = cos(rotation.m_z);
            const real32 sy = sin(rotation.m_z);

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
        Matrix4<T> setTranslation(const spark::math::Vector3f translation)
        {
            // Attention: OpenGL matrices are Column-major
            m_matrix[12] = translation.m_x;
            m_matrix[13] = translation.m_y;
            m_matrix[14] = translation.m_z;

            return *this;
        }

        /**
        *
        */
        Matrix4<T> setScale(const uint16_t scale)
        {
            m_matrix[0] = scale;
            m_matrix[5] = scale;
            m_matrix[10] = scale;

            return *this;
        }

        /**
        *
        */
        Matrix4<T> setScale(const real32 x, const real32 y, const real32 z)
        {
            m_matrix[0] = x;
            m_matrix[5] = y;
            m_matrix[10] = z;

            return *this;
        }

        /**
        *
        */
        Matrix4<T> getInverseMatrix() const
        {
            // The invert of a translation matrix is the negation of its translation coordinates
            math::Matrix4<T> invertOfTranslation;
            invertOfTranslation[12] = -m_matrix[12]; invertOfTranslation[13] = -m_matrix[13]; invertOfTranslation[14] = -m_matrix[14];

            // The invert of a rotation matrix is its transposed matrix
            math::Matrix4<T> invertOfRotation;
            memcpy(invertOfRotation.m_matrix, m_matrix, sizeof(m_matrix));
            invertOfRotation[12] = 0; // Reset translation X to copy the rotation part of this matrix
            invertOfRotation[13] = 0; // Reset translation Y to copy the rotation part of this matrix
            invertOfRotation[14] = 0; // Reset translation Z to copy the rotation part of this matrix

            invertOfRotation = invertOfRotation.getTransposedMatrix();

            // The multiplication is the result
            math::Matrix4<T> m = invertOfRotation * invertOfTranslation;

            return m;
        }

        /**
        *
        */
        Matrix4<T> getTransposedMatrix() const
        {
            spark::math::Matrix4<T> m;

            m[0] = m_matrix[0]; m[1] = m_matrix[4]; m[2] = m_matrix[8]; m[3] = m_matrix[12];
            m[4] = m_matrix[1]; m[5] = m_matrix[5]; m[6] = m_matrix[9]; m[7] = m_matrix[13];
            m[8] = m_matrix[2]; m[9] = m_matrix[6]; m[10] = m_matrix[10]; m[11] = m_matrix[14];
            m[12] = m_matrix[3]; m[13] = m_matrix[7]; m[14] = m_matrix[11]; m[15] = m_matrix[15];

            return m;
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
        inline T& operator()(const uint32_t row, const uint32_t col)
        {
            return m_matrix[row * 4 + col];
        }

        /**
        * @Brief Multiply this matrix with a scalar
        */
        inline Matrix4<T> operator*(const T& scalar) const
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
            m[9] = m_matrix[9] * scalar;
            m[10] = m_matrix[10] * scalar;
            m[11] = m_matrix[11] * scalar;
            m[12] = m_matrix[12] * scalar;
            m[13] = m_matrix[13] * scalar;
            m[14] = m_matrix[14] * scalar;
            m[15] = m_matrix[15] * scalar;

            return m;
        }

        /**
        * @Brief Multiply this matrix with another matrix.
        */
        inline Matrix4<T> operator*(const Matrix4<T>& matrix) const
        {
            const T* m1 = m_matrix;
            const T* m2 = matrix.m_matrix;

            Matrix4<T> result;

            result[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
            result[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
            result[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
            result[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];

            result[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
            result[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
            result[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
            result[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];

            result[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11];
            result[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
            result[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
            result[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];

            result[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
            result[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
            result[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
            result[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];

            return result;
        }

        /**
        * @Brief Multiply this matrix with an vector
        */
        inline math::Vector3<T> operator*(const math::Vector3<T>& vector) const
        {
            const T* m = m_matrix;
            math::Vector3<T> result;

            result.m_x = m[0] * vector.m_x + m[4] * vector.m_y + m[8] * vector.m_z;
            result.m_y = m[1] * vector.m_x + m[5] * vector.m_y + m[9] * vector.m_z;
            result.m_z = m[2] * vector.m_x + m[6] * vector.m_y + m[10] * vector.m_z;

            return result;
        }

        /**
        *
        */
        inline Matrix4<T>& operator=(const Matrix4<T>& matrix)
        {
            if (this == &matrix)
            {
                return *this;
            }

            memcpy(m_matrix, matrix.m_matrix, 16 * sizeof(T));

            return *this;
        }

    public: // The matrix data
        T m_matrix[16];
    };

    // Define a float typed Matrix4	
    typedef Matrix4<real32> Matrix4f;
}
#endif
