#include<gtk/gtk.h>
static void window(GtkApplication *app,gpointer data)
{
    GtkWidget *window;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window),"rounak");
    gtk_window_set_default_size(GTK_WINDOW(window),500,600);
    const gchar *icon_path = "img/img.jpg";  // Replace with the path to your icon file
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(icon_path, NULL);
    gtk_widget_set_name(pixbuf,"icon");
    // GtkWidget *image = gtk_image_new_from_pixbuf(pixbuf);
    GtkWidget *button = gtk_button_new();
    // gtk_button_set_image(GTK_BUTTON(button), image);
    gtk_button_set_icon_name(button, "icon");
    gtk_window_set_child(GTK_WINDOW(window), button);
    gtk_window_present(GTK_WINDOW(window));
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