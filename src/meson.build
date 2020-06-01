sources = files (
    'instalarch.c'
)

deps = [
    gtk_dep
]

executable (
    meson.project_name (),
    sources, resources,
    dependencies: deps,
    install: true,
    gui_app: true
)
