#include <iostream>
#include "Course.h"
#include <string>

using namespace std;

// These are the methods for the Course class

string Course::getCourseName() {
    return name;
}

string Course::getCourseTitle() {
    return title;
}

string Course::getInstructor() {
    return instructor;
}

int Course::getStudentCount() {
    return numStudents;
}

void Course::setCourseName(string theName) {
    name = theName;
}

void Course::setCourseTitle(string theTitle) {
    title = theTitle;
}

void Course::setInstructor(string theInstructor) {
    instructor = theInstructor;
}

void Course::setStudentCount(int count) {
    numStudents = count;
}