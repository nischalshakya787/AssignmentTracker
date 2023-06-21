#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *originalFile = fopen("files/storeAssignment.txt", "r");
    if (originalFile == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    FILE *newFile = fopen("tempfile.txt", "w");
    if (newFile == NULL) {
        printf("Unable to create the temporary file.\n");
        fclose(originalFile);
        return 1;
    }

    int id = 5;  // Line number to delete (example: delete line 3)

    int currentLine = 1;
    char buffer[1000];
    int fileId;
    // Read lines from the original file and write to the new file, skipping the specified line
    while (fgets(buffer, sizeof(buffer), originalFile) != NULL) {
        sscanf(buffer,"%d",&fileId);
        if(fileId !=id){
            printf("%s",buffer);
        }
        
    }

    fclose(originalFile);
    fclose(newFile);

    // Remove the original file
    if (remove("files/storeAssignment.txt") == 0) {
        // Rename the new file to the original filename
        if (rename("files/tempfile.txt", "files/storeAssignment.txt") != 0) {
            printf("Unable to rename the temporary file.\n");
            return 1;
        }
        printf("Id %d deleted successfully.\n", id);
    } else {
        printf("Unable to delete the original file.\n");
        return 1;
    }

    return 0;
}
