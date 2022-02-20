#ifndef UITOOLS_H
#define UITOOLS_H

#include <gtkmm.h>
#include <iostream>
#include "../config.h"

class uiTools
{
public:
    static Glib::RefPtr<Gtk::Builder> getBuilder(const std::string &resource)
    {
        auto builder = Gtk::Builder::create();

        try
        {
            builder->add_from_resource(config::resourcePrefix + resource);
        }
        catch (const Glib::FileError &ex)
        {
            std::cerr << "FileError: " << ex.what() << std::endl;
            return NULL;
        }
        catch (const Glib::MarkupError &ex)
        {
            std::cerr << "MarkupError: " << ex.what() << std::endl;
            return NULL;
        }
        catch (const Gtk::BuilderError &ex)
        {
            std::cerr << "BuilderError: " << ex.what() << std::endl;
            return NULL;
        }

        return builder;
    }

    template <class T>
    static T *getWidget(Glib::RefPtr<Gtk::Builder> &builder, const std::string &widgetId)
    {
        T *widget = builder->get_widget<T>(widgetId);
        if (widget == NULL)
        {
            std::cerr << "Could not get the widget " << widgetId << std::endl;
            return NULL;
        }

        return widget;
    }

protected:
private:
};

#endif // UITOOLS_H