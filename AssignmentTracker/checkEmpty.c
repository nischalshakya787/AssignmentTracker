#include <stdio.h>

int main() {
    // Open the file in read mode
    FILE* file = fopen("files/storeAssignment.txt", "r");

    // Check if the file exists
    if (file == NULL) {
        printf("File does not exist.\n");
        return 1;
    }

    // Move the file position indicator to the end of the file
    fseek(file, 0, SEEK_END);

    // Get the current position of the file position indicator
    long fileSize = ftell(file);

    // Check if the file size is 0
    if (fileSize == 0) {
        printf("File is empty.\n");
    } else {
        printf("File is not empty.\n");
    }

    // Close the file
    fclose(file);

    return 0;
}