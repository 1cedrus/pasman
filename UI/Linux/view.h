#include <gtk/gtk.h>

enum
{
  COL_DETAIL = 0,
  COL_USERNAME,
  COL_PASSWORD,
  NUM_COLS
};

GtkTreeModel* create_and_fill_model (GtkListStore *store);
GtkWidget* create_view_and_model (GtkListStore *store);