#include <stdio.h>
#include <ctype.h>
#include <string.h>

char decrypt_char(char c, int key) {
    if (isupper(c)) {
        return 'A' + (c - 'A' - key % 26 + 26) % 26;
    }
    if (islower(c)) {
        return 'a' + (c - 'a' - key % 26 + 26) % 26;
    }
    return c; 
}

void decrypt_with_key(const char *text, int key) { 
    for (int i = 0; text[i] != '\0'; i++) {
        putchar(decrypt_char(text[i], key));
    }
    putchar('\n');
}

int main(int argc, char *argv[]) { 
    if (argc != 2) {
        printf("Usage: %s \"encrypted text\"\n", argv[0]);
        return 1;
    }

    printf("Trying all 25 possible Caesar cipher shifts:\n\n");

    for (int key = 1; key <= 25; key++) {
        printf("Key %2d: ", key);
        decrypt_with_key(argv[1], key);
    }

    return 0;
}