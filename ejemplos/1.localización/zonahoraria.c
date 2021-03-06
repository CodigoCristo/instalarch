#include <gtk/gtk.h>

GtkApplication   *app;
GtkBuilder       *builder;
GtkWindow        *window;
GtkButton        *boton;
GtkLabel         *resultado;


void on_boton_clicked(GtkButton *btn, gpointer data) {

    char* zona_horaria;
    g_spawn_command_line_sync ("sh script.sh", &zona_horaria, NULL, NULL, NULL);
    gtk_label_set_label (resultado, zona_horaria);
    printf("Tu zona horaria es: %s \n", zona_horaria);

}
	

void appActivate(GtkApplication *app, gpointer data) {
  // Cargamos la interfaz y asignamos los objetos
  builder       	= (GtkBuilder*)    gtk_builder_new_from_file("zonahoraria.glade");
  window         	= (GtkWindow*)     gtk_builder_get_object(builder, "window");
  boton          	= (GtkButton*)     gtk_builder_get_object(builder, "boton");
  resultado      	= (GtkLabel*)      gtk_builder_get_object(builder, "resultado");



  // Conectamos signals correspondientes
  g_signal_connect(boton, "clicked", (GCallback) on_boton_clicked, NULL);


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

