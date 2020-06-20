#include <gtk/gtk.h>
#define _(String) gettext (String)
#define N_(String) String


GtkApplication   *app;
GtkBuilder       *builder;
GtkWindow        *window;
GtkComboBox      *combo1; 
GtkLabel         *resultado; 

GtkTreeIter      iter;
GtkListStore     *list;
GtkComboBox      *listwidget;
GtkTreeModel     *model;

void comboChange(GtkWidget* widget, gpointer data) {
  
  gchar *disco_select;
  gchar *commandline, **command;

  listwidget = (GtkComboBox *) gtk_builder_get_object(builder, "combo1");
  gtk_combo_box_get_active_iter(listwidget, &iter);
  list = (GtkListStore *) gtk_combo_box_get_model(listwidget);
  gtk_tree_model_get((GtkTreeModel *) list, &iter, 0, &disco_select, -1);
  if (strlen(disco_select) == 0) {
    g_free(disco_select);
    disco_select = g_strdup(NULL);         
  }

  gtk_label_set_label(resultado, disco_select);

  printf("Disco Seleccionado: %s \n", disco_select);

  // Ejecutar un comando usando la variable guardada
  commandline = g_strdup_printf("echo %s" , disco_select);

  g_shell_parse_argv(commandline, NULL, &command, NULL);
  g_free(commandline);
  g_spawn_async(NULL, command, NULL, G_SPAWN_SEARCH_PATH|G_SPAWN_DO_NOT_REAP_CHILD, NULL, NULL, NULL, NULL);


}


void initlocations() {
  gchar **lines, *output;
  gint i;
  gint status;

  listwidget = (GtkComboBox *) gtk_builder_get_object(builder, "combo1");
  list = (GtkListStore *) gtk_combo_box_get_model(listwidget);
  int select_discos = 0;
  g_spawn_command_line_sync("sudo sh script.sh disco", &output, NULL, &status, NULL);
  if (status == 0) {
    lines = g_strsplit(output, "\n", 0);
    for (i=0; lines[i] != NULL && strlen(lines[i])>0; i++) {
      gtk_list_store_append(list, &iter);
      gtk_list_store_set(list, &iter, 0, lines[i], -1);
    }
    select_discos = i;
    g_strfreev(lines);
  }
  g_free(output);

  //if (select_discos != 0){
  // gtk_combo_box_set_active_iter(listwidget, &iter);
  //}


  //gtk_combo_box_get_active(listwidget);
  //gtk_label_set_label(resultado, output);
  //printf("Active text: %s\n", text);

}


void appActivate(GtkApplication *app, gpointer data) {
  // Cargamos la interfaz y asignamos los objetos
  builder       	= (GtkBuilder*)    gtk_builder_new_from_file("menu.glade");
  window         	= (GtkWindow*)     gtk_builder_get_object(builder, "window");
  combo1          = (GtkComboBox*)   gtk_builder_get_object(builder, "combo1");
  resultado       = (GtkLabel*)      gtk_builder_get_object(builder, "resultado");
  list            = (GtkListStore*)  gtk_builder_get_object(builder, "list");
  model           = (GtkTreeModel*)  gtk_builder_get_object(builder, "model");
  
  initlocations();
  g_signal_connect (combo1, "changed", (GCallback) comboChange, NULL);



  // Mostramos todos los widgets dentro de "window"
  gtk_widget_show_all((GtkWidget*) window);
  // Y agregamos nuestra ventana a la applicación :)
  gtk_application_add_window(app, window);
}


int main(int argc, char **argv) {
  int status;

  app = gtk_application_new("com.github", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", (GCallback) appActivate, NULL);


  status = g_application_run((GApplication*) app, argc, argv);
  g_object_unref(app);

  return status;
}

