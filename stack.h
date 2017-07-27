//
// Created by grigo on 27.07.17.
//

#ifndef LIST_STACK_C_H
#define LIST_STACK_C_H

typedef struct Stack {
    char *name;
    struct Stack *previous;
} Stack;

void push(Stack **stack, char *fullName);
void pop(Stack **stack);
#endif //LIST_STACK_C_H
