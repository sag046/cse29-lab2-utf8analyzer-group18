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
    const char *input = argv[1];
    int is_ascii = 1;
    int length_in_bytes = strlen(input);

    char uppercased[1024];
    strncpy(uppercased, input, sizeof(uppercased));
    uppercased[sizeof(uppercased) - 1] = '\0';

    for (int i = 0; i < length_in_bytes; i++) {
        unsigned char c = input[i];
      if (c > 127) {
        is_ascii = 0;
      }
      if (c >= 'a' && c <= 'z') {
        uppercased[i] = c - 32;
      }
}

printf("Valid ASCII: %s\n", is_ascii ? "true" : "false");
printf("Uppercased ASCII: %s\n", uppercased);
printf("Length in bytes: %d\n", length_in_bytes);
    // implement the UTF-8 analyzer here
}
