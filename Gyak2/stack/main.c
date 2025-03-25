#include "matrix.h"
#include "stack.h"
#include <stdio.h>
#include <math.h>

int main(void) {
    MatrixStack stack;
    float transform[3][3];
    init_identity_matrix(transform);
    init_stack(&stack);
    
    push_matrix(&stack, transform);
    scale(transform, 2.0f, 3.0f);
    printf("After scale:\n");
    print_matrix(transform);
    pop_matrix(&stack, transform);
    printf("After undo scale:\n");
    print_matrix(transform);
    
    push_matrix(&stack, transform);
    rotate(transform, 3.14159f/4.0f);
    printf("After rotate:\n");
    print_matrix(transform);
    pop_matrix(&stack, transform);
    printf("After undo rotate:\n");
    print_matrix(transform);
    
    push_matrix(&stack, transform);
    shift(transform, 5.0f, -2.0f);
    printf("After shift:\n");
    print_matrix(transform);
    pop_matrix(&stack, transform);
    printf("After undo shift:\n");
    print_matrix(transform);
    
    return 0;
}