#ifndef __SPARK_MATH_PROJECTION_HPP_INCLUDED__
#define __SPARK_MATH_PROJECTION_HPP_INCLUDED__

#define USE_DIRECTX_PERSPECTIVE
#define PI 3.14159265358979323846

namespace spark {
    namespace math {
        template <class T> class ProjectionMatrix
        {
        public:
            /**
            *
            */
            static void createOrthofMatrix(T left, T right, T bottom, T top, T znear, T zfar, T* matrix)
            {
                T m[4][4];	// Matrix layout: [col][row]
                identity(&m[0][0]);

                m[0][0] = 2 / (right - left);
                m[1][1] = 2 / (top - bottom);
                m[2][2] = -2 / (zfar - znear);
                m[3][0] = -(right + left) / (right - left);	// tx
                m[3][1] = -(top + bottom) / (top - bottom);	// ty
                m[3][2] = -(zfar + znear) / (zfar - znear);	// tz

                memcpy(matrix, m, sizeof(m));
            }

            /**
            *
            */
            static void createPerspectiveMatrix(T fovy, T aspect, T zNear, T zFar, T* matrix)
            {
                T m[4][4];	// Matrix layout: [col][row]
                identity(&m[0][0]);

#ifdef USE_GLU_PERSPECTIVE		
                real32 sine, cotangent, deltaZ;
                real32 radians = fovy / 2 * PI / 180;

                deltaZ = zFar - zNear;
                sine = sin(radians);
                if ((deltaZ == 0) || (sine == 0) || (aspect == 0))
                {
                    return;
                }
                cotangent = cos(radians) / sine;

                m[0][0] = cotangent / aspect;
                m[1][1] = cotangent;
                m[2][2] = -(zFar + zNear) / deltaZ;
                m[2][3] = -1;
                m[3][2] = -2 * zNear * zFar / deltaZ;
                m[3][3] = 0;
#endif
#ifdef USE_DIRECTX_PERSPECTIVE			
                real32 xScale, yScale, fovyRad;

                fovyRad = (T)((fovy / 180.0f) * PI);

                yScale = 1.0f / (tan(fovyRad * 0.5f));
                xScale = yScale / aspect;

                // DirectX clipping default - mapped to z:0..1 (nearPlane/farPlane) 
                m[0][0] = xScale;
                m[1][1] = yScale;
                m[2][2] = zFar / (zNear - zFar);			//  OpenGL clipping default - mapped to z:-1..1 (zFar + zNear) / (zNear - zFar) 
                m[2][3] = -1.0f;
                m[3][2] = (zFar * zNear) / (zNear - zFar);	//  OpenGL clipping default - mapped to z:-1..1 (2.0f * zFar*zNear) / (zNear - zFar);
#endif
                memcpy(matrix, m, sizeof(m));
            }

            /**
            *
            */
            static void createLookAtMatrix(T eyeX, T eyeY, T eyeZ, T centerX, T centerY, T centerZ, T upX, T upY, T upZ, T* matrix)
            {
                real32 forward[3], side[3], up[3];
                T m[4][4];	// Matrix layout: [col][row]

                T t[4][4];
                T product[4][4];

                forward[0] = centerX - eyeX;
                forward[1] = centerY - eyeY;
                forward[2] = centerZ - eyeZ;

                up[0] = upX;
                up[1] = upY;
                up[2] = upZ;

                normalize(forward);

                // Side = forward x up
                cross(forward, up, side);
                normalize(side);

                // Recompute up as: up = side x forward
                cross(side, forward, up);

                identity(&m[0][0]);
                m[0][0] = side[0];
                m[1][0] = side[1];
                m[2][0] = side[2];

                m[0][1] = up[0];
                m[1][1] = up[1];
                m[2][1] = up[2];

                m[0][2] = -forward[0];
                m[1][2] = -forward[1];
                m[2][2] = -forward[2];


                identity(&t[0][0]);
                t[3][0] = -eyeX;
                t[3][1] = -eyeY;
                t[3][2] = -eyeZ;

                // Multiplies LookAt with this translation matrix
                for (uint16_t row = 0; row < 4; row++)
                {
                    for (uint16_t col = 0; col < 4; col++)
                    {
                        real32 value = 0.0f;
                        for (uint16_t inner = 0; inner < 4; inner++)
                        {
                            value += m[inner][col] * t[row][inner];
                        }
                        product[row][col] = value;
                    }
                }

                memcpy(matrix, product, sizeof(product));
            }

        private:
            /**
            *
            */
            static void identity(T m[16])
            {
                m[0 + 4 * 0] = 1; m[0 + 4 * 1] = 0; m[0 + 4 * 2] = 0; m[0 + 4 * 3] = 0;
                m[1 + 4 * 0] = 0; m[1 + 4 * 1] = 1; m[1 + 4 * 2] = 0; m[1 + 4 * 3] = 0;
                m[2 + 4 * 0] = 0; m[2 + 4 * 1] = 0; m[2 + 4 * 2] = 1; m[2 + 4 * 3] = 0;
                m[3 + 4 * 0] = 0; m[3 + 4 * 1] = 0; m[3 + 4 * 2] = 0; m[3 + 4 * 3] = 1;
            }

            /**
            *
            */
            static void normalize(T v[3])
            {
                real32 r;
                r = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
                if (r == 0.0) return;
                v[0] /= r;
                v[1] /= r;
                v[2] /= r;
            }

            /**
            *
            */
            static void cross(T v1[3], T v2[3], T result[3])
            {
                result[0] = v1[1] * v2[2] - v1[2] * v2[1];
                result[1] = v1[2] * v2[0] - v1[0] * v2[2];
                result[2] = v1[0] * v2[1] - v1[1] * v2[0];
            }
        };
        // Define a float typed Projection matrix
        typedef ProjectionMatrix<real32> ProjectionMatrixf;
    } // end namespace math
} // end namespace spark
#endif