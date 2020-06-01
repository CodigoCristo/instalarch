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
GtkWidget 		*stack1;
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


char* concat(const char *s1, const char *s2)
{
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2)+1;
    char *result = malloc(len1 + len2 );
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 );
    return result;
}

void clearlocations() {
	GtkComboBox *listwidget;
	GtkListStore *list;
	// clear copydevices
	listwidget = (GtkComboBox *) gtk_builder_get_object(builder, "select_idioma2");
	list = (GtkListStore *) gtk_combo_box_get_model(listwidget);
	gtk_list_store_clear (list) ;
    // Clear installdevices
	gtk_list_store_clear (list) ;
	listwidget = (GtkComboBox *) gtk_builder_get_object(builder, "select_disco");
	list = (GtkListStore *) gtk_combo_box_get_model(listwidget);
	gtk_list_store_clear (list) ;
	// Clear homedevices
	gtk_list_store_clear (list) ;
	listwidget = (GtkComboBox *) gtk_builder_get_object(builder, "select_idioma1");
	list = (GtkListStore *) gtk_combo_box_get_model(listwidget);
	gtk_list_store_clear (list) ;
	
}


void initlocations() {
	GtkComboBox *listwidget;
	GtkTreeIter iter;
	GtkListStore *list;
	gchar **lines, *output, *device;
	gint i;
	gint status;


	listwidget = (GtkComboBox *) gtk_builder_get_object(builder, "select_disco");
	list = (GtkListStore *) gtk_combo_box_get_model(listwidget);
	int select_disco_count = 0;
	g_spawn_command_line_sync("sudo sh disco.sh disco", &output, NULL, &status, NULL);
	if (status == 0) {
		lines = g_strsplit(output, "\n", 0);
		for (i=0; lines[i] != NULL && strlen(lines[i])>0; i++) {
			gtk_list_store_append(list, &iter);
			gtk_list_store_set(list, &iter, 0, lines[i], -1);
		}
		select_disco_count = i;
		g_strfreev(lines);
	}
	g_free(output);
	if (select_disco_count != 0){
		system("echo");
	}



	listwidget = (GtkComboBox *) gtk_builder_get_object(builder, "select_idioma2");
	list = (GtkListStore *) gtk_combo_box_get_model(listwidget);
	int select_idioma1_count = 0;
	g_spawn_command_line_sync("sudo sh disco.sh key-terminal", &output, NULL, &status, NULL);
	if (status == 0) {
		lines = g_strsplit(output, "\n", 0);
		for (i=0; lines[i] != NULL && strlen(lines[i])>0; i++) {
			gtk_list_store_append(list, &iter);
			gtk_list_store_set(list, &iter, 0, lines[i], -1);
		}
		select_idioma1_count = i;
		g_strfreev(lines);
	}
	g_free(output);
	if (select_idioma1_count != 0){
		system("echo");
	}



	listwidget = (GtkComboBox *) gtk_builder_get_object(builder, "select_idioma1");
	list = (GtkListStore *) gtk_combo_box_get_model(listwidget);
	int select_idioma2_count = 0;
	g_spawn_command_line_sync("sudo sh disco.sh key-sistema", &output, NULL, &status, NULL);
	if (status == 0) {
		lines = g_strsplit(output, "\n", 0);
		for (i=0; lines[i] != NULL && strlen(lines[i])>0; i++) {
			gtk_list_store_append(list, &iter);
			gtk_list_store_set(list, &iter, 0, lines[i], -1);
		}
		select_idioma2_count = i;
		g_strfreev(lines);
	}
	g_free(output);
	if (select_idioma2_count != 0){
		system("echo");
	}


}


void on_gparted_clicked (GtkWidget *widget, gpointer user_data) {
	if (g_file_test("/usr/bin/gparted", G_FILE_TEST_EXISTS)) {
	system("/usr/bin/gparted");
	clearlocations();
	initlocations();
	}
}


int main(int argc, char *argv[])
{
	
	gtk_init(&argc, &argv);

	builder = gtk_builder_new_from_file ("instalarch.ui");
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	
	// Coloca el Título
 	gtk_window_set_title (GTK_WINDOW (window), "Instalar Arch Linux");
 	// Logo con la función FnPixbufCreate
 	gtk_window_set_icon(GTK_WINDOW(window), FnPixbufCreate("logo.svg"));
 	// Evitamos que sea redimensionable
 	gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_builder_connect_signals(builder, NULL);


	fondo = GTK_WIDGET(gtk_builder_get_object(builder, "fondo"));
	titulo = GTK_WIDGET(gtk_builder_get_object(builder, "titulo"));
	atras = GTK_WIDGET(gtk_builder_get_object(builder, "atras"));
	siguiente = GTK_WIDGET(gtk_builder_get_object(builder, "siguiente"));
	gparted = GTK_WIDGET(gtk_builder_get_object(builder, "gparted"));
	select_disco = GTK_WIDGET(gtk_builder_get_object(builder, "select_disco"));
	select_idioma1 = GTK_WIDGET(gtk_builder_get_object(builder, "select_idioma1"));
	select_idioma2 = GTK_WIDGET(gtk_builder_get_object(builder, "select_idioma2"));
	
	gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(builder, "select_disco"), TRUE);
	gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(builder, "select_idioma1"), TRUE);
	gtk_widget_set_sensitive ((GtkWidget *) gtk_builder_get_object(builder, "select_idioma2"), TRUE);
	initlocations();
	
	


	  // Variable para el Color
	  GdkColor color_panel1;
	  GdkColor color_panel2;
	  GdkColor color_titulo;
	  // Establecemos el Color
	  gdk_color_parse ("#222d46", &color_panel1);
	  gdk_color_parse ("#1e1d1e", &color_panel2);
	  gdk_color_parse ("#000000", &color_titulo);
	  // Selected hace referencia al Borde
	  gtk_widget_modify_bg(fondo, GTK_STATE_NORMAL, &color_panel2);
	  gtk_widget_modify_bg(siguiente, GTK_STATE_NORMAL, &color_panel2);
	  gtk_widget_modify_bg(atras, GTK_STATE_NORMAL, &color_panel2);
	  gtk_widget_modify_bg(gparted, GTK_STATE_NORMAL, &color_panel2);
	  gtk_widget_modify_bg(titulo, GTK_STATE_NORMAL, &color_titulo);




             

	gtk_widget_show_all (window);
	
	gtk_main ();
	
	return EXIT_SUCCESS;

}


