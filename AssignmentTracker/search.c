#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1000

int main() {
    int id;
    FILE *file = fopen("files/storeAssignment.txt", "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    // Count the number of lines in the file
    int lineCount = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lineCount++;
        }
    }

    // Move the file pointer to the beginning of the last line
    fseek(file, 0, SEEK_SET);
    for (int i = 0; i < lineCount - 1; i++) {
        while ((ch = fgetc(file)) != '\n') {
            // Skip characters until a newline is encountered
            if (ch == EOF) {
                break;
            }
        }
        if (ch == EOF) {
            break;
        }
    }

    // Read the second-to-last line into a buffer
    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file);
    printf("Second-to-last line: %s\n", line);

    fclose(file);
    sscanf(line,"%d", &id);
    printf("%d", id);
    return 0;
}
