#include "matrix.h"
#include <stdio.h>
#include <math.h>

void init_zero_matrix(float matrix[3][3])
{
    int i, j;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            matrix[i][j] = 0.0f;
        }
    }
}

void print_matrix(const float matrix[3][3])
{
    int i, j;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void add_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    int i, j;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void init_identity_matrix(float matrix[3][3])
{
    int i, j;
    init_zero_matrix(matrix);
    for(i = 0; i < 3; i++){
        matrix[i][i] = 1.0f;
    }
}

void scalar_multiply_matrix(float matrix[3][3], float scalar)
{
    int i, j;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            matrix[i][j] *= scalar;
        }
    }
}

void multiply_matrices(const float a[3][3], const float b[3][3], float result[3][3])
{
    int i, j, k;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            result[i][j] = 0.0f;
            for(k = 0; k < 3; k++){
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void transform_point(const float matrix[3][3], const float point[3], float result[3])
{
    int i, j;
    for(i = 0; i < 3; i++){
        result[i] = 0.0f;
        for(j = 0; j < 3; j++){
            result[i] += matrix[i][j] * point[j];
        }
    }
}

void scale(float matrix[3][3], float sx, float sy)
{
    float s[3][3];
    init_identity_matrix(s);
    s[0][0] = sx;
    s[1][1] = sy;
    float temp[3][3];
    multiply_matrices(s, matrix, temp);
    int i, j;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            matrix[i][j] = temp[i][j];
        }
    }
}

void shift(float matrix[3][3], float tx, float ty)
{
    float t[3][3];
    init_identity_matrix(t);
    t[0][2] = tx;
    t[1][2] = ty;
    float temp[3][3];
    multiply_matrices(t, matrix, temp);
    int i, j;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            matrix[i][j] = temp[i][j];
        }
    }
}

void rotate(float matrix[3][3], float angle)
{
    float r[3][3];
    init_identity_matrix(r);
    r[0][0] = cos(angle);
    r[0][1] = -sin(angle);
    r[1][0] = sin(angle);
    r[1][1] = cos(angle);
    float temp[3][3];
    multiply_matrices(r, matrix, temp);
    int i, j;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            matrix[i][j] = temp[i][j];
        }
    }
}