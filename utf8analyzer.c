#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        if (c > 127) is_ascii = 0;
        if (c >= 'a' && c <= 'z') uppercased[i] = c - 32;
    }

    printf("Valid ASCII: %s\n", is_ascii ? "true" : "false");
    printf("Uppercased ASCII: %s\n", uppercased);
    printf("Length in bytes: %d\n", length_in_bytes);

    int codepoint_count = 0;
    for (int i = 0; i < length_in_bytes;) {
        unsigned char c = input[i];
        int bytes = 1;
        if ((c & 0x80) == 0) bytes = 1;
        else if ((c & 0xE0) == 0xC0) bytes = 2;
        else if ((c & 0xF0) == 0xE0) bytes = 3;
        else if ((c & 0xF8) == 0xF0) bytes = 4;
        codepoint_count++;
        i += bytes;
    }
    printf("Number of code points: %d\n", codepoint_count);

    printf("Code points as decimal numbers: ");
    for (int i = 0; i < length_in_bytes;) {
        uint32_t cp = 0;
        unsigned char c = input[i];
        int bytes = 1;
        if ((c & 0x80) == 0) {
            cp = c;
            bytes = 1;
        } else if ((c & 0xE0) == 0xC0) {
            cp = ((input[i] & 0x1F) << 6) | (input[i + 1] & 0x3F);
            bytes = 2;
        } else if ((c & 0xF0) == 0xE0) {
            cp = ((input[i] & 0x0F) << 12) | ((input[i + 1] & 0x3F) << 6) | (input[i + 2] & 0x3F);
            bytes = 3;
        } else if ((c & 0xF8) == 0xF0) {
            cp = ((input[i] & 0x07) << 18) | ((input[i + 1] & 0x3F) << 12) |
                 ((input[i + 2] & 0x3F) << 6) | (input[i + 3] & 0x3F);
            bytes = 4;
        }
        printf("%u ", cp);
        i += bytes;
    }
    printf("\n");

    printf("Bytes per code point: ");
    for (int i = 0; i < length_in_bytes;) {
        unsigned char c = input[i];
        int bytes = 1;
        if ((c & 0x80) == 0) bytes = 1;
        else if ((c & 0xE0) == 0xC0) bytes = 2;
        else if ((c & 0xF0) == 0xE0) bytes = 3;
        else if ((c & 0xF8) == 0xF0) bytes = 4;
        printf("%d ", bytes);
        i += bytes;
    }
    printf("\n");

    printf("Substring of the first 6 code points: \"");
    int count = 0;
    for (int i = 0; i < length_in_bytes && count < 6;) {
        unsigned char c = input[i];
        int bytes = 1;
        if ((c & 0x80) == 0) bytes = 1;
        else if ((c & 0xE0) == 0xC0) bytes = 2;
        else if ((c & 0xF0) == 0xE0) bytes = 3;
        else if ((c & 0xF8) == 0xF0) bytes = 4;
        for (int j = 0; j < bytes; j++) {
            putchar(input[i + j]);
        }
        i += bytes;
        count++;
    }
    printf("\"\n");

    return 0;
}

