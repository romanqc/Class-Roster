#ifndef COURSECATALOG_H
#define COURSECATALOG_H

#include "Course.h"
#include <map>
#include <memory>  // Include for shared_ptr
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
using namespace std;

class CourseCatalog {
    public:
        CourseCatalog(int newlineType, string &directory);
        ~CourseCatalog();

        void listCourses();
        void addNewCourse();
        void removeCourse();

        void editCourseName();
        void editCourseTitle();
        void editCourseInstructor();
        void editCourseEnrollment();

    private:
        // Course map mCourse
        map<string, CoursePtr> mCourses;
        map<string, int> mNameToIndexMap;
        fstream mFileStream;

        void saveCourse(Course &);
        void loadDataFromFile();
        string fpath;
};

#endif
