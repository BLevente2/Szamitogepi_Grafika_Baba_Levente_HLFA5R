#include "matrix.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[])
{
    float a[3][3] = {
        { 1.0f, -2.0f,  3.0f},
        { 5.0f, -3.0f,  0.0f},
        {-2.0f,  1.0f, -4.0f}
    };
    float b[3][3];
    float c[3][3];

    init_zero_matrix(b);
    b[1][1] =  8.0f;
    b[2][0] = -3.0f;
    b[2][2] =  5.0f;

    printf("Matrix A:\n");
    print_matrix(a);
    printf("\nMatrix B:\n");
    print_matrix(b);

    add_matrices(a, b, c);
    printf("\nSum (A + B):\n");
    print_matrix(c);

    float id[3][3];
    init_identity_matrix(id);
    printf("\nIdentity Matrix:\n");
    print_matrix(id);

    scalar_multiply_matrix(id, 2.0f);
    printf("\nIdentity Matrix after scalar multiplication by 2:\n");
    print_matrix(id);

    float m1[3][3] = {
        {1.0f, 2.0f, 3.0f},
        {0.0f, 1.0f, 4.0f},
        {5.0f, 6.0f, 0.0f}
    };
    float m2[3][3];
    init_identity_matrix(m2);
    float mprod[3][3];
    multiply_matrices(m1, m2, mprod);
    printf("\nProduct of M1 and Identity Matrix (M2):\n");
    print_matrix(mprod);

    float point[3] = {1.0f, 1.0f, 1.0f};
    float tpoint[3];
    transform_point(mprod, point, tpoint);
    printf("\nTransformed point using product matrix:\n");
    printf("%4.4f %4.4f %4.4f\n", tpoint[0], tpoint[1], tpoint[2]);

    float transform[3][3];
    init_identity_matrix(transform);
    scale(transform, 2.0f, 3.0f);
    rotate(transform, 3.14159f/4.0f);
    shift(transform, 5.0f, -2.0f);
    printf("\nTransformation Matrix (after scale, rotate, shift):\n");
    print_matrix(transform);

    float point2[3] = {2.0f, 3.0f, 1.0f};
    float tpoint2[3];
    transform_point(transform, point2, tpoint2);
    printf("\nTransformed point2 using transformation matrix:\n");
    printf("%4.4f %4.4f %4.4f\n", tpoint2[0], tpoint2[1], tpoint2[2]);

    return 0;
}