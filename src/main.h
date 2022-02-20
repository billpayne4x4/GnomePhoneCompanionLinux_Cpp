#ifndef MAIN_H
#define MAIN_H

#include <gtkmm.h>

namespace gpc
{
    Glib::RefPtr<Gtk::Application> m_app;
    Gtk::ApplicationWindow *m_window;

    void on_app_activate(Glib::RefPtr<Gtk::Application> app, Gtk::ApplicationWindow *window);
}

#endif // MAIN_H