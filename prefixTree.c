#include <stdio.h>
#include <stdlib.h>
#include "prefixTree.h"
#include <string.h>
#include <ctype.h>

void addTree(char letter) {
    tolower(letter);
    letter = letter - 'a';
    printf("letter = %d ", letter);
}

int main(int argc, char *argv[]) {
    Prefix *x = malloc(sizeof(Prefix));
    int *i = "sdas sdsad saweqw";
    int c = 123;
    char bi = 123;
    printf("i = %s \n", i);
    x->changWord = false;
    x->followingLetter[1] = malloc(sizeof(Prefix));
    Prefix *x1 = x->followingLetter[1];
    x1->changWord = true;
    addTree('c');
    printf("x->changWord = %d,  x1->changWord = %d \n", x->changWord, x1->changWord);
    return 0;
}