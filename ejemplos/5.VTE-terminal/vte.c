#include <gtk/gtk.h>
#include <vte/vte.h> // todas esas cosas.
#define Length(arr) (sizeof (arr) / sizeof ((arr)[0]))

GtkApplication   *app;
GtkBuilder       *builder;
GtkWindow        *window;
GtkButton        *boton;
GtkLabel         *termTitle;
GtkViewport		 *termView;
VteTerminal      *term;
VtePty           *pty;


void on_boton_clicked(GtkButton *btn, gpointer data) {

    char *comando;
    comando = "ping -c 5 8.8.8.8 && read line \n";
    vte_terminal_feed_child (term, comando, -1);
    

}



// Con esta función, se abre la shell del usuario en la terminal de la pagina de la terminal
void spawnShell(VteTerminal *term, gint status, gpointer data)
{

  char **termArgv = (char *[]) { getenv("SHELL"), NULL };

  vte_terminal_spawn_async(
    term,            
    VTE_PTY_DEFAULT, 
    NULL,            
    termArgv,        
    NULL,            
    G_SPAWN_DEFAULT, 
    NULL,            
    NULL,            
    NULL,            
    -1,              
    NULL,           
    NULL,            
    NULL             
  );
}



void appActivate(GtkApplication *app, gpointer data) {
  // Cargamos la interfaz y asignamos los objetos
  builder       	= (GtkBuilder*)    gtk_builder_new_from_file("vte.glade");
  window         	= (GtkWindow*)     gtk_builder_get_object(builder, "window");
  boton          	= (GtkButton*)     gtk_builder_get_object(builder, "boton");
  termTitle      	= (GtkLabel*)      gtk_builder_get_object(builder, "termTitle");
  termView        	= (GtkViewport*)   gtk_builder_get_object(builder, "termView");
  term           	= (VteTerminal*)   vte_terminal_new(); 
  spawnShell(term, 0, NULL); // Hacemos que aparezca nuestra shell

  gtk_container_add((GtkContainer*) termView, (GtkWidget*) term);


  gtk_builder_connect_signals(builder, NULL);
  // Mostramos todos los widgets dentro de "window"
  gtk_widget_show_all((GtkWidget*) window);
  // Y agregamos nuestra ventana a la applicación :)
  gtk_application_add_window(app, window);
}


int main(int argc, char **argv) {
  int status;

  // Creamos una nueva applicación
  app = gtk_application_new("com.github", G_APPLICATION_FLAGS_NONE);
  // Conectamos la función previa con nuestra appliación
  g_signal_connect(app, "activate", (GCallback) appActivate, NULL);

  // Corremos la appliación
  status = g_application_run((GApplication*) app, argc, argv);
  // Sinceramente, no sé que hace esto xd véase la documentación de GObject para más información.
  g_object_unref(app);

  return status;
}

