#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <time.h>
#include "files/combolist.c"
#define MAX_LINE_LENGTH 256

int total=0,pending=0,completed=0,filtersno = 0,subFlag = 0;
GtkWidget *window;
GtkWidget *box, *container, *comboSubject, *comboSemester, *entry, *frame, *label, *calendar, *button,*vbox,*checkButton,*filterbox,*filter,*filter2;
char* Subject[100]={"Default"};
char *filterBySuject[2] = {"NULL"};
char date_string[11];
char widget_name[15];
char *btn_widget_name[5]={"Defualt"};
struct Assignment
{
    int id;
    char semester[50];
    char subject[50];
    char work[50];
    char date[50];
    char status[50];
};

static void filterList(GtkWidget *combo){
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "All");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Submitted");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "UnSubmitted");
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo), "Subject");
}

static void destroyWindow(GtkWidget *window){
    gtk_window_set_child(GTK_WINDOW(window), NULL);
}

//To load the css file.
static void loadCss(){
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, "files/style.css");
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

}
void getDateToday(){
    time_t now;
    time(&now);

    // Convert the current time to a local time structure
    struct tm *local_time = localtime(&now);
    

   sprintf(date_string, "%04d/%02d/%02d", local_time->tm_year + 1900, local_time->tm_mon + 1,local_time->tm_mday);
}
time_t dateToTimestamp(const char* date_str) {
    struct tm date = {0};
    sscanf(date_str, "%d/%d/%d", &date.tm_year, &date.tm_mon, &date.tm_mday);
    date.tm_year -= 1900; // Adjust year since 1900
    date.tm_mon -= 1; // Adjust month (0-based index)
    return mktime(&date) / (60 * 60 * 24); // Divide by (60 seconds * 60 minutes * 24 hours) to get days
}
int isUnique(char *str, int num){
   for(int i=0;i<num;i++){
        if(strcmp(Subject[i],str)==0){
            return 0;// String is not unique
        }
    }
   return 1;//string is unique
}
static void filterSub(GtkWidget *combo, gpointer user_data){
    GtkComboBoxText *combo_Filter = GTK_COMBO_BOX_TEXT(filter2);
    gchar *subjectFilter = gtk_combo_box_text_get_active_text(combo_Filter);
    filterBySuject[0] = subjectFilter;
    filtersno = 3;
    destroyWindow(window);
    homePage();
}
static void filterSubjectSelection(GtkWidget *combo, gpointer user_data){
    GtkComboBoxText *combo_Filter= GTK_COMBO_BOX_TEXT(filter);
    gchar *selectedFilter = gtk_combo_box_text_get_active_text(combo_Filter);

    if(strcmp(selectedFilter,"Subject") == 0 ){
        int count =0;
        FILE *fp = fopen("files/storeAssignment.txt","r");
        struct Assignment assignment[100];
        int record=0;
        while(!feof(fp)){
                    fscanf(fp,"%d, %50[^,],%50[^,],%50[^,],%50[^,],%50[^\n]\n",&assignment[record].id,assignment[record].semester,assignment[record].subject, assignment[record].work, assignment[record].date,assignment[record].status);
                    if(isUnique(assignment[record].subject,record)){//This function returns 1 or 0 and below process will only store unique subjects.
                        Subject[record] = assignment[record].subject; //We are appending the array
                        record++;
                    }
        }
        fclose(fp);
        // while (Subject[count] != NULL) {
        //     count++;
        // }
        // for(int i=0;i<count;i++){
        //     printf("%d. %s\n",i+1, Subject[i]);
        // }
        // for(int i=0;i<count;i++){
        //     gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (filter2), Subject[i]);
        // }
        subFlag = 1;// To make subject selected in homepage if subject is selected.
        destroyWindow(window);
        homePage();
        
        
    }
    else if(strcmp(selectedFilter,"Submitted") == 0){
        subFlag = 0;//Resets the suject selected
        filtersno = 1;
        destroyWindow(window);
        homePage();
    }
    else if(strcmp(selectedFilter,"UnSubmitted") == 0){
        subFlag = 0;//Resets the suject selected
        filtersno = 2;
        destroyWindow(window);
        homePage();
    }
    
    else if(strcmp(selectedFilter,"All") == 0){
        subFlag = 0;//Resets the suject selected
        filtersno = 0;
        destroyWindow(window);
        homePage();
    }
}
static void checkInfo(){
    total=0,pending=0,completed=0;
    FILE *fp = fopen("files/storeAssignment.txt","r");
        int record = 0;
        struct Assignment assignment[100];
        while(!feof(fp)){
            fscanf(fp,"%d, %50[^,],%50[^,],%50[^,],%50[^,],%50[^\n]\n",&assignment[record].id,assignment[record].semester,assignment[record].subject, assignment[record].work, assignment[record].date,assignment[record].status);
            total++;
            if(strcmp(assignment[record].status,"Done")==0){
                completed++; 
                record++;
            }
            else{
                pending++;
                record++;
            }
        }
        fclose(fp);
}
static void semSelection(GtkWidget *combo, gpointer user_data){
    GtkComboBoxText *combo_semSelction = GTK_COMBO_BOX_TEXT(comboSemester);
    gchar *selectedSemester = gtk_combo_box_text_get_active_text(combo_semSelction);
    if(strcmp(selectedSemester,"Semester I") == 0 ){
        gtk_combo_box_text_remove_all(user_data);
        SemesterI(user_data);
    }
    else if(strcmp(selectedSemester,"Semester II") == 0 ){
        gtk_combo_box_text_remove_all(user_data);
        SemesterII(user_data);
    }
    else if(strcmp(selectedSemester,"Semester III") == 0 ){
        gtk_combo_box_text_remove_all(user_data);
        SemesterIII(user_data);
    }
    else if(strcmp(selectedSemester,"Semester IV") == 0 ){
        gtk_combo_box_text_remove_all(user_data);
        SemesterIV(user_data);
    }
    else if(strcmp(selectedSemester,"Semester V") == 0 ){
        gtk_combo_box_text_remove_all(user_data);
        SemesterV(user_data);
    }
    else if(strcmp(selectedSemester,"Semester VI") == 0 ){
        gtk_combo_box_text_remove_all(user_data);
        SemesterVI(user_data);
    }
    else if(strcmp(selectedSemester,"Semester VII") == 0 ){
        gtk_combo_box_text_remove_all(user_data);
        SemesterVII(user_data);
    }
    else if(strcmp(selectedSemester,"Semester VIII") == 0 ){
        gtk_combo_box_text_remove_all(user_data);
        SemesterVIII(user_data);
    }
}



static void createLabel(GtkWidget *parentContainer, gchar *labelText, gchar *name, int xalign){
    label = gtk_label_new(labelText);
    gtk_widget_set_name(label,name);
    if(xalign){
        gtk_label_set_xalign(GTK_LABEL(label), 0);
    }
    gtk_box_append(GTK_BOX(parentContainer), label);
}

static void createButton(GtkWidget *parentContainer, gchar *labelText, gchar *name, GCallback callback, gpointer data){
    button = gtk_button_new_with_label(labelText);
    gtk_widget_set_name(button,name);
    gtk_box_append(GTK_BOX(parentContainer),button);
    g_signal_connect(button, "clicked", callback, data);
}
static void labelInGrid(GtkWidget *mainGrid, gchar *labelText, gchar *name, int col, int row){
    label = gtk_label_new(labelText);
    gtk_grid_attach(GTK_GRID(mainGrid),label,col,row,1,1);
    gtk_widget_set_name(label, name);
}
static void createCheckBox(GtkWidget *parentContainer,gchar *name,GCallback callback, gpointer data,int active){
    checkButton = gtk_check_button_new();
    gtk_box_append(GTK_BOX(parentContainer), checkButton);
    gtk_widget_set_name(checkButton,name);

    g_signal_connect(checkButton,"toggled", callback ,data);

    if(active==1){
        gtk_check_button_set_active(checkButton, 1);
    }
    else{
        gtk_check_button_set_active(checkButton, 0);
    }
}
int file_exists(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    int is_exist = 0;
    if (fp != NULL)
    {
        is_exist = 1;
        fclose(fp); // close the file
    }
    return is_exist;
}
int isFileEmpty(const char *filename) {
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        perror("Error opening file");
        return -1; // Return -1 to indicate an error
    }
    
    fseek(file, 0, SEEK_END); // Move the file pointer to the end of the file
    long file_size = ftell(file); // Get the current file pointer position (file size)
    fclose(file); // Close the file
    
    return file_size == 0; // Return 1 if file_size is 0 (empty), otherwise return 0 (not empty)
}
int getLastIdSubmitted(){
    // Count the number of lines in the file
        int id;
        const char *filename = "files/externfile/submittedAssignment.txt";
        int result = isFileEmpty(filename);
        FILE *file = fopen(filename, "r");
        int lineCount = 0;
        char ch;
        if (result == -1) {
            printf("Failed to open the file or file does not exist.\n");
        } else if (result) {
            fclose(file);
            return 0;
        } else {
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

        sscanf(line,"%d\n", &id);
        printf("Id: %d\n", id);

        return id;
        }
        
}
int getLastId(){
    // Count the number of lines in the file
        int id;
        FILE *file = fopen("files/storeAssignment.txt", "r");
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

        sscanf(line,"%d\n", &id);
        printf("Id: %d\n", id);

        return id;
}

int lastId(){
    int id;
    FILE *file = fopen("files/storeAssignment.txt", "r");
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
        id=0;
        return id;
    } 

    else {//else will work if the file is not empty.
        id = getLastId();
    }
    fclose(file);
    
    return id;
}
static void deleteInfoHistory(int idDel){
    FILE *originalFile = fopen("files/externfile/submittedAssignment.txt","r");
    if (originalFile == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    FILE *newFile = fopen("files/externfile/tempfile.txt", "w");
    if (newFile == NULL) {
        printf("Unable to create the temporary file.\n");
        fclose(originalFile);
        return 1;
    }
    int id = idDel;  // Id To be deleted.

    char buffer[1000];
    int fileId;
    // Read lines from the original file and write to the new file, skipping the specified line
    while (fgets(buffer, sizeof(buffer), originalFile) != NULL) {
        sscanf(buffer,"%d",&fileId);
        if(fileId !=id){
            fputs(buffer, newFile);
        }
        
    }

    fclose(originalFile);
    fclose(newFile);

    // Remove the original file
    if (remove("files/externfile/submittedAssignment.txt") == 0) {
        // Rename the new file to the original filename
        if (rename("files/externfile/tempfile.txt", "files/externfile/submittedAssignment.txt") != 0) {
            printf("Unable to rename the temporary file.\n");
        }
        printf("Id %d deleted successfully.\n", fileId);
        destroyWindow(window);
    } else {
        printf("Unable to delete the original file.\n");
    }
}

static void deleteInfo(int idDel){
    FILE *originalFile = fopen("files/storeAssignment.txt", "r");
    if (originalFile == NULL) {
        printf("Unable to open the file.\n");
        return 1;
    }

    FILE *newFile = fopen("files/tempfile.txt", "w");
    if (newFile == NULL) {
        printf("Unable to create the temporary file.\n");
        fclose(originalFile);
        return 1;
    }
    int id = idDel;  // Id To be deleted.

    char buffer[1000];
    int fileId;
    // Read lines from the original file and write to the new file, skipping the specified line
    while (fgets(buffer, sizeof(buffer), originalFile) != NULL) {
        sscanf(buffer,"%d",&fileId);
        if(fileId !=id){
            fputs(buffer, newFile);
        }
        
    }

    fclose(originalFile);
    fclose(newFile);

    // Remove the original file
    if (remove("files/storeAssignment.txt") == 0) {
        // Rename the new file to the original filename
        if (rename("files/tempfile.txt", "files/storeAssignment.txt") != 0) {
            printf("Unable to rename the temporary file.\n");
        }
        printf("Id %d deleted successfully.\n", fileId);
        destroyWindow(window);
    } else {
        printf("Unable to delete the original file.\n");
    }
}

static void func_call(GtkWidget *label , gpointer user_data){
    gchar *text = gtk_label_get_text(user_data);// stores the label in text variable i.e id that is to be deleted.
    int num = atoi(text); //converts str into int
    deleteInfo(num); //main function for deleting the specific line
    homePage();
}
static void func_callHistory(GtkWidget *label , gpointer user_data){
    gchar *text = gtk_label_get_text(user_data);// stores the label in text variable i.e id that is to be deleted.
    int num = atoi(text); //converts str into int
    deleteInfoHistory(num); //main function for deleting the specific line
    Page_3();
}

void unsubmitAssignment(int id){
    char sem[50],subject[50],work[50],status[50],year[50];
     FILE *originalFile = fopen("files/storeAssignment.txt", "r");
    if (originalFile == NULL) {
        printf("Unable to open the file.\n");
    }

    FILE *newFile = fopen("files/tempfile.txt", "w");
    if (newFile == NULL) {
        printf("Unable to create the temporary file.\n");
        fclose(originalFile);
    }

    char buffer[1000];
    char combined[1000];
    int fileId;
    // Read lines from the original file and write to the new file, skipping the specified line
    
    while (fgets(buffer, sizeof(buffer), originalFile) != NULL) {
        sscanf(buffer,"%d,%[^,],%[^,],%[^,],%[^,],%s",&fileId,sem,subject,work,year,status);
        if(fileId ==id){
            sprintf(combined, "%d,%s,%s,%s,%s,Pending\n",fileId,sem,subject,work,year);
            fputs(combined,newFile);
        }
        else{
            fputs(buffer, newFile);
        }
        
    }

    fclose(originalFile);
    fclose(newFile);

    // Remove the original file
    if (remove("files/storeAssignment.txt") == 0) {
        // Rename the new file to the original filename
        if (rename("files/tempfile.txt", "files/storeAssignment.txt") != 0) {
            printf("Unable to rename the temporary file.\n");
        }
        printf("Id %d successfully.\n", fileId);
        destroyWindow(window);
        homePage();
    } else {
        printf("Unable to delete the original file.\n");
    }
}
void storeHistory(char submitted[100]){
    FILE *file = fopen("files/externfile/submittedAssignment.txt","a");
    fprintf(file,"%s",submitted);
    fclose(file);
}
void addWithDate(char submitted[100],int submittedId){
    char sem[50],subject[50],work[50],status[50],year[50];
     FILE *file = fopen("files/externfile/submittedAssignment.txt","r");
     
     printf("%s\n", submitted);
     char buffer[1000];
     int fileId;
     int flag = 1;
     int id = getLastIdSubmitted();

     while (fgets(buffer, sizeof(buffer), file) != NULL) {
        sscanf(buffer,"%d,%[^,],%[^,],%[^,],%[^,],%s",&fileId,sem,subject,work,year,status);
        if(submittedId == fileId){
            flag = 0;
            break;
        }
     }
     if(flag == 1){
        storeHistory(submitted);
     }
    fclose(file);
}
void submitAssignment(int id){
    char sem[50],subject[50],work[50],status[50],year[50];
    FILE *originalFile = fopen("files/storeAssignment.txt", "r");
   
    if (originalFile == NULL) {
        printf("Unable to open the file.\n");
    }
    FILE *newFile = fopen("files/tempfile.txt", "w");
    // FILE *newFile1 = fopen("files/externfile/tempfile.txt","w");
    if (newFile == NULL) {
        printf("Unable to create the temporary file.\n");
        fclose(originalFile);
    }
    char submitted[1000];
    
    char buffer[1000];
    char combined[1000];
    char date[50];
    int fileId;
    // Read lines from the original file and write to the new file, skipping the specified line
    while (fgets(buffer, sizeof(buffer), originalFile) != NULL) {
        sscanf(buffer,"%d,%[^,],%[^,],%[^,],%[^,],%s",&fileId,sem,subject,work,year,status);
        if(fileId ==id){
            sprintf(combined, "%d,%s,%s,%s,%s,Done\n",fileId,sem,subject,work,year);
            sprintf(submitted,"%d,%s,%s,%s,%s,Done,%s\n",fileId,sem,subject,work,year,date_string);
            addWithDate(submitted,fileId);
            fputs(combined,newFile);
        }
        else{
            fputs(buffer, newFile);
        }
        
    }
    fclose(originalFile);

    // fclose(newFile1);
    fclose(newFile);
    if (remove("files/storeAssignment.txt") == 0) {
        // Rename the new file to the original filename
        if (rename("files/tempfile.txt", "files/storeAssignment.txt") != 0) {
            printf("Unable to rename the temporary file.\n");
        }
        printf("Id %d successfully.\n", fileId);
        destroyWindow(window);
        homePage();
    } else {
        printf("Unable to delete the original file.\n");
    }
}

void checkTask(GtkToggleButton *checkButton, gpointer data){
    gboolean status = gtk_check_button_get_active(checkButton);
    printf("Status = %d\n",status);

    gchar *text = gtk_label_get_text(data);
    int numId = atoi(text);
    printf("Id: %d\n",numId);
    if (status==1){
    // if(status){
        // printf("Btn clicked");
        submitAssignment(numId);
    }
    else{
        unsubmitAssignment(numId);
    }
    
}

static void addWork(){
    FILE *fp;
    int id;
    gchar *textbuffer = gtk_entry_get_buffer(entry);
    const char *assignment = gtk_entry_buffer_get_text(textbuffer);

    GDateTime *date = gtk_calendar_get_date(calendar);
    gint year = g_date_time_get_year(date);
    gint month = g_date_time_get_month(date);
    gint day = g_date_time_get_day_of_month(date);

    GtkComboBoxText *combo_box_text = GTK_COMBO_BOX_TEXT(comboSubject);
    gchar *subject = gtk_combo_box_text_get_active_text(combo_box_text);

    GtkComboBoxText *semseter_text = GTK_COMBO_BOX_TEXT(comboSemester);
    gchar *semester = gtk_combo_box_text_get_active_text(semseter_text);


    char *filename = "files/storeAssignment.txt";
    int i=0;
    if(file_exists(filename)){
        fp = fopen("files/storeAssignment.txt","a");
        id = lastId() + 1;// Fetches the Id of last line
    }
    else{
        fp = fopen("files/storeAssignment.txt","w");
        id = 1;
    }
    if(semester == NULL || subject == NULL || strlen(assignment) == 0){
        printf("Any field can't be Empty");
    }
    else{
        fprintf(fp,"%d,%s,%s,%s,%d/%d/%d,Pending\n",id,semester,subject, assignment, year,month,day);
    }
    
    //clears input box after clicking.
    gtk_entry_buffer_set_text(textbuffer," ", -1);
    // //clears dropdown after clicking.
    // gtk_combo_box_set_active(GTK_COMBO_BOX(comboSemester), -1);
    gtk_combo_box_set_active(GTK_COMBO_BOX(comboSubject), -1);
    fclose(fp);
}

static void displayAssignment(GtkWidget *parentContainer){
    FILE *fp = fopen("files/storeAssignment.txt","r");
    int record = 0,sno;
    char snoStr[100],id[100];
    // Check if the file exists
    if (fp == NULL) {
        printf("File does not exist.\n");
    }

    // Move the file position indicator to the end of the file
    fseek(fp, 0, SEEK_END);

    // Get the current position of the file position indicator
    long fileSize = ftell(fp);
    // Check if the file size is 0
    fclose(fp);
    if (fileSize == 0) {
        GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
        gtk_grid_attach(parentContainer,box,2,1,1,1);
        createLabel(box,"Nothing to Show!!! ","nothing-box",0);
    }
    else {
        FILE *fp = fopen("files/storeAssignment.txt","r");
        struct Assignment assignment[100];
        int record = 0,sno;
        char snoStr[100],id[100],daysRemaining[30];
        int row = 1;
        while(!feof(fp)){
            int col = 0;
            fscanf(fp,"%d, %50[^,],%50[^,],%50[^,],%50[^,],%50[^\n]\n",&assignment[record].id,assignment[record].semester,assignment[record].subject, assignment[record].work, assignment[record].date,assignment[record].status);
            sno = record + 1;
            sprintf(snoStr,"%d. ",sno);//converting integer to string
            sprintf(id,"%d",assignment[record].id);
            time_t dateToday = dateToTimestamp(date_string);
            time_t dueDate = dateToTimestamp(assignment[record].date);
    
            int daysRemainingInt = dueDate - dateToday; // Use labs to get the absolute difference
            sprintf(daysRemaining, "%d", daysRemainingInt);
            GtkWidget *elementId = gtk_label_new(id);
            if(daysRemainingInt<0){
                strcpy(widget_name,"label-overdue");
                btn_widget_name[0] = "check-btn-od";
                btn_widget_name[1] = "delete-btn-od";
            }
            else{
                strcpy(widget_name,"label");
                btn_widget_name[0] = "check-btn-nd";
                btn_widget_name[1] = "delete-btn-nd";
                
            }
            if(filtersno ==0){
                if(strcmp(assignment[record].status,"Done")==0){
                    GtkWidget *check = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
                    gtk_widget_set_name(check, "check-btn-d");
                    gtk_grid_attach(GTK_GRID(parentContainer),check,col,row,1,1);
                    createCheckBox(check,"check-btn",G_CALLBACK(checkTask),elementId,1);
                    col++;
                    labelInGrid(parentContainer,assignment[record].subject,"label-submit",col,row);
                    col++;
                    labelInGrid(parentContainer,assignment[record].work,"label-submit",col,row);
                    col++;
                    labelInGrid(parentContainer,assignment[record].date,"label-submit",col,row);
                    col++;
                    labelInGrid(parentContainer,"Submitted","label-submit",col,row);
                    col++;
                    GtkWidget *checkAndDel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
                    gtk_grid_attach(GTK_GRID(parentContainer),checkAndDel,col,row,1,1);
                    gtk_widget_set_name(checkAndDel, "check-btn-d");

                    createButton(checkAndDel,"x","delete-btn-d",G_CALLBACK(func_call),elementId);
                    }
                else{
                    GtkWidget *check = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
                    gtk_widget_set_name(check, btn_widget_name[0]);
                    gtk_grid_attach(GTK_GRID(parentContainer),check,col,row,1,1);
                    createCheckBox(check,"check-btn",G_CALLBACK(checkTask),elementId,0);
                    col++;
                    labelInGrid(parentContainer,assignment[record].subject,widget_name,col,row);
                    col++;
                    labelInGrid(parentContainer,assignment[record].work,widget_name,col,row);
                    col++;
                    labelInGrid(parentContainer,assignment[record].date,widget_name,col,row);
                    col++;
                    labelInGrid(parentContainer,daysRemaining,widget_name,col,row);
                    col++;
                    GtkWidget *checkAndDel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
                    gtk_grid_attach(GTK_GRID(parentContainer),checkAndDel,col,row,1,1);
                    gtk_widget_set_name(checkAndDel, btn_widget_name[0]);

                    // createCheckBox(checkAndDel,G_CALLBACK(checkTask),elementId,0);
                    createButton(checkAndDel,"x",btn_widget_name[1],G_CALLBACK(func_call),elementId); //button that deletes the specific id from file.
                }
                record = record + 1;
                row++;
            }
            else if(filtersno==1){
                if(strcmp(assignment[record].status,"Done")==0){
                    
                    GtkWidget *check = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
                    gtk_widget_set_name(check, "check-btn-d");
                    gtk_grid_attach(GTK_GRID(parentContainer),check,col,row,1,1);
                    createCheckBox(check,"check-btn",G_CALLBACK(checkTask),elementId,1);
                    col++;
                    labelInGrid(parentContainer,assignment[record].subject,"label-submit",col,row);
                    col++;
                    labelInGrid(parentContainer,assignment[record].work,"label-submit",col,row);
                    col++;
                    labelInGrid(parentContainer,assignment[record].date,"label-submit",col,row);
                    col++;
                    labelInGrid(parentContainer,"Submitted","label-submit",col,row);
                    col++;
                    GtkWidget *checkAndDel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
                    gtk_grid_attach(GTK_GRID(parentContainer),checkAndDel,col,row,1,1);
                    gtk_widget_set_name(checkAndDel, "check-btn-d");
                    // createCheckBox(checkAndDel,G_CALLBACK(checkTask),elementId,0);
                    createButton(checkAndDel,"x","delete-btn-d",G_CALLBACK(func_call),elementId);//button that deletes the specific id from file.
                    
                record = record + 1;
                row++;
                }
            }
            else if(filtersno==2){
                if(strcmp(assignment[record].status,"Pending")==0){
                    GtkWidget *check = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
                    gtk_widget_set_name(check, btn_widget_name[0]);
                    gtk_grid_attach(GTK_GRID(parentContainer),check,col,row,1,1);
                    createCheckBox(check,"check-btn",G_CALLBACK(checkTask),elementId,0);
                    col++;
                    labelInGrid(parentContainer,assignment[record].subject,widget_name,col,row);
                    col++;
                    labelInGrid(parentContainer,assignment[record].work,widget_name,col,row);
                    col++;
                    labelInGrid(parentContainer,assignment[record].date,widget_name,col,row);
                    col++;
                    labelInGrid(parentContainer,daysRemaining,widget_name,col,row);
                    col++;
                    GtkWidget *checkAndDel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
                    gtk_grid_attach(GTK_GRID(parentContainer),checkAndDel,col,row,1,1);
                    gtk_widget_set_name(checkAndDel, btn_widget_name[0]);

                    createButton(checkAndDel,"x",btn_widget_name[1],G_CALLBACK(func_call),elementId);//button that deletes the specific id from file.
                
                // printf("%d. Subject = %s \t Work = %s \t Date = %s\n", record + 1, assignment[record].subject,assignment[record].work,assignment[record].date );
                record = record + 1;
                row++;
                }
            }
            else if(filtersno==3){
                if(strcmp(assignment[record].subject,filterBySuject[0])==0){
                    if(strcmp(assignment[record].status,"Done")==0){
                    GtkWidget *check = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
                    gtk_widget_set_name(check, "check-btn-d");
                    gtk_grid_attach(GTK_GRID(parentContainer),check,col,row,1,1);
                    createCheckBox(check,"check-btn",G_CALLBACK(checkTask),elementId,1);
                    col++;
                    labelInGrid(parentContainer,assignment[record].subject,"label-submit",col,row);
                    col++;
                    labelInGrid(parentContainer,assignment[record].work,"label-submit",col,row);
                    col++;
                    labelInGrid(parentContainer,assignment[record].date,"label-submit",col,row);
                    col++;
                    labelInGrid(parentContainer,"Submitted","label-submit",col,row);
                    col++;
                    GtkWidget *checkAndDel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
                    gtk_grid_attach(GTK_GRID(parentContainer),checkAndDel,col,row,1,1);
                    gtk_widget_set_name(checkAndDel, "check-btn-d");

                    createButton(checkAndDel,"x","delete-btn-d",G_CALLBACK(func_call),elementId);
                    }
                else{
                    GtkWidget *check = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
                    gtk_widget_set_name(check, btn_widget_name[0]);
                    gtk_grid_attach(GTK_GRID(parentContainer),check,col,row,1,1);
                    createCheckBox(check,"check-btn",G_CALLBACK(checkTask),elementId,0);
                    col++;
                    labelInGrid(parentContainer,assignment[record].subject,widget_name,col,row);
                    col++;
                    labelInGrid(parentContainer,assignment[record].work,widget_name,col,row);
                    col++;
                    labelInGrid(parentContainer,assignment[record].date,widget_name,col,row);
                    col++;
                    labelInGrid(parentContainer,daysRemaining,widget_name,col,row);
                    col++;
                    GtkWidget *checkAndDel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
                    gtk_grid_attach(GTK_GRID(parentContainer),checkAndDel,col,row,1,1);
                    gtk_widget_set_name(checkAndDel, btn_widget_name[0]);

                    // createCheckBox(checkAndDel,G_CALLBACK(checkTask),elementId,0);
                    createButton(checkAndDel,"x",btn_widget_name[1],G_CALLBACK(func_call),elementId); //button that deletes the specific id from file.
                }
                record = record + 1;
                row++;
                }
            }
        }
        fclose(fp);
    }
}
static void displayHistory(GtkWidget *parentContainer){
    FILE *fp = fopen("files/externfile/submittedAssignment.txt","r");
    int record = 0,sno;
    char snoStr[100],id[100];
    // Check if the file exists
    if (fp == NULL) {
        printf("File does not exist.\n");
    }

    // Move the file position indicator to the end of the file
    fseek(fp, 0, SEEK_END);

    // Get the current position of the file position indicator
    long fileSize = ftell(fp);
    // Check if the file size is 0
    fclose(fp);
    if (fileSize == 0) {
        GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
        gtk_grid_attach(parentContainer,box,2,1,1,1);
        createLabel(box,"Nothing to Show!!! ","nothing-box",0);
    }
    else {
        FILE *fp = fopen("files/externfile/submittedAssignment.txt","r");
        int historyid;
        char sem[30],subject[50],work[50],due[15],status[10],date[15];
        int record = 0,sno;
        char snoStr[100],id[100];
        int row = 1;
        while(!feof(fp)){
            int col = 0;
            fscanf(fp,"%d, %50[^,],%50[^,],%50[^,],%50[^,],%50[^,],%50[^\n]\n",&historyid,sem,subject, work, due,status,date);
            sno = record + 1;
            sprintf(snoStr,"%d. ",sno);//converting integer to string
            sprintf(id,"%d",historyid);

            GtkWidget *elementId = gtk_label_new(id);
            labelInGrid(parentContainer,snoStr,"label",col,row);
            col++;
            labelInGrid(parentContainer,subject,"label",col,row);
            col++;
            labelInGrid(parentContainer,work,"label",col,row);
            col++;
            labelInGrid(parentContainer,due,"label",col,row);
            col++;
            labelInGrid(parentContainer,date,"label",col,row);
            col++;
            GtkWidget *checkAndDel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
            gtk_grid_attach(GTK_GRID(parentContainer),checkAndDel,col,row,1,1);
            gtk_widget_set_name(checkAndDel, "check-btn-nd");
            createButton(checkAndDel,"x","delete-btn-nd",G_CALLBACK(func_callHistory),elementId);
            record = record + 1;
            row++;
            }
        }
        fclose(fp);
}

void go_back_pg_2(){
    destroyWindow(window);
    Page_2();
}

void go_to_homepage(){
    destroyWindow(window);
    homePage();
}
void go_to_page3(){
    destroyWindow(window);
    Page_3();
}
void Page_3(){
    //-----------------------------CONTAINER------------------------------------------//
    checkInfo();
    // Get the current time
    getDateToday();
    
    char strTotal[5],strCompleted[5],strPending[5];
    //converting the total, pending and completed works into string to display in label.
    sprintf(strTotal, "%d", total);
    sprintf(strCompleted, "%d", completed);
    sprintf(strPending, "%d", pending);

    container = gtk_box_new(GTK_ORIENTATION_VERTICAL,3);
    gtk_widget_set_name(container, "container");

    gtk_window_set_child(GTK_WINDOW(window), container);
    
    GtkWidget *box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_box_append(GTK_BOX(container), box);
    gtk_box_set_homogeneous(GTK_BOX(box), TRUE);

    //--------------IMAGE---------------//
    GtkWidget *box2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box), box2);
    gtk_widget_set_halign(box2, GTK_ALIGN_START);
    

    GtkWidget *image = gtk_image_new_from_file("img/img.jpg");
    gtk_image_set_pixel_size(GTK_IMAGE(image), 55);
    gtk_box_append(GTK_BOX(box2), image);
    gtk_widget_set_name(image, "image");

    createLabel(box2, "Student's HandBook","title",0);

    GtkWidget *minibox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 2);
    gtk_box_append(GTK_BOX(box), minibox);
    gtk_widget_set_halign(minibox, GTK_ALIGN_END);
    gtk_widget_set_name(minibox, "minibox");
    
    createButton(minibox,"Go Back","button3",G_CALLBACK(go_to_homepage), NULL);
    
    GtkWidget *halign = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
    gtk_box_append(GTK_BOX(container), halign);
    gtk_widget_set_name(halign,"testbox");

    GtkWidget *infoBar =gtk_box_new(GTK_ORIENTATION_VERTICAL,3);
    gtk_box_append(GTK_BOX(halign),infoBar);
    gtk_widget_set_name(infoBar,"box1");

    

    GtkWidget *subInfoBar2 = gtk_box_new(GTK_ORIENTATION_VERTICAL,3);
    gtk_widget_set_name(subInfoBar2,"sub-infobar2");
    gtk_box_append(GTK_BOX(infoBar), subInfoBar2);

    createLabel(subInfoBar2,"Today's Date: ", "InfoDateHead", 0);
    createLabel(subInfoBar2,date_string, "subHead", 0);

    GtkWidget *subInfoBar = gtk_box_new(GTK_ORIENTATION_VERTICAL,3);
    gtk_widget_set_name(subInfoBar,"sub-infobar");
    gtk_box_append(GTK_BOX(infoBar), subInfoBar);

    createLabel(subInfoBar,"Total Work", "InfoHead", 0);
    createLabel(subInfoBar,strTotal, "subInfo0", 0);
    createLabel(subInfoBar,"Due", "InfoHead", 0);
    createLabel(subInfoBar,strPending, "subInfo1", 0);
    createLabel(subInfoBar,"Completed", "InfoHead", 0);
    createLabel(subInfoBar,strCompleted, "subInfo2", 0);

    GtkWidget *subInfoBar3 = gtk_box_new(GTK_ORIENTATION_VERTICAL,3);
    gtk_widget_set_name(subInfoBar3,"sub-infobar");
    gtk_box_append(GTK_BOX(infoBar), subInfoBar3);

    GtkWidget *line = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
    gtk_box_append(GTK_BOX(subInfoBar3), line);
    gtk_widget_set_name(line,"color-info-box");
    createLabel(line," ","circle-1",0);
    createLabel(line,"Submitted Task","color-info",0);

    GtkWidget *line2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
    gtk_widget_set_name(line2,"color-info-box");
    gtk_box_append(GTK_BOX(subInfoBar3), line2);
    createLabel(line2," ","circle-2",0);
    createLabel(line2,"Missed Task","color-info",0);

    GtkWidget *subcontainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_append(GTK_BOX(halign), subcontainer);
    gtk_widget_set_name(subcontainer,"box2");   

    createLabel(subcontainer,"Submission History","title",0);
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_box_append(GTK_BOX(subcontainer), vbox);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_name(grid,"table");
    gtk_box_append(GTK_BOX(vbox), grid);

    // Add widgets to the table
    GtkWidget *label1 = gtk_label_new(" ");
    gtk_grid_attach(GTK_GRID(grid), label1, 0, 0, 1, 1);
    gtk_widget_set_name(label1,"subcontainer-title");

    GtkWidget *label2 = gtk_label_new("Subject");
    gtk_grid_attach(GTK_GRID(grid), label2, 1, 0, 1, 1);
    gtk_widget_set_name(label2,"subcontainer-title");

    GtkWidget *label3 = gtk_label_new("Assignment");
    gtk_grid_attach(GTK_GRID(grid), label3, 2, 0, 1, 1);
    gtk_widget_set_name(label3,"subcontainer-title");

    GtkWidget *label4 = gtk_label_new("Due Date");
    gtk_grid_attach(GTK_GRID(grid), label4, 3, 0, 1, 1);
    gtk_widget_set_name(label4,"subcontainer-title");

    GtkWidget *label6 = gtk_label_new("Submitted Date");
    gtk_grid_attach(GTK_GRID(grid), label6, 4, 0, 1, 1);
    gtk_widget_set_name(label6,"subcontainer-title");

    GtkWidget *label5 = gtk_label_new(" ");
    gtk_grid_attach(GTK_GRID(grid), label5, 5, 0, 1, 1);
    gtk_widget_set_name(label5,"subcontainer-title");

    displayHistory(grid);
    
    printf("%d", filtersno);
    gtk_window_present(GTK_WINDOW(window));
}
void homePage(){
    //-----------------------------CONTAINER------------------------------------------//
    checkInfo();
    // Get the current time
    getDateToday();
    
    char strTotal[5],strCompleted[5],strPending[5];
    //converting the total, pending and completed works into string to display in label.
    sprintf(strTotal, "%d", total);
    sprintf(strCompleted, "%d", completed);
    sprintf(strPending, "%d", pending);

    container = gtk_box_new(GTK_ORIENTATION_VERTICAL,3);
    gtk_widget_set_name(container, "container");

    gtk_window_set_child(GTK_WINDOW(window), container);
    
    GtkWidget *box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_box_append(GTK_BOX(container), box);
    gtk_box_set_homogeneous(GTK_BOX(box), TRUE);

    //--------------IMAGE---------------//
    GtkWidget *box2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box), box2);
    gtk_widget_set_halign(box2, GTK_ALIGN_START);
    

    GtkWidget *image = gtk_image_new_from_file("img/img.jpg");
    gtk_image_set_pixel_size(GTK_IMAGE(image), 55);
    gtk_box_append(GTK_BOX(box2), image);
    gtk_widget_set_name(image, "image");

    createLabel(box2, "Student's HandBook","title",0);

    GtkWidget *minibox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 2);
    gtk_box_append(GTK_BOX(box), minibox);
    gtk_widget_set_halign(minibox, GTK_ALIGN_END);
    gtk_widget_set_name(minibox, "minibox");
    
    createButton(minibox,"Submission History","button3",G_CALLBACK(Page_3), NULL);
    
    GtkWidget *halign = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
    gtk_box_append(GTK_BOX(container), halign);
    gtk_widget_set_name(halign,"testbox");

    GtkWidget *infoBar =gtk_box_new(GTK_ORIENTATION_VERTICAL,3);
    gtk_box_append(GTK_BOX(halign),infoBar);
    gtk_widget_set_name(infoBar,"box1");

    

    GtkWidget *subInfoBar2 = gtk_box_new(GTK_ORIENTATION_VERTICAL,3);
    gtk_widget_set_name(subInfoBar2,"sub-infobar2");
    gtk_box_append(GTK_BOX(infoBar), subInfoBar2);

    createLabel(subInfoBar2,"Today's Date: ", "InfoDateHead", 0);
    createLabel(subInfoBar2,date_string, "subHead", 0);

    GtkWidget *subInfoBar = gtk_box_new(GTK_ORIENTATION_VERTICAL,3);
    gtk_widget_set_name(subInfoBar,"sub-infobar");
    gtk_box_append(GTK_BOX(infoBar), subInfoBar);

    createLabel(subInfoBar,"Total Work", "InfoHead", 0);
    createLabel(subInfoBar,strTotal, "subInfo0", 0);
    createLabel(subInfoBar,"Due", "InfoHead", 0);
    createLabel(subInfoBar,strPending, "subInfo1", 0);
    createLabel(subInfoBar,"Completed", "InfoHead", 0);
    createLabel(subInfoBar,strCompleted, "subInfo2", 0);

    GtkWidget *subInfoBar3 = gtk_box_new(GTK_ORIENTATION_VERTICAL,3);
    gtk_widget_set_name(subInfoBar3,"sub-infobar");
    gtk_box_append(GTK_BOX(infoBar), subInfoBar3);

    GtkWidget *line = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
    gtk_box_append(GTK_BOX(subInfoBar3), line);
    gtk_widget_set_name(line,"color-info-box");
    createLabel(line," ","circle-1",0);
    createLabel(line,"Submitted Task","color-info",0);

    GtkWidget *line2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
    gtk_widget_set_name(line2,"color-info-box");
    gtk_box_append(GTK_BOX(subInfoBar3), line2);
    createLabel(line2," ","circle-2",0);
    createLabel(line2,"Missed Task","color-info",0);

    GtkWidget *subcontainer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    gtk_box_append(GTK_BOX(halign), subcontainer);
    gtk_widget_set_name(subcontainer,"box2");   

    GtkWidget *buttonAndFilterContainer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
    gtk_box_append(GTK_BOX(subcontainer), buttonAndFilterContainer);
    gtk_widget_set_name(buttonAndFilterContainer,"btn-filter");
    createButton(buttonAndFilterContainer,"Add Work","btn1",G_CALLBACK(go_back_pg_2),NULL);

    createLabel(buttonAndFilterContainer, "Filter By: ","lbl", 1);//layout funct(BoxToAppend, Title, NameForCss,boolean value for x-align(T))
    filterbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,4);
    gtk_box_append(GTK_BOX(buttonAndFilterContainer),filterbox);
    gtk_widget_set_name(filterbox,"filter-box");
    

    //Label for DropDown/Combobox
    
    //To create a DropDown.
    filter = gtk_combo_box_text_new();
    
    filterList(filter);// This fucntion provides option for DropDown.
    gtk_box_append (GTK_BOX(filterbox), filter);

    
    if(filtersno ==0){//This done to keep on selecting the selected option.
        gtk_combo_box_set_active(GTK_COMBO_BOX(filter), 0);
    }
    else if(filtersno == 1){
        gtk_combo_box_set_active(GTK_COMBO_BOX(filter), 1);
    }
    else if(filtersno == 2){
        gtk_combo_box_set_active(GTK_COMBO_BOX(filter), 2);
    }
    else if(filtersno == 3){
        gtk_combo_box_set_active(GTK_COMBO_BOX(filter), 3);
    }
    if(subFlag == 1){
        printf("heyyy");
        gtk_combo_box_set_active(GTK_COMBO_BOX(filter), 3);
    }

    filter2 = gtk_combo_box_text_new();
    gtk_widget_set_name(filter2,"flt");
    gtk_widget_set_size_request(filter2, 180, -1);
    gtk_widget_set_hexpand(filter2, FALSE);
    gtk_widget_set_vexpand(filter2, FALSE);
    gtk_box_append (GTK_BOX(filterbox), filter2);

    int count = 0;
    while (Subject[count] != NULL) {
        count++;
    }
    for(int i=0;i<count;i++){
        printf("%d. %s\n",i+1, Subject[i]);
    }
    for(int i=0;i<count;i++){
        gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (filter2), Subject[i]);
    }
    g_signal_connect(filter, "changed", G_CALLBACK(filterSubjectSelection),filter2);
    g_signal_connect(filter2,"changed",G_CALLBACK(filterSub),NULL);

    
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_box_append(GTK_BOX(subcontainer), vbox);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_name(grid,"table");
    gtk_box_append(GTK_BOX(vbox), grid);

    // Add widgets to the table
    GtkWidget *label1 = gtk_label_new(" ");
    gtk_grid_attach(GTK_GRID(grid), label1, 0, 0, 1, 1);
    gtk_widget_set_name(label1,"subcontainer-title");

    GtkWidget *label2 = gtk_label_new("Subject");
    gtk_grid_attach(GTK_GRID(grid), label2, 1, 0, 1, 1);
    gtk_widget_set_name(label2,"subcontainer-title");

    GtkWidget *label3 = gtk_label_new("Assignment");
    gtk_grid_attach(GTK_GRID(grid), label3, 2, 0, 1, 1);
    gtk_widget_set_name(label3,"subcontainer-title");

    GtkWidget *label4 = gtk_label_new("Due Date");
    gtk_grid_attach(GTK_GRID(grid), label4, 3, 0, 1, 1);
    gtk_widget_set_name(label4,"subcontainer-title");

    GtkWidget *label6 = gtk_label_new("Time Remaining");
    gtk_grid_attach(GTK_GRID(grid), label6, 4, 0, 1, 1);
    gtk_widget_set_name(label6,"subcontainer-title");

    GtkWidget *label5 = gtk_label_new(" ");
    gtk_grid_attach(GTK_GRID(grid), label5, 5, 0, 1, 1);
    gtk_widget_set_name(label5,"subcontainer-title");

    displayAssignment(grid);
    
    printf("%d", filtersno);
    gtk_window_present(GTK_WINDOW(window));
}

void Page_2(){
    //-----------------------------CONTAINER------------------------------------------//
    //Main box
    container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    gtk_window_set_child (GTK_WINDOW (window), container);
    gtk_style_context_add_class(container, "second-page");
    gtk_widget_set_name(container, "container");

    //-----------------------------HEADER---------------------------------------//
    //Title
    
    GtkWidget *box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 2);
    gtk_box_append(GTK_BOX(container), box);
    gtk_box_set_homogeneous(GTK_BOX(box), TRUE);

    //--------------IMAGE---------------//
    GtkWidget *box2 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(box), box2);
    gtk_widget_set_halign(box2, GTK_ALIGN_START);

    GtkWidget *image = gtk_image_new_from_file("img/img.jpg");
    gtk_image_set_pixel_size(GTK_IMAGE(image), 55);
    gtk_box_append(GTK_BOX(box2), image);
    gtk_widget_set_name(image, "image");
    

    createLabel(box2, "Student's HandBook","title",0); //layout funct(BoxToAppend, Title, NameForCss,boolean value for x-align(F))

    GtkWidget *minibox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 2);
    gtk_box_append(GTK_BOX(box), minibox);
    gtk_widget_set_halign(minibox, GTK_ALIGN_END);
    gtk_widget_set_name(minibox, "minibox");
    
    createButton(minibox,"View Assignment","button2",G_CALLBACK(go_to_homepage), NULL);
    

    //-----------------------------CLOSE HEADER---------------------------------------//
    
    //-----------------------------SUB-MAIN-BODY--------------------------------------//
    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_append(GTK_BOX(container),box);
    gtk_widget_set_name(box, "box");

    //-----------------DROPDOWN-BOX-----------------------//

    //Label for DropDown/Combobox
    createLabel(box, "Select Semester:","sub-title", 1);//layout funct(BoxToAppend, Title, NameForCss,boolean value for x-align(T))
    
    //To create a DropDown.
    comboSemester = gtk_combo_box_text_new();
    gtk_widget_set_name(comboSemester, "combo");
    semesterList(comboSemester);// This fucntion provides option for DropDown.
    gtk_box_append (GTK_BOX(box), comboSemester);
    

    //-----------------DROPDOWN-BOX-----------------------//

    //Label for DropDown/Combobox
    createLabel(box, "Select Subject:", "sub-title",1);//layout funct(BoxToAppend, Title, NameForCss,boolean value for x-align(T))

    //To create a DropDown.
    comboSubject = gtk_combo_box_text_new();
    gtk_widget_set_name(comboSubject, "combo");
    g_signal_connect(comboSemester, "changed", G_CALLBACK(semSelection),comboSubject);
    // printf("%d", *semCondition);
    
    // This fucntion provides option for DropDown.
    gtk_box_append (GTK_BOX(box), comboSubject);

   //-----------------INPUT-BOX-----------------------//
    GtkEntryBuffer *buffer = gtk_entry_buffer_new(NULL, -1);

    //Label for input-box
    createLabel(box, "Enter Your Assignment:", "sub-title", 1);//layout funct(BoxToAppend, Title, NameForCss,boolean value for x-align(T))
    
    //To create a Entry/Input-box
    entry = gtk_entry_new_with_buffer(buffer);
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Your Assignment");
    gtk_widget_set_name(entry, "input-box");
    gtk_box_append(GTK_BOX(box),entry);

   //-----------------CALENDAR-----------------------//

   //Label for calendar.
   createLabel(box, "Select Due Date For Your Assignment:", "sub-title", 1);//layout funct(BoxToAppend, Title, NameForCss,boolean value for x-align(T))
    
    //To create calender
    calendar = gtk_calendar_new();
    gtk_widget_set_name(calendar, "calendar");
    gtk_box_append(GTK_BOX(box),calendar);

    //-----------------BUTTON-----------------------//
    createButton(box,"Add Work", "button1", G_CALLBACK(addWork), NULL);
    //-----------------------------CLOSE-SUB-MAIN-BODY--------------------------------------//

    //-----------------------------CLOSE-CONTAINER------------------------------------------//
    gtk_window_present(GTK_WINDOW(window));
}

static void createWindow(GtkApplication *app, gpointer user_data){
    window = gtk_application_window_new(app);

    gtk_window_set_default_size(GTK_WINDOW(window), 650,700); // sets the default size for the window.
    gtk_window_set_title(GTK_WINDOW(window),"Student's HandBook - Assignment Tracker"); // sets title for the window.
    gtk_widget_set_name(window, "window"); 
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    loadCss();// Loads CSS file.

    homePage();
}

int main(int argc, char **argv){
    GtkApplication *app;
    int status;
    app = gtk_application_new("assignment.tracker.gtk", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(createWindow), NULL); // connects the app with the window.
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
