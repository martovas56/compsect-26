#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    FILE *fin = fopen("encrypted.txt", "r");
    if (!fin) {
        perror("Error opening encrypted.txt");
        return 1;
    }

    char text[10000];
    if (!fgets(text, sizeof(text), fin)) {
        fclose(fin);
        return 0;
    }
    fclose(fin);

    text[strcspn(text, "\r\n")] = '\0';
    int len = strlen(text);

    printf("Searching for repeating trigrams...\n");

    for (int i = 0; i <= len - 3; i++) {
        
        if (!isalpha(text[i]) || !isalpha(text[i + 1]) || !isalpha(text[i + 2])) {
            continue;
        }

        char trigram1[4] = {toupper(text[i]), toupper(text[i+1]), toupper(text[i+2]), '\0'};

        for (int j = i + 1; j <= len - 3; j++) {
            if (!isalpha(text[j]) || !isalpha(text[j + 1]) || !isalpha(text[j + 2])) {
                continue;
            }

            char trigram2[4] = {toupper(text[j]), toupper(text[j+1]), toupper(text[j+2]), '\0'};

            if (strcmp(trigram1, trigram2) == 0) {
                
                printf("Found \"%s\": Pos %d & Pos %d -> Distance: %d\n",
                       trigram1, i, j, j - i);
            }
        }
    }

    return 0;
}
