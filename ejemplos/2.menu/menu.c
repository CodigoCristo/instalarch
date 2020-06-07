#include <gtk/gtk.h>
#define _(String) gettext (String)
#define N_(String) String


GtkApplication   *app;
GtkBuilder       *builder;
GtkWindow        *window;
GtkComboBox      *combo1; 
GtkComboBox      *combo2;

GtkListStore     *list;
GtkTreeModel     *model;


void initlocations() {
  GtkComboBox *listwidget;
  GtkTreeIter iter;
  GtkListStore *list;
  gchar **lines, *output, *device;
  gint i;
  gint status;
  
  listwidget = (GtkComboBox *) gtk_builder_get_object(builder, "combo1");
  list = (GtkListStore *) gtk_combo_box_get_model(listwidget);
  int select_idiomaS_count = 0;
  g_spawn_command_line_sync("sudo sh script.sh key-sistema", &output, NULL, &status, NULL);
  if (status == 0) {
    lines = g_strsplit(output, "\n", 0);
    for (i=0; lines[i] != NULL && strlen(lines[i])>0; i++) {
      gtk_list_store_append(list, &iter);
      gtk_list_store_set(list, &iter, 0, lines[i], -1);
    }
    select_idiomaS_count = i;
    g_strfreev(lines);
  }
  g_free(output);
  if (select_idiomaS_count != 0){
    gtk_combo_box_set_active_iter(listwidget, &iter);
  }

  listwidget = (GtkComboBox *) gtk_builder_get_object(builder, "combo2");
  list = (GtkListStore *) gtk_combo_box_get_model(listwidget);
  int select_idiomaT_count = 0;
  g_spawn_command_line_sync("sudo sh script.sh key-terminal", &output, NULL, &status, NULL);
  if (status == 0) {
    lines = g_strsplit(output, "\n", 0);
    for (i=0; lines[i] != NULL && strlen(lines[i])>0; i++) {
      gtk_list_store_append(list, &iter);
      gtk_list_store_set(list, &iter, 0, lines[i], -1);
    }
    select_idiomaT_count = i;
    g_strfreev(lines);
  }
  g_free(output);
  if (select_idiomaT_count != 0){
    gtk_combo_box_set_active_iter(listwidget, &iter);
  }



}


void appActivate(GtkApplication *app, gpointer data) {
  // Cargamos la interfaz y asignamos los objetos
  builder       	= (GtkBuilder*)    gtk_builder_new_from_file("menu.glade");
  window         	= (GtkWindow*)     gtk_builder_get_object(builder, "window");
  combo1          = (GtkComboBox*)   gtk_builder_get_object(builder, "combo1");
  combo2          = (GtkComboBox*)   gtk_builder_get_object(builder, "combo2");
  list            = (GtkListStore*)  gtk_builder_get_object(builder, "list");
  model           = (GtkTreeModel*)  gtk_builder_get_object(builder, "model");
  
  initlocations();



  // Mostramos todos los widgets dentro de "window"
  gtk_widget_show_all((GtkWidget*) window);
  // Y agregamos nuestra ventana a la applicación :)
  gtk_application_add_window(app, window);
}


int main(int argc, char **argv) {
  int status;

  // Creamos una nueva applicación
  app = gtk_application_new("com.github.M1que4s.Instalarch", G_APPLICATION_FLAGS_NONE);
  // Conectamos la función previa con nuestra appliación
  g_signal_connect(app, "activate", (GCallback) appActivate, NULL);

  // Corremos la appliación
  status = g_application_run((GApplication*) app, argc, argv);
  // Sinceramente, no sé que hace esto xd véase la documentación de GObject para más información.
  g_object_unref(app);

  return status;
}

