#include <iostream>

#include "MenuCommand.h"

using namespace std;

MenuCommand::MenuCommand(char promptChar, string title, function<bool()> action) : MenuItem(promptChar, title), action(action) {}

bool MenuCommand::select() {
    // Calling Lambda Expression
    return action();
}

void MenuCommand::display() {
    cout << mPromptChar << "> " << mTitle << endl;
}

// Added MenuCommand destructor
// MenuCommand::~MenuCommand() {
//     cout << "MenuCommand " << mTitle << " deleted." << endl;
// }
