#ifndef CONTACTSTAB_H
#define CONTACTSTAB_H

#include <gtkmm.h>
#include "../baseWidget.tpp"

class contactsTab : public baseWidget<Gtk::Paned>
{
    public:
        contactsTab();
        virtual ~contactsTab();

    protected:
    private:
};

#endif // CONTACTSTAB_H