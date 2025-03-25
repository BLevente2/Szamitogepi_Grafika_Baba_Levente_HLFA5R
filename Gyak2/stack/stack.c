#include "stack.h"

void init_stack(MatrixStack *stack) {
    stack->top = 0;
}

int push_matrix(MatrixStack *stack, float matrix[3][3]) {
    if (stack->top >= STACK_MAX) return 0;
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            stack->matrices[stack->top][i][j] = matrix[i][j];
        }
    }
    stack->top++;
    return 1;
}

int pop_matrix(MatrixStack *stack, float matrix[3][3]) {
    if (stack->top <= 0) return 0;
    stack->top--;
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            matrix[i][j] = stack->matrices[stack->top][i][j];
        }
    }
    return 1;
}