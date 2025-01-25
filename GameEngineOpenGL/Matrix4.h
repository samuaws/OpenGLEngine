#ifndef MATRIX4_H
#define MATRIX4_H

#include "Vector3.h"

class Matrix4 {
public:
    float data[4][4];

    Matrix4() {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                data[i][j] = (i == j) ? 1.0f : 0.0f; // Identity matrix
    }

    // Translation matrix
    static Matrix4 translate(const Vector3& translation) {
        Matrix4 result;
        result.data[0][3] = translation.x;
        result.data[1][3] = translation.y;
        result.data[2][3] = translation.z;
        return result;
    }

    // Scaling matrix
    static Matrix4 scale(const Vector3& scale) {
        Matrix4 result;
        result.data[0][0] = scale.x;
        result.data[1][1] = scale.y;
        result.data[2][2] = scale.z;
        return result;
    }

    // Multiplication with another matrix
    Matrix4 operator*(const Matrix4& other) const {
        Matrix4 result;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < 4; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];
            }
        return result;
    }
};

#endif // MATRIX4_H
