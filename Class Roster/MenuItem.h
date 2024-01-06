#ifndef MENUITEM_H
#define MENUITEM_H

#include <iostream>

using namespace std;

class MenuItem {
    public:
        MenuItem(char promptChar, string title) {
            mPromptChar = promptChar;
            mTitle = title;
        }

        virtual bool select() = 0;
        virtual void display() = 0;
        char getPromptChar() {
            return mPromptChar;
        }
        
        // Creating a destructor for MenuItem
        // virtual ~MenuItem() {
        //     cout << "MenuItem " << mTitle << " deleted." << endl;
        // };

    protected:
        char mPromptChar;
        string mTitle;
};

#endif
