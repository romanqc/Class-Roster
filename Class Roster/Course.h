#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <memory>  // Include for shared_ptr

using namespace std;

class Course {

public:
    // getters
    string getCourseName();
    string getCourseTitle();
    string getInstructor();
    int getStudentCount();

    // setters
    void setCourseName(string theName);
    void setCourseTitle(string theTitle);
    void setInstructor(string theInstructor);
    void setStudentCount(int count);

private:
    // variables
    string name;
    string title;
    string instructor;
    int numStudents;
};

// Define a shared_ptr alias for Course
using CoursePtr = shared_ptr<Course>;

#endif
