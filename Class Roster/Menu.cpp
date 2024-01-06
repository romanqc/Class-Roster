#include <iostream>
#include "Menu.h"

Menu::Menu(char commandChar, string title) : MenuItem(commandChar, title) {}

void Menu::addMenuItem(shared_ptr<MenuItem> item) {  // Use shared_ptr
    mItems[item->getPromptChar()] = item;
}

void Menu::displayMenu() {
    cout << "==== " << mTitle << " MENU ====" << endl;
    for (auto &menuItem : mItems) {
        menuItem.second -> display();
    }
}

bool Menu::promptUser() {
    char command;

    cout << "Enter choice: ";
    cin >> command;
    
    // finding items to select from char command
    auto it = mItems.find(command);
    if (it != mItems.end()) {
        return it -> second -> select();
    }

    cout << "Unknown Menu Selection" << endl;

    return true;
}

bool Menu::select() {
    for (;;) {
        displayMenu();

        bool keepGoing = promptUser();

        if (!keepGoing) {
            break;
        }
    }
    return true;
}

void Menu::display() {
    cout << mPromptChar << "> " << mTitle << ">" << endl;
}

// Added Menu destructor
// Menu::~Menu() {
//     cout << "Menu " << mTitle << " deleted." << endl;
// }