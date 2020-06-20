#include <gtk/gtk.h>

GtkApplication   *app;
GtkBuilder       *builder;
GtkWindow        *window;
GtkButton        *boton;

char git[]="";
char neofetch[]	="";
char wget[]		="";


void on_chkbtn_1_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
	
	if (gtk_toggle_button_get_active(togglebutton)) {
	char git[]="git";
    g_print("Seleccionado: %s \n", git);
    
	}
	else {
		char git[]="";
		g_print("git desmarcado\n");
	}
}

void on_chkbtn_2_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton)) {
	char neofetch[]	="neofetch";
    g_print("Seleccionado: %s \n", neofetch);
	}
	else {
		g_print("neofetch desmarcado\n");
	}
}

void on_chkbtn_3_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
	if (gtk_toggle_button_get_active(togglebutton)) {
	char wget[]		="wget";
    g_print("Seleccionado: %s \n", wget);
	}
	else {
		g_print("wget desmarcado\n");
	}
}

void on_process_end () {

	gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(builder, "window"), TRUE);	

}


void on_boton_clicked(GtkButton *boton, gpointer data) {

	gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(builder, "window"), FALSE);
  gchar *commandline, **command;


    // Ejecutar un comando usando la variable guardada
  commandline = g_strdup_printf("yay -S %s %s %s --noconfirm \n", git, neofetch, wget);
  

  g_shell_parse_argv(commandline, NULL, &command, NULL);
  g_free(commandline);
  g_spawn_async(NULL, command, NULL, G_SPAWN_SEARCH_PATH|G_SPAWN_DO_NOT_REAP_CHILD, NULL, NULL, NULL, NULL);
  g_strfreev(command);

}
	

void appActivate(GtkApplication *app, gpointer data) {
  // Cargamos la interfaz y asignamos los objetos
  builder       	= (GtkBuilder*)    gtk_builder_new_from_file("check.glade");
  window         	= (GtkWindow*)     gtk_builder_get_object(builder, "window");
  boton          	= (GtkButton*)     gtk_builder_get_object(builder, "boton");




  // Conectamos signals correspondientes
  g_signal_connect(boton, "clicked", (GCallback) on_boton_clicked, NULL);
  gtk_builder_connect_signals(builder, NULL);


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
  on_process_end ();
  return status;
}

