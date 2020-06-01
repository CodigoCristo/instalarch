//Créditos: 
// @Miqueas2020
// @nahuelwexd
// @Bourne_Again

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>
#include <libintl.h>
#include <locale.h>
#include <sys/wait.h> 
#define _(String) gettext (String)
#define N_(String) String

GtkWidget		*window;
GtkWidget 		*fondo;
GtkWidget 		*sidebar;
GtkWidget 		*panel;
GtkWidget 		*control;
GtkWidget 		*stack;
GtkWidget 		*sig;
GtkWidget 		*atras;
GtkWidget 		*siguiente;
GtkWidget 		*titulo;
GtkWidget 		*gparted;
GtkWidget 		*select_disco;
GtkWidget 		*select_idioma1;
GtkWidget 		*select_idioma2;


GtkBuilder		*builder;


GdkPixbuf *FnPixbufCreate(const gchar * filename)
{
   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);

   if(!pixbuf)
   {
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}



static void
on_back_button_clicked (GtkButton *button, GtkStack *stack)
{
  const gchar *seq[] = { "Bienvenido", "Idioma", "Discos", "Particiones", "Usuario", "Escritorio", "Programas", "Extras", "Instalación", "Finalizar" };
  const gchar *vis;
  gint i;

  vis = gtk_stack_get_visible_child_name (stack);

  for (i = 1; i < G_N_ELEMENTS (seq); i++)
    {
      if (g_strcmp0 (vis, seq[i]) == 0)
        {
          gtk_stack_set_visible_child_full (stack, seq[i - 1], GTK_STACK_TRANSITION_TYPE_SLIDE_RIGHT);
          break;
        }
    }
}

static void
on_forward_button_clicked (GtkButton *button, GtkStack *stack)
{
  const gchar *seq[] = { "Bienvenido", "Idioma", "Discos", "Particiones", "Usuario", "Escritorio", "Programas", "Extras", "Instalación", "Finalizar" };
  const gchar *vis;
  gint i;

  vis = gtk_stack_get_visible_child_name (stack);

  for (i = 0; i < G_N_ELEMENTS (seq) - 1; i++)
    {
      if (g_strcmp0 (vis, seq[i]) == 0)
        {
          gtk_stack_set_visible_child_full (stack, seq[i + 1], GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT);
          break;
        }
    }
}


static void
update_back_button_sensitivity (GtkStack *stack, GParamSpec *pspec, GtkWidget *button)
{
  const gchar *vis;

  vis = gtk_stack_get_visible_child_name (stack);
  gtk_widget_set_sensitive (button, g_strcmp0 (vis, "Bienvenido") != 0);
}

static void
update_forward_button_sensitivity (GtkStack *stack, GParamSpec *pspec, GtkWidget *button)
{
  const gchar *vis;

  vis = gtk_stack_get_visible_child_name (stack);
  gtk_widget_set_sensitive (button, g_strcmp0 (vis, "Finalizar") != 0);
}




int main(int argc, char *argv[])
{
	
	gtk_init(&argc, &argv);

	builder = gtk_builder_new_from_file ("./data/gtk/instalarch.ui");
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	
	// Coloca el Título
 	gtk_window_set_title (GTK_WINDOW (window), "Instalar Arch Linux");
 	// Logo con la función FnPixbufCreate
 	gtk_window_set_icon(GTK_WINDOW(window), FnPixbufCreate("./data/icons/logo.svg"));
 	// Evitamos que sea redimensionable
 	gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_builder_connect_signals(builder, NULL);


	fondo = GTK_WIDGET(gtk_builder_get_object(builder, "fondo"));
	titulo = GTK_WIDGET(gtk_builder_get_object(builder, "titulo"));
	stack = GTK_WIDGET(gtk_builder_get_object(builder, "stack"));
	gparted = GTK_WIDGET(gtk_builder_get_object(builder, "gparted"));
	select_disco = GTK_WIDGET(gtk_builder_get_object(builder, "select_disco"));
	select_idioma1 = GTK_WIDGET(gtk_builder_get_object(builder, "select_idioma1"));
	select_idioma2 = GTK_WIDGET(gtk_builder_get_object(builder, "select_idioma2"));
	
	gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(builder, "select_disco"), TRUE);
	gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(builder, "select_idioma1"), TRUE);
	gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(builder, "select_idioma2"), TRUE);


	  atras = GTK_WIDGET(gtk_builder_get_object(builder, "atras"));
	  g_signal_connect (atras, "clicked", (GCallback) on_back_button_clicked, stack);
	  g_signal_connect (stack, "notify::visible-child-name",
	                    (GCallback)update_back_button_sensitivity, atras);


	  siguiente = GTK_WIDGET(gtk_builder_get_object(builder, "siguiente"));
	  g_signal_connect (siguiente, "clicked", (GCallback) on_forward_button_clicked, stack);
	  g_signal_connect (stack, "notify::visible-child-name",
	                    (GCallback)update_forward_button_sensitivity, siguiente);
	


	  // Variable para el Color
	  GdkColor color_panel;
	  GdkColor color_titulo;
	  // Establecemos el Color
	  gdk_color_parse ("#1e1d1e", &color_panel);
	  gdk_color_parse ("#000000", &color_titulo);
	  // Selected hace referencia al Borde
	  gtk_widget_modify_bg(fondo, GTK_STATE_NORMAL, &color_panel);
	  gtk_widget_modify_bg(siguiente, GTK_STATE_NORMAL, &color_panel);
	  gtk_widget_modify_bg(atras, GTK_STATE_NORMAL, &color_panel);
	  gtk_widget_modify_bg(gparted, GTK_STATE_NORMAL, &color_panel);
	  gtk_widget_modify_bg(titulo, GTK_STATE_NORMAL, &color_titulo);




             

	gtk_widget_show_all (window);
	
	gtk_main ();
	
	return EXIT_SUCCESS;

}


