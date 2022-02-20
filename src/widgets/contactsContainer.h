#ifndef CONTACTSCONTAINER_H
#define CONTACTSCONTAINER_H

#include <gtkmm.h>
#include "baseWidget.tpp"

namespace gpc
{
    namespace widgets
    {
        class contactsContainer : public baseWidget<Gtk::Label>
        {
        public:
            contactsContainer();
            virtual ~contactsContainer();

        protected:
        private:
        };
    }
}

#endif // CONTACTSCONTAINER_H