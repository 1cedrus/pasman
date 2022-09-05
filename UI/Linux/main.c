#include <gtk/gtk.h>
#include "view.h"

    GtkListStore *store;


void start() {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *label;
    GtkWidget *entry;
    GtkWidget *button;
    GtkEntryBuffer *entryBuffer;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW(window), 480, 240);
    gtk_window_set_title(GTK_WINDOW(window), "");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 50);

    vbox = gtk_box_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    label = gtk_label_new("Welcome to PASMAN");
    gtk_widget_set_valign(label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);

    gchar buffer[] = "Please set your primary password...";
    entryBuffer = gtk_entry_buffer_new(buffer, strlen(buffer));

    entry = gtk_entry_new_with_buffer(entryBuffer);
    gtk_box_pack_start(GTK_BOX(vbox), entry, 0, 0, 50);

    button = gtk_button_new_with_label("Get started");
    gtk_widget_set_size_request(button, 180, 50);
    gtk_widget_set_halign(button, GTK_ALIGN_CENTER);
    // gtk_widget_set_valign(button, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

    gtk_widget_show_all(window);
}

void login() {
    GtkWidget *window;
    GtkWidget *entry;
    GtkWidget *label;
    GtkWidget *checkbox;
    GtkWidget *button;
    GtkWidget *hbox;
    GtkWidget *vbox;


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 430);
    gtk_window_set_title(GTK_WINDOW(window), "");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 50);

    vbox = gtk_box_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    hbox = gtk_box_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, 0, 0, 0);
    
    label = gtk_label_new("Password:");
    gtk_box_pack_start(GTK_BOX(hbox), label, 0, 0, 10);

    entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox), entry, TRUE, TRUE, 10);

    checkbox = gtk_check_button_new();
    gtk_box_pack_start(GTK_BOX(hbox), checkbox, 0, 0, 10);

    button = gtk_button_new_with_label("Login");
    gtk_widget_set_size_request(button, 120, 60);
    gtk_widget_set_halign(button, GTK_ALIGN_END);
    gtk_widget_set_valign(button, GTK_ALIGN_END);
    
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

    gtk_widget_show_all(window);

    
}

void pasman() {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *buttonHelp;
    GtkWidget *buttonAdd;
    GtkWidget *buttonChange;
    GtkWidget *buttonDelete;
    GtkWidget *scwin;
    GtkWidget *view;


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 430);
    gtk_window_set_title(GTK_WINDOW(window), "");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);

    vbox = gtk_box_new(TRUE, 20);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    scwin = gtk_scrolled_window_new(NULL, NULL);
    view = create_view_and_model(store);
    gtk_container_add(GTK_CONTAINER(scwin), view);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scwin), 
                                GTK_POLICY_AUTOMATIC,
                                GTK_POLICY_ALWAYS);
    gtk_box_pack_start(GTK_BOX(vbox), scwin, TRUE, TRUE, 0);

    hbox = gtk_box_new(FALSE, 20);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, 0, 1, 0);

    buttonAdd = gtk_button_new_with_label("Add");
    gtk_box_pack_start(GTK_BOX(hbox), buttonAdd, 1, 1, 0);

    buttonChange = gtk_button_new_with_label("Change");
    gtk_box_pack_start(GTK_BOX(hbox), buttonChange, 1, 1, 0);
    
    buttonDelete = gtk_button_new_with_label("Delete");
    gtk_box_pack_start(GTK_BOX(hbox), buttonDelete, 1, 1, 0);

    buttonHelp = gtk_button_new_with_label("Help");
    gtk_box_pack_start(GTK_BOX(hbox), buttonHelp, 1, 1, 0);

    gtk_widget_show_all(window);
}

void change() {
        GtkWidget *window;
    GtkWidget *labelDetail;
    GtkWidget *labelUsername;
    GtkWidget *labelPassword;
    GtkWidget *entryDetail;
    GtkWidget *entryUsername;
    GtkWidget *entryPassword;
    GtkWidget *buttonGenerate;
    GtkWidget *buttonAdd;
    GtkWidget *hboxDetail;
    GtkWidget *hboxUsername;
    GtkWidget *hboxPassword;
    GtkWidget *vbox;


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW(window), 480, 220);
    gtk_window_set_title(GTK_WINDOW(window), "");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);

    vbox = gtk_box_new(TRUE, 20);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    hboxDetail = gtk_box_new(FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), hboxDetail, 0, 0, 0);

    labelDetail = gtk_label_new("     Detail:     ");
    gtk_box_pack_start(GTK_BOX(hboxDetail), labelDetail, 0, 0, 0);

    entryDetail = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hboxDetail), entryDetail, 1, 1, 0);
    //
    hboxUsername = gtk_box_new(FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), hboxUsername, 0, 0, 0);

    labelUsername = gtk_label_new("Username: ");
    gtk_box_pack_start(GTK_BOX(hboxUsername), labelUsername, 0, 0, 0);

    entryUsername = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hboxUsername), entryUsername, 1, 1, 0);
    //
    hboxPassword = gtk_box_new(FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), hboxPassword, 0, 0, 0);

    labelPassword = gtk_label_new("Password: ");
    gtk_box_pack_start(GTK_BOX(hboxPassword), labelPassword, 0, 0, 0);

    entryPassword = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hboxPassword), entryPassword, 1, 1, 0);

    buttonGenerate = gtk_button_new_with_label("Generate");
    gtk_box_pack_start(GTK_BOX(hboxPassword), buttonGenerate, 0, 0, 0);

    buttonAdd = gtk_button_new_with_label("Change");
    gtk_widget_set_halign(buttonAdd, GTK_ALIGN_END);
    gtk_widget_set_valign(buttonAdd, GTK_ALIGN_END);
    gtk_widget_set_size_request(buttonAdd, 130, 40);
    gtk_box_pack_start(GTK_BOX(vbox), buttonAdd, 0, 0, 0);

    gtk_widget_show_all(window);
}

void add() {
    GtkWidget *window;
    GtkWidget *labelDetail;
    GtkWidget *labelUsername;
    GtkWidget *labelPassword;
    GtkWidget *entryDetail;
    GtkWidget *entryUsername;
    GtkWidget *entryPassword;
    GtkWidget *buttonGenerate;
    GtkWidget *buttonAdd;
    GtkWidget *hboxDetail;
    GtkWidget *hboxUsername;
    GtkWidget *hboxPassword;
    GtkWidget *vbox;


    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW(window), 480, 220);
    gtk_window_set_title(GTK_WINDOW(window), "");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 15);

    vbox = gtk_box_new(TRUE, 20);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    hboxDetail = gtk_box_new(FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), hboxDetail, 0, 0, 0);

    labelDetail = gtk_label_new("     Detail:     ");
    gtk_box_pack_start(GTK_BOX(hboxDetail), labelDetail, 0, 0, 0);

    entryDetail = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hboxDetail), entryDetail, 1, 1, 0);
    //
    hboxUsername = gtk_box_new(FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), hboxUsername, 0, 0, 0);

    labelUsername = gtk_label_new("Username: ");
    gtk_box_pack_start(GTK_BOX(hboxUsername), labelUsername, 0, 0, 0);

    entryUsername = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hboxUsername), entryUsername, 1, 1, 0);
    //
    hboxPassword = gtk_box_new(FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), hboxPassword, 0, 0, 0);

    labelPassword = gtk_label_new("Password: ");
    gtk_box_pack_start(GTK_BOX(hboxPassword), labelPassword, 0, 0, 0);

    entryPassword = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hboxPassword), entryPassword, 1, 1, 0);

    buttonGenerate = gtk_button_new_with_label("Generate");
    gtk_box_pack_start(GTK_BOX(hboxPassword), buttonGenerate, 0, 0, 0);

    buttonAdd = gtk_button_new_with_label("Add");
    gtk_widget_set_halign(buttonAdd, GTK_ALIGN_END);
    gtk_widget_set_valign(buttonAdd, GTK_ALIGN_END);
    gtk_widget_set_size_request(buttonAdd, 130, 40);
    gtk_box_pack_start(GTK_BOX(vbox), buttonAdd, 0, 0, 0);

    gtk_widget_show_all(window);
}


int main (int argc, char *argv[]) {

    gtk_init(&argc, &argv);
    // start();
    login();
    pasman();
    // add();
    // change();
    gtk_main();
}

