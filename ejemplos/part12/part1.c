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
GtkWidget	*color1;
GtkWidget	*file1;
GtkWidget	*font1;
GtkWidget	*volume1;
GtkWidget	*scroll1;
GtkWidget	*frame1;
GtkWidget	*frame2;
GtkWidget	*frame3;
GtkWidget	*frame4;
GtkBuilder	*builder; 

GtkListStore	*liststore1;
GtkAdjustment	*adjustment2;

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
	color1 = GTK_WIDGET(gtk_builder_get_object(builder, "color1"));
	font1 = GTK_WIDGET(gtk_builder_get_object(builder, "font1"));
	file1 = GTK_WIDGET(gtk_builder_get_object(builder, "file1"));
	volume1 = GTK_WIDGET(gtk_builder_get_object(builder, "volume1"));
	frame1 = GTK_WIDGET(gtk_builder_get_object(builder, "frame1"));
	frame2 = GTK_WIDGET(gtk_builder_get_object(builder, "frame2"));
	frame3 = GTK_WIDGET(gtk_builder_get_object(builder, "frame3"));
	frame4 = GTK_WIDGET(gtk_builder_get_object(builder, "frame4"));
	scroll1 = GTK_WIDGET(gtk_builder_get_object(builder, "scroll1"));

	liststore1 = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));
	adjustment2 = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment2"));

	/*******************
	struct GtkAdjustment {
                    gdouble lower,
                    gdouble upper,
                    gdouble step_increment,
                    gdouble page_increment,
                    gdouble page_size};
	****************************/

	/* alter the range of the scroll bar */
        gtk_range_set_range (GTK_RANGE(scroll1), 0, 100);

        GdkColor color; // default background color
        color.red = 0xcccc;
        color.green = 0xcccc;
        color.blue = 0xd900;
        gtk_widget_modify_bg(GTK_WIDGET(window), GTK_STATE_NORMAL, &color);

        color.red = 0xaaaa;
        color.green = 0xaaaa;
        color.blue = 0xeeee;
        gtk_widget_modify_bg(frame1, GTK_STATE_NORMAL, &color);

        color.red = 0xaaaa;
        color.green = 0xeeee;
        color.blue = 0xaaaa;
        gtk_widget_modify_bg(frame2, GTK_STATE_NORMAL, &color);

        color.red = 0xeeee;
        color.green = 0xaaaa;
        color.blue = 0xaaaa;
        gtk_widget_modify_bg(frame3, GTK_STATE_NORMAL, &color);

        color.red = 0xeeee;
        color.green = 0xeeee;
        color.blue = 0xaaaa;

        gtk_widget_modify_bg(frame4, GTK_STATE_NORMAL, &color);

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

void	on_color1_color_set (GtkColorButton *c) {
	GdkRGBA color;
	gtk_color_chooser_get_rgba (GTK_COLOR_CHOOSER(c), &color);
	printf("red %f\n", color.red);
	printf("green %f\n", color.green);
	printf("blue %f\n", color.blue);
	printf("alpha %f\n\n", color.alpha);
	/* just for fun, lets change the scrollbar background */
	gtk_widget_override_background_color (scroll1, GTK_STATE_FLAG_NORMAL, &color);
	}

void	on_file1_file_set(GtkFileChooserButton *f) {
	printf("file name = %s\n", gtk_file_chooser_get_filename (GTK_FILE_CHOOSER(f)) );
	printf("folder name = %s\n", gtk_file_chooser_get_current_folder (GTK_FILE_CHOOSER(f)) );
	}

void	on_font1_font_set(GtkFontButton *f1) {
	printf("font name = %s\n", gtk_font_button_get_font_name (f1) );
	}

void	on_volume1_value_changed (GtkVolumeButton *v1) {

	/*******************************************************************
	The function:
		void gtk_scale_button_set_value (GtkScaleButton *, gdouble)
	can be used to set the volume control to a particular value.
	********************************************************************/

	printf("volume scale = %f\n", gtk_scale_button_get_value(GTK_SCALE_BUTTON(v1)) );
	}

void    on_scroll1_value_changed(GtkRange *r) {
        gdouble x = gtk_range_get_value (r);
	printf("scroll = %d\n", (int) x );
        }

