#include <iostream>
#include "mainWindow.h"
#include "tools/uiTools.tpp"

mainWindow::mainWindow(const Glib::RefPtr<Gtk::Application> app) : mainLoop(Glib::MainLoop::create()),
                                                                   contacts(),
                                                                   appServer()
{
    application = app;
    builder = uiTools::getBuilder("mainWindow");

    window = uiTools::getWidget<Gtk::Window>(builder, "mainWindow");
    viewportContacts = uiTools::getWidget<Gtk::Viewport>(builder, "pageContacts");
    viewportContacts->set_child(*contacts.getWidget());

    application->add_window(*window);
    window->signal_close_request().connect([this]
                                           { 
                                               appServer.stop();
                                               mainLoop->quit(); return false; },
                                           true);
    window->show();

    Glib::signal_idle().connect_once([this]
                                     { appServer.start(); });

    mainLoop->run();
}

mainWindow::~mainWindow()
{
    // dtor
}

void mainWindow::startServer()
{
    if (!appServer.isRunning())
        appServer.start();
}
