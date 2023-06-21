#include<gtk/gtk.h>
static void window(GtkApplication *app,gpointer data)
{
    GtkWidget *window;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window),"rounak");
    gtk_window_set_default_size(GTK_WINDOW(window),500,600);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_window_set_child(GTK_WINDOW(window), box);

    GtkWidget *button = gtk_button_new_with_label("Hell");
    gtk_box_append(GTK_BOX(box),button);
    gtk_widget_set_halign(box,GTK_ALIGN_END);
    gtk_window_present(window);
}
int main(int argc,char **argv)
{
    int status;
    GtkApplication *app;
    app = gtk_application_new("text.org.gtk",G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app,"activate",G_CALLBACK(window),NULL);
    status =g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);
    return status;
}