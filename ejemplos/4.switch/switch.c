#include <gtk/gtk.h>

GtkApplication   *app;
GtkBuilder       *builder;
GtkWindow        *window;
GtkSwitch        *switch1;
GtkLabel         *usuario;
GtkFrame         *frame;
GtkSpinner       *spinner;

void on_switch_state_set(GtkSwitch *switch1) {

    gboolean T = gtk_switch_get_active(switch1);
    if (T) gtk_spinner_start (spinner),
    gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(builder, "frame"), TRUE);
  
    else gtk_spinner_stop(spinner),
    gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(builder, "frame"), FALSE);
}
	

void appActivate(GtkApplication *app, gpointer data) {
  // Cargamos la interfaz y asignamos los objetos
  builder       	= (GtkBuilder*)    gtk_builder_new_from_file("switch.glade");
  window         	= (GtkWindow*)     gtk_builder_get_object(builder, "window");
  switch1         = (GtkSwitch*)     gtk_builder_get_object(builder, "switch1");
  spinner         = (GtkSpinner*)     gtk_builder_get_object(builder, "spinner");
  frame           = (GtkFrame*)      gtk_builder_get_object(builder, "frame");
  usuario      	  = (GtkLabel*)      gtk_builder_get_object(builder, "usuario");


  gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(builder, "frame"), FALSE);

  // Conectamos signals correspondientes
  gtk_builder_connect_signals (builder, NULL);
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

