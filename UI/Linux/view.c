#include "view.h"
#include <gtk/gtk.h>

GtkTreeModel* create_and_fill_model (GtkListStore *store) {
    store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    return GTK_TREE_MODEL (store);
}

GtkWidget* create_view_and_model (GtkListStore *store)
{
    GtkWidget *view = gtk_tree_view_new ();

    GtkCellRenderer *renderer;    

    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                -1,      
                                                "Detail",  
                                                renderer,
                                                "text", COL_DETAIL,
                                                NULL);

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

    GtkTreeModel *model = create_and_fill_model (store);

    gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

    return view;
}
