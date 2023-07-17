#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "files/combolist.c"
#define MAX_LINE_LENGTH 256

int autoSubmitCheck =0;
int filtersno = 0;
GtkWidget *window;
GtkWidget *box, *container, *comboSubject, *comboSemester, *entry, *frame, *label, *calendar, *button,*vbox,*checkButton,*filterbox,*filter,*filter2;
char* Subject[100]={"Default"};


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
int isUnique(char *str, int num){
   for(int i=0;i<num;i++){
        if(strcmp(Subject[i],str)==0){
            return 0;// String is not unique
        }
    }
   return 1;//string is unique
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
    while (Subject[count] != NULL) {
        count++;
    }

    for(int i=0;i<count;i++){
        printf("%d. %s\n",i+1, Subject[i]);
    }
    for(int i=0;i<count;i++){
        gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (user_data), Subject[i]);
    }
        // storedSubject(user_data);
    }
    else if(strcmp(selectedFilter,"Submitted") == 0){
        filtersno = 1;
        destroyWindow(window);
        homePage();
    }
    else if(strcmp(selectedFilter,"UnSubmitted") == 0){
        filtersno = 2;
        destroyWindow(window);
        homePage();
    }
    
    else if(strcmp(selectedFilter,"All") == 0){
        filtersno = 0;
        destroyWindow(window);
        homePage();
    }
    
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

static void createCheckBox(GtkWidget *parentContainer,GCallback callback, gpointer data,int active){
    checkButton = gtk_check_button_new();
    gtk_box_append(GTK_BOX(parentContainer), checkButton);

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
    // displayAssignment()
    homePage();
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
            sprintf(combined, "%d,%s,%s,%s,%s,Pending\n",fileId,sem,subject,work,year,status);
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

void submitAssignment(int id){
    char sem[50],subject[50],work[50],status[50],year[50];
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

    char buffer[1000];
    char combined[1000];
    int fileId;
    // Read lines from the original file and write to the new file, skipping the specified line
    while (fgets(buffer, sizeof(buffer), originalFile) != NULL) {
        sscanf(buffer,"%d,%[^,],%[^,],%[^,],%[^,],%s",&fileId,sem,subject,work,year,status);
        if(fileId ==id){
            sprintf(combined, "%d,%s,%s,%s,%s,Done\n",fileId,sem,subject,work,year,status);
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
    } 
    else {
        printf("Unable to delete the original file.\n");
    }
}

void checkTask(GtkToggleButton *checkButton, gpointer data){
    gboolean status = gtk_check_button_get_active(checkButton);
    printf("Status = %d\n",status);
    gchar *text = gtk_label_get_text(data);
    int numId = atoi(text);
    printf("Id: %d\n",numId);
    if (status==1 && autoSubmitCheck!=0){
    // if(status){
        // printf("Btn clicked");
        submitAssignment(numId);
        autoSubmitCheck ++;//when we first run the program, if the submit is in done. Then button automatically toggles and checks the toggle. This will prevent the program to call submitAssignment.
    }
    else if(autoSubmitCheck!=0){
    // else {
        unsubmitAssignment(numId);
        autoSubmitCheck++;
    }
    autoSubmitCheck = 1;
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
        gtk_box_append(GTK_BOX(parentContainer), box);
        createLabel(box,"Nothing to Show!!!","nothing-box",0);
    }
    else {
        FILE *fp = fopen("files/storeAssignment.txt","r");
        struct Assignment assignment[100];
        int record = 0,sno;
        char snoStr[100],id[100];
        while(!feof(fp)){
            fscanf(fp,"%d, %50[^,],%50[^,],%50[^,],%50[^,],%50[^\n]\n",&assignment[record].id,assignment[record].semester,assignment[record].subject, assignment[record].work, assignment[record].date,assignment[record].status);
            sno = record + 1;
            sprintf(snoStr,"%d. ",sno);//converting integer to string
            sprintf(id,"%d",assignment[record].id);

            GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,3);
            gtk_box_append(GTK_BOX(parentContainer), box);

            GtkWidget *elementId = gtk_label_new(id);

            
            if(filtersno ==0){
                GtkWidget *recordLabel = gtk_label_new(snoStr);
                gtk_box_append(GTK_BOX(box), recordLabel);
                if(strcmp(assignment[record].status,"Done")==0){
                    createLabel(box,assignment[record].semester,"label-submit",0);
                    createLabel(box,assignment[record].subject,"label-submit",0);
                    createLabel(box,assignment[record].work,"label-submit",0);
                    createLabel(box,assignment[record].date,"label-submit",0);
                    createCheckBox(box,G_CALLBACK(checkTask),elementId,1);
                    }
                else{
                    createLabel(box,assignment[record].semester,"null",0);
                    createLabel(box,assignment[record].subject,"null",0);
                    createLabel(box,assignment[record].work,"null",0);
                    createLabel(box,assignment[record].date,"null",0);
                    createCheckBox(box,G_CALLBACK(checkTask),elementId,0);
                }
                createButton(box,"Delete","delete-btn",G_CALLBACK(func_call),elementId); //button that deletes the specific id from file.
                
                printf("%d. Subject = %s \t Work = %s \t Date = %s\n", record + 1, assignment[record].subject,assignment[record].work,assignment[record].date );
                record = record + 1;
            }
            
            else if(filtersno==1){
                
                if(strcmp(assignment[record].status,"Done")==0){
                    GtkWidget *recordLabel = gtk_label_new(snoStr);
                    gtk_box_append(GTK_BOX(box), recordLabel);
                    createLabel(box,assignment[record].semester,"label-submit",0);
                    createLabel(box,assignment[record].subject,"label-submit",0);
                    createLabel(box,assignment[record].work,"label-submit",0);
                    createLabel(box,assignment[record].date,"label-submit",0);
                    createCheckBox(box,G_CALLBACK(checkTask),elementId,1);
                    createButton(box,"Delete","delete-btn",G_CALLBACK(func_call),elementId); //button that deletes the specific id from file.
                
                printf("%d. Subject = %s \t Work = %s \t Date = %s\n", record + 1, assignment[record].subject,assignment[record].work,assignment[record].date );
                record = record + 1;
                }
            }
            else if(filtersno==2){
                if(strcmp(assignment[record].status,"Pending")==0){
                    GtkWidget *recordLabel = gtk_label_new(snoStr);
                    gtk_box_append(GTK_BOX(box), recordLabel);
                    createLabel(box,assignment[record].semester,"null",0);
                    createLabel(box,assignment[record].subject,"null",0);
                    createLabel(box,assignment[record].work,"null",0);
                    createLabel(box,assignment[record].date,"null",0);
                    createCheckBox(box,G_CALLBACK(checkTask),elementId,0);
                createButton(box,"Delete","delete-btn",G_CALLBACK(func_call),elementId); //button that deletes the specific id from file.
                
                printf("%d. Subject = %s \t Work = %s \t Date = %s\n", record + 1, assignment[record].subject,assignment[record].work,assignment[record].date );
                record = record + 1;
                }
            }
        }
        fclose(fp);
    }
}

void go_back_pg_2(){
    destroyWindow(window);
    Page_2();
}

void go_to_homepage(){
    destroyWindow(window);
    homePage();
}

void homePage(){
    //-----------------------------CONTAINER------------------------------------------//
    container = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_widget_set_name(container, "container");

    gtk_window_set_child(GTK_WINDOW(window), container);
    
    createButton(container,"Add Work","btn",G_CALLBACK(go_back_pg_2),NULL);

    //Title
    createLabel(container, "Your Assignments:","title",0);


    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_box_append(GTK_BOX(container),vbox);

    createLabel(vbox, "FILTER:","", 1);//layout funct(BoxToAppend, Title, NameForCss,boolean value for x-align(T))
    filterbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_box_append(GTK_BOX(vbox),filterbox);

    //Label for DropDown/Combobox
    
    //To create a DropDown.
    filter = gtk_combo_box_text_new();
    filterList(filter);// This fucntion provides option for DropDown.
    gtk_box_append (GTK_BOX(filterbox), filter);
    if(filtersno ==0){
        gtk_combo_box_set_active(GTK_COMBO_BOX(filter), 0);
    }
    else if(filtersno == 1){
        gtk_combo_box_set_active(GTK_COMBO_BOX(filter), 1);
    }
    else if(filtersno == 2){
        gtk_combo_box_set_active(GTK_COMBO_BOX(filter), 2);
    }

    

    filter2 = gtk_combo_box_text_new();
    gtk_box_append (GTK_BOX(filterbox), filter2);
    g_signal_connect(filter, "changed", G_CALLBACK(filterSubjectSelection),filter2);

    //title-box(table)
    // box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
    // gtk_box_append(GTK_BOX(vbox), box);

    // createLabel(box,"S.No","table-title",0);
    // createLabel(box,"Semester","table-title",0);
    // createLabel(box,"Subject","table-title",0);
    // createLabel(box,"Assignment","table-title",0);
    // createLabel(box,"Due Date","table-title",0);

    displayAssignment(vbox);
    
    printf("%d", filtersno);
    gtk_window_present(GTK_WINDOW(window));
}

void Page_2(){
    //-----------------------------CONTAINER------------------------------------------//
    //Main box
    container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
    gtk_window_set_child (GTK_WINDOW (window), container);
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
