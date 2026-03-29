#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char caesar_shift(char c, int key, int encrypt) {
    if (isalpha(c)) {
        char base = islower(c) ? 'a' : 'A';
        key = key % 26; 

        if (encrypt)
            return (c - base + key) % 26 + base;
        else
            return (c - base - key + 26) % 26 + base;
    }
    return c;
}

int main(int argc, char *argv[]) { 
    if (argc != 2) {
        printf("Usage: %s -e (encrypt) or -d (decrypt)\n", argv[0]);
        return 1;
    }

    int encrypt;
    if (argv[1][0] == '-' && argv[1][1] == 'e')
        encrypt = 1;
    else if (argv[1][0] == '-' && argv[1][1] == 'd')
        encrypt = 0;
    else {
        printf("Invalid option. Use -e or -d\n");
        return 1;
    }

    
    FILE *keyFile = fopen("key.txt", "r");
    if (!keyFile) {
        perror("Error opening key.txt");
        return 1;
    }

    int key;
    if (fscanf(keyFile, "%d", &key) != 1) {
        fprintf(stderr, "Invalid key format\n");
        fclose(keyFile);
        return 1;
    }
    fclose(keyFile);

    
    const char *inputName = encrypt ? "plaintext.txt" : "encrypted.txt";
    FILE *inputFile = fopen(inputName, "r");
    if (!inputFile) {
        perror("Error opening input file");
        return 1;
    }

    FILE *outputFile;
    if (encrypt)
        outputFile = fopen("encrypted.txt", "w");
    else
        outputFile = fopen("decrypted.txt", "w");

    if (!outputFile) {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }

    int ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        fputc(caesar_shift((char)ch, key, encrypt), outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
    printf("Operation completed successfully.\n");

    return 0;
}