#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <map>
#include <memory>
#include "MenuItem.h"

using namespace std;

class Menu : public MenuItem {
public:
    Menu(char commandChar, string title);
    void addMenuItem(shared_ptr<MenuItem> item);  // Use shared_ptr
    bool select();
    void display();
    // Added Menu destructor
    // virtual ~Menu();

private:
    void displayMenu();
    bool promptUser();
    map<char, shared_ptr<MenuItem>> mItems;  // Use shared_ptr
};

#endif
