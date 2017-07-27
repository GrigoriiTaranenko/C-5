#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int help;
    struct Node *helpi;
} Node;

int main(int argc, char *argv[]) {
    Node* inver = NULL;
    inver = malloc(sizeof(Node));
    inver->help = 11;
    inver->helpi = malloc(sizeof(Node));

    Node* inm = inver->helpi;
    inm->help = 18;

    for (int i = 0; i<10; i++) {
        inm->helpi = malloc(sizeof(Node));
        inm = inm->helpi;
        inm->help = i;
    }

    for (int i = 0; i<10; i++) {
        printf("inver->help = %i \n",inver->help);
        inver = inver->helpi;
    }

    printf("inver->help = %d \n", inver->help);

    return 0;
}