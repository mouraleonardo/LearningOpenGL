#ifndef MATRIX4_H
#define MATRIX4_H

#include <cmath>

/*
    Matrix4

    Utility class used to create and manipulate 4x4 matrices.

    These matrices are commonly used in 3D graphics for:

    - Identity transformations
    - Rotations
    - Translations
    - Perspective projections

    OpenGL expects matrices in column-major order.
*/

class Matrix4
{
public:

    /*
        Creates a 4x4 identity matrix.

        An identity matrix does not change the position,
        rotation, or scale of an object.

        [1 0 0 0]
        [0 1 0 0]
        [0 0 1 0]
        [0 0 0 1]
    */
    static void Identity(float* m)
    {
        // Set all values to zero
        for (int i = 0; i < 16; i++)
            m[i] = 0.0f;

        // Set diagonal values to one
        m[0] = 1.0f;
        m[5] = 1.0f;
        m[10] = 1.0f;
        m[15] = 1.0f;
    }

    /*
        Creates a rotation matrix around the Y axis.

        This matrix rotates an object left or right
        around its vertical axis.

        angle is measured in radians.
    */
    static void RotationY(float angle, float* m)
    {
        Identity(m);

        m[0] = cosf(angle);
        m[2] = -sinf(angle);

        m[8] = sinf(angle);
        m[10] = cosf(angle);
    }

    /*
        Creates a translation matrix.

        Translation moves an object in 3D space.

        x = horizontal movement
        y = vertical movement
        z = depth movement
    */
    static void Translation(
        float x,
        float y,
        float z,
        float* m)
    {
        Identity(m);

        m[12] = x;
        m[13] = y;
        m[14] = z;
    }

    /*
        Creates a perspective projection matrix.

        This matrix simulates how the human eye sees
        objects in the real world.

        Objects farther away appear smaller,
        creating the illusion of depth.

        Parameters:

        fov        = field of view angle
        aspect     = screen width / height
        nearPlane  = closest visible distance
        farPlane   = farthest visible distance
    */
    static void Perspective(
        float fov,
        float aspect,
        float nearPlane,
        float farPlane,
        float* m)
    {
        // Calculate focal length
        float f =
            1.0f /
            tanf(fov * 0.5f);

        // Clear matrix
        for (int i = 0; i < 16; i++)
            m[i] = 0.0f;

        // Horizontal scaling
        m[0] = f / aspect;

        // Vertical scaling
        m[5] = f;

        // Depth calculations
        m[10] =
            (farPlane + nearPlane) /
            (nearPlane - farPlane);

        m[11] = -1.0f;

        m[14] =
            (2.0f * farPlane * nearPlane) /
            (nearPlane - farPlane);
    }

    /*
        Multiplies two 4x4 matrices.

        result = a × b

        Matrix multiplication combines multiple
        transformations into a single matrix.

        Example:

        MVP = Projection × View × Model
    */
    static void Multiply(
        float* result,
        const float* a,
        const float* b)
    {
        float temp[16];

        // Multiply matrix A by matrix B
        for (int col = 0; col < 4; col++)
        {
            for (int row = 0; row < 4; row++)
            {
                temp[col * 4 + row] =

                    a[0 * 4 + row] *
                    b[col * 4 + 0]

                    +

                    a[1 * 4 + row] *
                    b[col * 4 + 1]

                    +

                    a[2 * 4 + row] *
                    b[col * 4 + 2]

                    +

                    a[3 * 4 + row] *
                    b[col * 4 + 3];
            }
        }

        // Copy temporary result
        // into the output matrix
        for (int i = 0; i < 16; i++)
            result[i] = temp[i];
    }
};

#endif