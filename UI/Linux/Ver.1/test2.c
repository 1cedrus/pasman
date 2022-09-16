#include <gtk/gtk.h>
#include "file.h"
#include "aes.h"
#include <json-c/json.h>
#include "commands.h"

char *keyLog = "key.log";
char *dataLog = "database.json";

enum
{
  COL_USERNAME = 0,
  COL_PASSWORD,
  NUM_COLS
};

////
    GtkWidget *window;
    GtkWidget *hbox1;
    GtkWidget *vbox1;
    GtkWidget *hbox2_a;
    GtkWidget *hbox2_b;
    GtkWidget *vbox2;
    GtkWidget *hbox3;

    GtkWidget *buttonCheckKey;
    GtkWidget *buttonChange;
    GtkWidget *buttonAdd;
    GtkWidget *buttonDelete;
    
    GtkWidget *searchBar;
    GtkWidget *entryKey;

    GtkWidget *entryUsername;
    GtkWidget *entryPassword;

    GtkListStore *store;
    GtkTreeIter iterIsChosen;
    char key[80];

////


GtkTreeModel* create_and_fill_model (void) {
    store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_STRING);
    return GTK_TREE_MODEL (store);
}

GtkWidget* create_view_and_model (void)
{
    GtkWidget *view = gtk_tree_view_new ();

    GtkCellRenderer *renderer;    

    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                -1,      
                                                "Username",  
                                                renderer,
                                                "text", COL_USERNAME,
                                                NULL);

    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                -1,      
                                                "Password",  
                                                renderer,
                                                "text", COL_PASSWORD,
                                                NULL);

    GtkTreeModel *model = create_and_fill_model ();

    gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

    return view;
}

int i = 0;
void list_account() 
{
	
    json_object *database, *username, *password, *account;
	size_t numOfAcc;

	database = json_object_from_file("database.json");
	numOfAcc = json_object_array_length(database);

    GtkTreeIter iter;
	for (; i < numOfAcc; i++) 
	{
		account = json_object_array_get_idx(database, i);
		username = json_object_object_get(account, "username");
		password = json_object_object_get(account, "password");

        gtk_list_store_append (store, &iter);
        gtk_list_store_set (store, &iter, 
                        COL_USERNAME, json_object_get_string(username),
                        COL_PASSWORD, json_object_get_string(password),
                        -1);
	}
}

void check_key (void) {
	unsigned char *cipher = NULL;
	readFile(keyLog, &cipher);

    const char *str;
    str = gtk_entry_get_text (GTK_ENTRY(entryKey));

    sprintf(key, "%s", str);

    unsigned char *keyCheck = NULL;
    aes_decrypt(cipher, strlen(cipher), key, &keyCheck);


    if (!strcmp(key, keyCheck)) {
        unsigned char *cipher = NULL;
        int cipherLen = readFile(dataLog, &cipher);
        writeCipherDecrypt(dataLog, cipher, key, cipherLen);

        list_account();

        gtk_container_remove (GTK_CONTAINER(hbox1), entryKey);
        gtk_container_remove (GTK_CONTAINER(hbox1), buttonCheckKey);
        gtk_widget_set_sensitive (GTK_WIDGET(buttonAdd), TRUE);
        return;
    }
}

void set_senitive (GtkWidget *widget, gpointer button) {
    gtk_widget_set_sensitive (GTK_WIDGET(button), TRUE);
}

void addAccount (GtkWidget *button, gpointer data) {
    const char *newUsername = gtk_entry_get_text (GTK_ENTRY(entryUsername));
    const char *newPassword = gtk_entry_get_text (GTK_ENTRY(entryPassword));

    Account newAccount = {newUsername, newPassword};
    new(newAccount);
    
    list_account();

    GtkWidget *widget;
    widget = (GtkWidget*) data;
    gtk_widget_hide(widget);
    set_senitive (widget, buttonAdd);
}

void deleteAccount (GtkWidget *button, gpointer iter) {
    // GtkTreeModel *model;
    // GtkTreeIter iter;
    i--;
    int numOfAcc, j;
    json_object *database, *username, *password, *account;
    char *delUsername, *delPassword;   

    // model = gtk_tree_view_get_model(view);

    // if (!gtk_tree_model_get_iter(GTK_TREE_MODEL(store), &iter, path))
        //return; /* path describes a non-existing row - should not happen */
    gtk_tree_model_get (GTK_TREE_MODEL(store), &iterIsChosen,
                                    COL_USERNAME, &delUsername,
                                    COL_PASSWORD, &delPassword, 
                                    -1);


	database = json_object_from_file("database.json");
	
	numOfAcc = json_object_array_length(database);

	for (j = 0; j < numOfAcc; j++) 
	{
		account = json_object_array_get_idx(database, j);
		username = json_object_object_get(account, "username");
		password = json_object_object_get(account, "password");
        if (!strcmp (json_object_get_string(username), delUsername) && !strcmp (json_object_get_string(password), delPassword)) {
            break;
        }
	}

	json_object_array_del_idx(database, j, 1);

	json_object_to_file("database.json", database);

    g_free(delUsername);
    g_free(delPassword);
    
    gtk_list_store_remove(store, &iterIsChosen);
    gtk_widget_set_sensitive (GTK_WIDGET(buttonChange), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(buttonDelete), FALSE);
}


void welcomeWindow (void) {
    GtkWidget *windowWelcome;
    GtkWidget *labelWelcome;
    GtkWidget *entryNewKey;
    GtkWidget *buttonStart;
    GtkWidget *vbox;
    GtkEntryBuffer *bufferNewKey;

    windowWelcome = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(windowWelcome), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(windowWelcome), FALSE);
    gtk_window_set_title(GTK_WINDOW(windowWelcome), "Welcome");
    gtk_container_set_border_width(GTK_CONTAINER(windowWelcome), 15);

    vbox = gtk_box_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(windowWelcome), vbox);

    labelWelcome = gtk_label_new("Welcome to PASMAN!!");
    gtk_box_pack_start(GTK_BOX(vbox), labelWelcome, 0, 0, 0);

    bufferNewKey = gtk_entry_buffer_new("Please set your first key....", 30);
    entryNewKey = gtk_entry_new_with_buffer(bufferNewKey);
    gtk_box_pack_start(GTK_BOX(vbox), entryNewKey, 0, 0, 0);

    buttonStart = gtk_button_new_with_label("Get started!!");
    gtk_box_pack_start(GTK_BOX(vbox), buttonStart, 0, 0, 0);

    gtk_widget_show_all(windowWelcome);


}
void doesHasKey (void) {
    // unsigned char *cipher = NULL;
	// readFile(keyLog, &cipher);

    printf("anhyeuem");

    // if (!cipher) welcomeWindow();
}

void addPopUp (void) {

    GtkWidget *popup;
    GtkWidget *buttonEnter;
    GtkWidget *labelUsername;
    GtkWidget *labelPassword;

    gtk_widget_set_sensitive (GTK_WIDGET(buttonChange), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(buttonDelete), FALSE);


    popup = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position (GTK_WINDOW(popup), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable (GTK_WINDOW(popup), FALSE);
    gtk_window_set_title (GTK_WINDOW(popup), "Add:");
    gtk_container_set_border_width (GTK_CONTAINER(popup), 15);


    vbox2 = gtk_box_new (TRUE, 0);
    gtk_container_add (GTK_CONTAINER(popup), vbox2);

    hbox2_a = gtk_box_new (FALSE, 0);
    hbox2_b = gtk_box_new (FALSE, 0);
    gtk_box_pack_start (GTK_BOX(vbox2), hbox2_a, 0, 0, 5);
    gtk_box_pack_start (GTK_BOX(vbox2), hbox2_b, 0, 0, 5);

    labelUsername = gtk_label_new ("Username:");
    entryUsername = gtk_entry_new ();
    gtk_box_pack_start (GTK_BOX(hbox2_a), labelUsername, 0, 0, 5);
    gtk_box_pack_start (GTK_BOX(hbox2_a), entryUsername, 0, 0, 5);
    
    
    labelPassword = gtk_label_new ("Password:");
    entryPassword = gtk_entry_new ();
    gtk_box_pack_start (GTK_BOX(hbox2_b), labelPassword, 0, 0, 5);
    gtk_box_pack_start (GTK_BOX(hbox2_b), entryPassword, 0, 0, 5);

    buttonEnter = gtk_button_new_with_label ("Enter");
    gtk_box_pack_start (GTK_BOX(vbox2), buttonEnter, 0, 0, 5);

    g_signal_connect (buttonEnter, "clicked", G_CALLBACK(addAccount), popup);

    g_signal_connect (popup, "destroy", G_CALLBACK(set_senitive), buttonAdd);
    // g_signal_connect (popup, "destroy", G_CALLBACK(set_senitive), buttonChange);


    gtk_widget_show_all (GTK_WIDGET(popup));
}

void changeAccount (GtkWidget *button, gpointer popup) {
    const char *changeUserErr = gtk_entry_get_text (GTK_ENTRY(entryUsername));
    const char *changePassErr = gtk_entry_get_text (GTK_ENTRY(entryPassword));

    gchar *changeUsername = g_locale_to_utf8 (changeUserErr, -1, NULL, NULL, NULL);
    gchar *changePassword = g_locale_to_utf8 (changePassErr, -1, NULL, NULL, NULL);

    gtk_list_store_set(store, &iterIsChosen, 0, changeUsername, -1);
    gtk_list_store_set(store, &iterIsChosen, 1, changePassword, -1);

    gtk_widget_set_sensitive (GTK_WIDGET(buttonChange), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(buttonDelete), FALSE);

    GtkWidget *widget = (GtkWidget *) popup;
    gtk_widget_hide(widget);
}

void changePopUp (GtkWidget *button, gpointer iter) {

    GtkWidget *popup;
    GtkWidget *buttonEnter;
    GtkWidget *labelUsername;
    GtkWidget *labelPassword;

    char *changeUsername, *changePassword;

    gtk_tree_model_get (GTK_TREE_MODEL(store), &iterIsChosen,
                                    COL_USERNAME, &changeUsername,
                                    COL_PASSWORD, &changePassword, 
                                    -1);

    GtkEntryBuffer *username = gtk_entry_buffer_new (changeUsername, strlen(changeUsername));
    GtkEntryBuffer *password = gtk_entry_buffer_new (changePassword, strlen(changePassword));

    gtk_widget_set_sensitive (GTK_WIDGET(buttonChange), FALSE);

    popup = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position (GTK_WINDOW(popup), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable (GTK_WINDOW(popup), FALSE);
    gtk_window_set_title (GTK_WINDOW(popup), "Change:");
    gtk_container_set_border_width (GTK_CONTAINER(popup), 5);

    vbox2 = gtk_box_new (TRUE, 0);
    gtk_container_add (GTK_CONTAINER(popup), vbox2);

    hbox2_a = gtk_box_new (FALSE, 0);
    hbox2_b = gtk_box_new (FALSE, 0);
    gtk_box_pack_start (GTK_BOX(vbox2), hbox2_a, 0, 0, 5);
    gtk_box_pack_start (GTK_BOX(vbox2), hbox2_b, 0, 0, 5);

    labelUsername = gtk_label_new ("Username:");
    entryUsername = gtk_entry_new_with_buffer (username);
    gtk_box_pack_start (GTK_BOX(hbox2_a), labelUsername, 0, 0, 5);
    gtk_box_pack_start (GTK_BOX(hbox2_a), entryUsername, 0, 0, 5);
    
    
    labelPassword = gtk_label_new ("Password:");
    entryPassword = gtk_entry_new_with_buffer (password);
    gtk_box_pack_start (GTK_BOX(hbox2_b), labelPassword, 0, 0, 5);
    gtk_box_pack_start (GTK_BOX(hbox2_b), entryPassword, 0, 0, 5);

    buttonEnter = gtk_button_new_with_label ("Enter");
    gtk_box_pack_start (GTK_BOX(vbox2), buttonEnter, 0, 0, 5);

    gtk_widget_set_sensitive (GTK_WIDGET(buttonDelete), FALSE);
    g_signal_connect (buttonEnter, "clicked", G_CALLBACK(changeAccount), popup);
    gtk_widget_show_all (popup);
}

void end () {
    unsigned char *text = NULL;
    int textLen = readFile(dataLog, &text);
    writeTextEncrypt(dataLog, text, key, textLen);
    gtk_main_quit();
}

void getIter (GtkTreeView *view, GtkTreePath *path, GtkTreeViewColumn *col, gpointer user_data) {
    gtk_widget_set_sensitive (GTK_WIDGET(buttonDelete), TRUE);
    gtk_widget_set_sensitive (GTK_WIDGET(buttonChange), TRUE);
    gtk_tree_model_get_iter (GTK_TREE_MODEL(store), &iterIsChosen, path);
}


int main (int argc, char **argv) {

    gtk_init (&argc, &argv);

    // unsigned char *cipher = NULL;
	// readFile(keyLog, &cipher);
    // if (!cipher) welcomeWindow();

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
    gtk_window_set_title (GTK_WINDOW(window), "PASMAN");
    gtk_container_set_border_width (GTK_CONTAINER(window), 15);
    gtk_window_set_default_size (GTK_WINDOW(window), 500, 400);

    vbox1 = gtk_box_new (TRUE, 0);
    gtk_container_add (GTK_CONTAINER(window), vbox1);

    // searchBar = gtk_search_entry_new ();
    // gtk_box_pack_start (GTK_BOX(vbox1), searchBar, 0, TRUE, 0);

    GtkWidget *scwin = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *view = create_view_and_model ();
    gtk_container_add(GTK_CONTAINER(scwin), view);
    // gtk_tree_view_set_activate_on_single_click (GTK_TREE_VIEW(view), TRUE);

    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scwin), 
                                GTK_POLICY_AUTOMATIC,
                                GTK_POLICY_ALWAYS);
    gtk_box_pack_start(GTK_BOX(vbox1), scwin, 
                    TRUE, TRUE, 10);

    hbox1 = gtk_box_new (FALSE, 0);
    gtk_box_pack_start (GTK_BOX(vbox1), hbox1, 0, 0, 0);

    buttonCheckKey = gtk_button_new_with_label ("Enter");
    buttonAdd = gtk_button_new_with_label ("Add");
    buttonChange = gtk_button_new_with_label ("Change");
    buttonDelete = gtk_button_new_with_label ("Delete");
    gtk_widget_set_sensitive (GTK_WIDGET(buttonAdd), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(buttonChange), FALSE);
    gtk_widget_set_sensitive (GTK_WIDGET(buttonDelete), FALSE);

    GtkEntryBuffer *entryTh = gtk_entry_buffer_new ("Password", 8);
    entryKey = gtk_entry_new_with_buffer (entryTh);
    gtk_entry_set_visibility (GTK_ENTRY(entryKey), FALSE);
    gtk_box_pack_start (GTK_BOX(hbox1), entryKey, 0, TRUE, 5);
    gtk_box_pack_start (GTK_BOX(hbox1), buttonCheckKey, 0, TRUE, 5);
    gtk_box_pack_start (GTK_BOX(hbox1), buttonChange, 0, TRUE, 5);
    gtk_box_pack_start (GTK_BOX(hbox1), buttonAdd, 0, TRUE, 5);
    gtk_box_pack_start (GTK_BOX(hbox1), buttonDelete, 0, TRUE, 5);

    GtkWidget *remove = gtk_label_new ("- Double click on a row to delete -");
    GtkWidget *search = gtk_label_new ("- Select a row on table and type somethings to search -");

    gtk_box_pack_start (GTK_BOX(vbox1), remove, 0, TRUE, 5);
    gtk_box_pack_start (GTK_BOX(vbox1), search, 0, TRUE, 5);


    // GtkTreeIter iterIsChosen;

        
    g_signal_connect (window, "destroy", G_CALLBACK(end), NULL);

    g_signal_connect (entryKey, "activate", G_CALLBACK(check_key), NULL);

    g_signal_connect (buttonCheckKey, "clicked", G_CALLBACK(check_key), NULL);

    g_signal_connect (buttonAdd, "clicked", G_CALLBACK(addPopUp), NULL);

    g_signal_connect (buttonChange, "clicked", G_CALLBACK(changePopUp), NULL);

    g_signal_connect (view, "row-activated", G_CALLBACK(getIter), NULL);

    g_signal_connect (buttonDelete, "clicked", G_CALLBACK(deleteAccount), NULL);

    gtk_widget_show_all (window);

    gtk_main ();
}