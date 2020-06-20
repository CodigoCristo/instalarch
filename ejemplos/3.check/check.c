#include <gtk/gtk.h>

GtkApplication *app;
GtkBuilder     *builder;
GtkWindow      *win;
GtkBox         *box;

char *wget = "";
char *git  = "";
char *lua  = "";

void onToggle(GtkToggleButton *tbtn, gpointer data) {
  gboolean isActive = gtk_toggle_button_get_active(tbtn);
  const gchar *name = gtk_widget_get_name((GtkWidget*) tbtn);

  if (isActive) {
    if (g_strcmp0(name, "wget") == 0) wget = "wget";
    if (g_strcmp0(name, "git") == 0) git = "git";
    if (g_strcmp0(name, "lua") == 0) lua = "lua";
  } else {
    if (g_strcmp0(name, "wget") == 0) wget = "";
    if (g_strcmp0(name, "git") == 0) git = "";
    if (g_strcmp0(name, "lua") == 0) lua = "";
  }

  g_print("Seleccionado: %s %s %s\n", wget, git, lua);
}

void onInstall(GtkButton *btn, gpointer data) {
  gchar *cmd, **cmdp;
  cmd = g_strdup_printf("yay -S %4s %3s %3s --noconfirm \n", wget, git, lua);
  g_print("Ejecutando: %s", cmd);

  g_shell_parse_argv(cmd, NULL, &cmdp, NULL);
  g_spawn_async(NULL, cmdp, NULL, G_SPAWN_SEARCH_PATH|G_SPAWN_DO_NOT_REAP_CHILD, NULL, NULL, NULL, NULL);
}

void onActivate(GtkApplication *app, gpointer data) {
  builder =              gtk_builder_new_from_file("check.ui");
  win     = (GtkWindow*) gtk_builder_get_object(builder, "win");
  box     = (GtkBox*)    gtk_builder_get_object(builder, "box");
  gtk_builder_connect_signals(builder, NULL);

  gtk_window_present(win);
  gtk_application_add_window(app, win);
}

int main(int argc, char **argv) {
  int status;

  app = gtk_application_new(NULL, 0);
  g_signal_connect(app, "activate", (GCallback) onActivate, NULL);

  status = g_application_run((GApplication*) app, argc, argv);
  g_object_unref(app);

  return status;
}