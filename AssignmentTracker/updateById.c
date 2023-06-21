#include<stdio.h>
void main(){
    char sem[50],subject[50],work[50],status[50],year[50];
    // int day,year,month;
     FILE *originalFile = fopen("files/storeAssignment.txt", "r");
    // if (originalFile == NULL) {
    //     printf("Unable to open the file.\n");
    //     return 1;
    // }

    // FILE *newFile = fopen("files/tempfile.txt", "w");
    // if (newFile == NULL) {
    //     printf("Unable to create the temporary file.\n");
    //     fclose(originalFile);
    //     return 1;
    // }

    char buffer[1000];
    char combined[100];
    int fileId;
    // Read lines from the original file and write to the new file, skipping the specified line
    while (fgets(buffer, sizeof(buffer), originalFile) != NULL) {
        sscanf(buffer,"%d,%[^,],%[^,],%[^,],%[^,],%s",&fileId,sem,subject,work,year,status);
        if(fileId ==3){
            sprintf(combined, "%d,%s,%s,%s,%s,Done",fileId,sem,subject,work,year,status);
            printf("%s", combined);
        }
        // else{
        //     fputs(buffer, newFile);
        // }
        
    }

    fclose(originalFile);
    // fclose(newFile);

    // Remove the original file
    // if (remove("files/storeAssignment.txt") == 0) {
    //     // Rename the new file to the original filename
    //     if (rename("files/tempfile.txt", "files/storeAssignment.txt") != 0) {
    //         printf("Unable to rename the temporary file.\n");
    //         return 1;
    //     }
    //     printf("Line %d deleted successfully.\n", fileId);
    //     // destroyWindow(window);
    // } else {
    //     printf("Unable to delete the original file.\n");
    //     return 1;
    // }
}
