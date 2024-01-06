#ifndef _MENU_COMMAND_H_
#define _MENU_COMMAND_H_

#include <iostream>
#include <functional>
#include "MenuItem.h"

using namespace std;

class MenuCommand : public MenuItem {
    public:
        MenuCommand(char promptChar, string title, function<bool()> action);
        bool select();
        void display();
        // Added MenuCommand destructor
        // ~MenuCommand();

    private:
        function<bool()> action;
};

#endif
