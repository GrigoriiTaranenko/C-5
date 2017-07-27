//
// Created by grigo on 27.07.17.
//

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
Stack *stack1;
Stack *stack;


int main(int argc, char *name[]) {
    Stack *stack = malloc(sizeof(Stack));
    int *b;
    b = malloc(sizeof(sizeof(int) * 4));
    char byt;
    stack->name = "Андреевич";
    push(&stack, "Григорий");
    pop(&stack);
    printf("Хотите ли вы работать со стеком стек? 1-да, 0-нет \n");
    scanf("%i", &byt);
    printf("byt = %d \n", byt);
    while (byt == 1) {
        printf("Хотите ли вы получить значения или отправить? 1-получить, 0 отправить");

    }
    return 0;
}

void push(Stack **stack, char *fullName) {
    stack1 = malloc(sizeof(Stack));
    stack1->name = fullName;
    stack1->previous = *stack;
    *stack = stack1;
}

void pop(Stack **stack) {
    printf("stack->name = %s \n", (*stack)->name);
    *stack = (*stack)->previous;
    free(*stack);
    printf("stack->name = %s \n", (*stack)->name);
}


