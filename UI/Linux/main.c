#include <gtk/gtk.h>

void start() {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *label;
    GtkWidget *entry;
    GtkWidget *button;
    GtkWidget *entryBuffer;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW(window), 480, 240);
    gtk_window_set_position(GKT_WINDOW(window), GTK_WIN_POS_CENTER);

    vbox = gtk_box_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    label = gtk_label_new("Welcome to PASMAN");
    gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);

    gchar buffer[] = "Please set your primary password...";
    entryBuffer = gtk_entry_buffer_new(buffer, strlen(buffer));
    free(buffer);

    entry = gtk_entry_new_with_buffer(GTK_ENTRY_BUFFER(entryBuffer));
    gtk_box_pack_start(GTK_BOX(vbox), entry, 0, 0, 0);

    button = gtk_button_new_with_label("Get started");
    gtk_box_pack_start(GTK_BOX(vbox), button, 0, 0, 0);

    gtk_widget_show_all(window);
}


int main (int argc, char *argv[]) {

    gtk_init(&argc, &argv);
    start();
    gtk_main();
}

