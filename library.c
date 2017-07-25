#include "library.h"

#include <stdio.h>


struct hello {
    int help;
    struct hello helpi;
};

int main(int argc, char *argv[]) {
    struct hello inver;
    inver.help = 10;
    printf("inver.help = %d \n", inver.help);
    return 0;
}