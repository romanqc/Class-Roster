#include <iostream>
#include "MenuItem.h"
#include "Menu.h"
#include "MenuCommand.h"
#include "CourseCatalog.h"

using namespace std;

int main(int argc, char *argv[]) {
    int newLineType;
    string directory;

    cout << "Enter New Line: ";
    cin >> newLineType;
    cin.ignore();

    cout << "Enter Directory: ";
    getline(cin, directory); 
    
    CourseCatalog catalog(newLineType, directory);

    Menu mainMenu('0', "Main");

    // Creating shared_ptr objects for MenuCommand and adding them to the mainMenu
    mainMenu.addMenuItem(make_shared<MenuCommand>('1', "List Courses", [&catalog]() {
        cout << "You chose 'List Courses'" << endl;
        catalog.listCourses();
        return true;
    }));

    shared_ptr<Menu> courseMenuPtr = make_shared<Menu>('2', "Edit Courses");

    // Creating shared_ptr objects for MenuCommand and adding them to courseMenuPtr
    // Adding shared pointer for editCourseName
    courseMenuPtr -> addMenuItem(make_shared<MenuCommand>('1', "Edit Course Name", [&catalog]() {
        cout << "You chose 'Edit Course Name'" << endl;
        catalog.editCourseName();
        return true;
    }));

    // Adding shared pointer for editCourseTitle
    courseMenuPtr -> addMenuItem(make_shared<MenuCommand>('2', "Edit Course Title", [&catalog]() {
        cout << "You chose 'Edit Course Title'" << endl;
        catalog.editCourseTitle();
        return true;
    }));

    // Adding shared pointer for editCourseInstructor
    courseMenuPtr -> addMenuItem(make_shared<MenuCommand>('3', "Edit Course Instructor", [&catalog]() {
        cout << "You chose 'Edit Course Instructor'" << endl;
        catalog.editCourseInstructor();
        return true;
    }));

    // Adding shared pointer for editCourseEnrollment
    courseMenuPtr -> addMenuItem(make_shared<MenuCommand>('4', "Edit Course Enrollment", [&catalog]() {
        cout << "You chose 'Edit Course Enrollment'" << endl;
        catalog.editCourseEnrollment();
        return true;
    }));

    courseMenuPtr -> addMenuItem(make_shared<MenuCommand>('b', "Back", []() {
        return false;
    }));

    mainMenu.addMenuItem(courseMenuPtr);

    mainMenu.addMenuItem(make_shared<MenuCommand>('3', "Add New Course", [&catalog]() {
        cout << "You chose 'Add New Course'" << endl;
        catalog.addNewCourse();
        return true;
    }));

    mainMenu.addMenuItem(make_shared<MenuCommand>('4', "Remove Course", [&catalog]() {
        cout << "You chose 'Remove Course'" << endl;
        catalog.removeCourse();
        return true;
    }));

    mainMenu.addMenuItem(make_shared<MenuCommand>('Q', "Quit", []() {
        return false;
    }));

    bool keepGoing = mainMenu.select();

    cout << "All Done!" << endl;

    return 0;
}
