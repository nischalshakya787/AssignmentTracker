#include <gtk/gtk.h>
GtkWidget *checkButton;
// Callback function to be called when the check button is toggled
int i = 1;
void on_check_button_toggled() {
     GtkToggleButton *checkbtn = GTK_CHECK_BUTTON(checkButton);
     gboolean checked = gtk_check_button_get_active(checkbtn);
    
    if (checked) {
        // Call the function for when the check button is checked
        g_print("Check button checked\n");
    } else {
        // Call the function for when the check button is unchecked
        g_print("Check button unchecked\n");
    }
}

void switch_check(){
    GtkToggleButton *btn = GTK_CHECK_BUTTON(checkButton);
    if(i%2==0){
        gtk_check_button_set_active(btn, 0);
        i++;
    }
    else{
        gtk_check_button_set_active(btn, 1);
        i++;
    }
    
}


static void window(GtkApplication *app, gpointer data){
    GtkWidget *window,*box, *button;
    window = gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window),500,500);
    gtk_window_set_title(GTK_WINDOW(window), "TEST");

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_window_set_child(GTK_WINDOW(window), box);

    // Create a check button
    checkButton = gtk_check_button_new_with_label("Check Button");
    gtk_box_append(GTK_BOX(box), checkButton);

    // Connect the "toggled" signal to the callback function
    g_signal_connect(checkButton, "toggled", G_CALLBACK(on_check_button_toggled), NULL);

    button = gtk_button_new_with_label("check");
    gtk_box_append(GTK_BOX(box), button);

    g_signal_connect(button, "clicked", G_CALLBACK(switch_check),NULL);


    gtk_window_present(GTK_WINDOW(window));
} 

int main(int argc, char **argv){
    GtkApplication *app;
    int status;
    app = gtk_application_new("test.gtk.project", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(window), NULL);
    status = g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);
    return status;

}