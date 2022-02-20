#include <gtkmm.h>
#include <iostream>
#include "config.h"
#include "mainWindow.h"
#include "tools/debug.tpp"

void on_app_activate(Glib::RefPtr<Gtk::Application> app)
{
    mainWindow window(app);
}

int main(int argc, char *argv[])
{
    config::load();

    auto app = Gtk::Application::create("org.gnome_phone_companion");
    app->signal_activate().connect([app]()
                                   { on_app_activate(app); });

    return app->run(argc, argv);
}
