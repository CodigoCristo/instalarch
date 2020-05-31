#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

GtkWidget		*window;
GtkWidget		*panel1;
GtkWidget		*capa1;
GtkWidget		*capa2;
GtkWidget		*boton1;
GtkWidget		*texto1;
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


void	on_boton1_clicked(GtkButton *boton1, const gchar *str)
		{
			gtk_label_set_text (GTK_LABEL(texto1), "Hola Mundo GTK" );
			//g_print ("hola mundo");
		}


int main(int argc, char *argv[])
{
	
	gtk_init(&argc, &argv);

	builder = gtk_builder_new_from_file ("install.glade");
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	
	// Coloca el Título
 	gtk_window_set_title (GTK_WINDOW (window), "Instalar Arch Linux - Español");
 	// Logo con la función FnPixbufCreate
 	gtk_window_set_icon(GTK_WINDOW(window), FnPixbufCreate("logo.svg"));
 	// Evitamos que sea redimensionable
 	gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_builder_connect_signals(builder, NULL);

	panel1 = GTK_WIDGET(gtk_builder_get_object(builder, "panel1"));
	capa1 = GTK_WIDGET(gtk_builder_get_object(builder, "capa1"));
	capa2 = GTK_WIDGET(gtk_builder_get_object(builder, "capa2"));
	boton1 = GTK_WIDGET(gtk_builder_get_object(builder, "boton1"));
	texto1 = GTK_WIDGET(gtk_builder_get_object(builder, "texto1"));
	
	  // Variable para el Color
	  GdkColor color_panel1;
	  GdkColor color_panel2;

	  // Establecemos el Color para el Botón de la Suma
	  gdk_color_parse ("#222d46", &color_panel1);
	  gdk_color_parse ("#1e1d1e", &color_panel2);

	  // Selected hace referencia al Borde
	  gtk_widget_modify_bg(capa1, GTK_STATE_NORMAL, &color_panel1);
	  gtk_widget_modify_bg(capa2, GTK_STATE_NORMAL, &color_panel2);




	gtk_widget_show_all (window);
	
	gtk_main ();
	
	return EXIT_SUCCESS;

}



