#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <gtkmm.h>
#include "../tools/uiTools.tpp"

template <typename T>
class baseWidget
{
public:
    baseWidget(const std::string &resource, const std::string &widgetId)
    {
        builder = uiTools::getBuilder(resource);
        widget = uiTools::getWidget<T>(builder, widgetId);
    }

    virtual ~baseWidget() {}

    T *getWidget() { return widget; }

protected:
    Glib::RefPtr<Gtk::Builder> builder;
    T *widget;

private:
};

#endif // BASEWIDGET_H