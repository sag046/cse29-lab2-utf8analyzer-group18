#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: utf8analyzer \"<UTF-8 encoded string>\"\n");
        return 1;
    }

    // implement the UTF-8 analyzer here

    //checks whether string is valid ASCII
    if(!(sizeof(argv) < 127)){
        return 1;
    }

    //string input, any character that is lowercase is turned to uppercase
}
