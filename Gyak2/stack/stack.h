#ifndef STACK_H
#define STACK_H

#define STACK_MAX 100

typedef struct {
    float matrices[STACK_MAX][3][3];
    int top;
} MatrixStack;

void init_stack(MatrixStack *stack);
int push_matrix(MatrixStack *stack, float matrix[3][3]);
int pop_matrix(MatrixStack *stack, float matrix[3][3]);

#endif