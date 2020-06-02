/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#+
#+     Glade / Gtk Programming
#+
#+     Copyright (C) 2019 by Kevin C. O'Kane
#+
#+     Kevin C. O'Kane
#+     kc.okane@gmail.com
#+     https://www.cs.uni.edu/~okane
#+     http://threadsafebooks.com/
#+
#+ This program is free software; you can redistribute it and/or modify
#+ it under the terms of the GNU General Public License as published by
#+ the Free Software Foundation; either version 2 of the License, or
#+ (at your option) any later version.
#+
#+ This program is distributed in the hope that it will be useful,
#+ but WITHOUT ANY WARRANTY; without even the implied warranty of
#+ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#+ GNU General Public License for more details.
#+
#+ You should have received a copy of the GNU General Public License
#+ along with this program; if not, write to the Free Software
#+ Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#+
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>

// Make them global

GtkWidget	*window;
GtkWidget	*fixed1;
GtkWidget	*button1;
GtkWidget	*label1;
GtkWidget	*label2;
GtkWidget	*radio1;
GtkWidget	*radio2;
GtkWidget	*radio3;
GtkWidget	*check1;
GtkWidget	*toggle1;
GtkWidget	*spin1;
GtkWidget	*switch1;
GtkWidget	*combo1;
GtkWidget	*entry1;
GtkBuilder	*builder; 

int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv); // init Gtk

//---------------------------------------------------------------------
// establish contact with xml code used to adjust widget settings
//---------------------------------------------------------------------
 
	builder = gtk_builder_new_from_file ("part1.glade");
 
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

        gtk_builder_connect_signals(builder, NULL);

	fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
	button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
	label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
	label2 = GTK_WIDGET(gtk_builder_get_object(builder, "label2"));
	radio1 = GTK_WIDGET(gtk_builder_get_object(builder, "radio1"));
	radio2 = GTK_WIDGET(gtk_builder_get_object(builder, "radio2"));
	radio3 = GTK_WIDGET(gtk_builder_get_object(builder, "radio3"));
	check1 = GTK_WIDGET(gtk_builder_get_object(builder, "check1"));
	toggle1 = GTK_WIDGET(gtk_builder_get_object(builder, "toggle1"));
	switch1 = GTK_WIDGET(gtk_builder_get_object(builder, "switch1"));
	combo1 = GTK_WIDGET(gtk_builder_get_object(builder, "combo1"));
	entry1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry1"));
	spin1 = GTK_WIDGET(gtk_builder_get_object(builder, "spin1"));

	gtk_widget_show(window);

	gtk_main();

	return EXIT_SUCCESS;
	}

void	on_button1_clicked (GtkButton *b) {
	char tmp[128];
	gdouble val = gtk_spin_button_get_value (GTK_SPIN_BUTTON(spin1));
	sprintf(tmp, "spin=%d", (int) val);
	gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) tmp);
	}

void	on_radio1_toggled(GtkRadioButton *b) {
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T) gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "Radio 1 Active");
	else gtk_label_set_text (GTK_LABEL(label2), (const gchar* ) "Radio 1 Not Active");
	}

void	on_radio2_toggled(GtkRadioButton *b) {
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T) gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "Radio 2 Active");
	else gtk_label_set_text (GTK_LABEL(label2), (const gchar* ) "Radio 2 Not Active");
	}

void	on_radio3_toggled(GtkRadioButton *b) {
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T) gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "Radio 3 Active");
	else gtk_label_set_text (GTK_LABEL(label2), (const gchar* ) "Radio 3 Not Active");
	}

void	on_check1_toggled(GtkCheckButton *b) {
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T) gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "Check 1 Active");
	else gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "Check 1 Not Active");
	}

void	on_toggle1_toggled(GtkToggleButton *b) {
	gboolean T = gtk_toggle_button_get_active(b);
	if (T) gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "Toggle 1 Active");
	else gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "Toggle 1 Not Active");
	}

void	on_switch1_state_set (GtkSwitch *s) {
	gboolean T = gtk_switch_get_active(s);
	if (T) gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "Switch 1 Active");
	else gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "Switch 1 Not Active");
	}
	
void	on_entry1_changed(GtkEntry *e) {
	char tmp[128];
	sprintf(tmp, "entry=%s", gtk_entry_get_text(e));
	gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) tmp);
	}

void	on_combo1_changed(GtkComboBox *c) {
	printf("combo1 changed entered\n");
	}
