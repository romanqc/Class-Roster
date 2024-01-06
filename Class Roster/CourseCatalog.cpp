#include <iostream>
#include "CourseCatalog.h"
#include "Course.h"
#include "Menu.h"

using namespace std;

CourseCatalog::CourseCatalog(int newlineType, string &directory) {
    string filePath = directory + "/courses.dat";  // Save the file path as a member variable
    fpath = filePath;
    // Debug: Print the file path
    cout << "File Path: " << filePath << endl;

    // Open the file in read and write mode simultaneously
    mFileStream.open(filePath, ios::in | ios::out | ios::binary);

    // Check if the file already exists, if not, create it
    if (!mFileStream) {
        cerr << "File does not exist. Creating a new file." << endl;
        mFileStream.clear();  // Clear error flags
        mFileStream.open(filePath, ios::out | ios::binary);  // Create the file
        mFileStream.close();  // Close the file after creation
        mFileStream.open(filePath, ios::in | ios::out | ios::binary);  // Reopen in read and write mode
    }

    // Set newline type based on the user input
    if (newlineType == 1) {
        // Set newline type for MacOS (1 byte)
        mFileStream << '\n';
    } else if (newlineType == 2) {
        // Set newline type for Windows (2 bytes)
        mFileStream << "\r\n";
    }

    loadDataFromFile();

    // Initialize mNameToIndexMap based on the loaded courses
    for (const auto &entry : mCourses) {
        CoursePtr course = entry.second;
        mNameToIndexMap[course->getCourseName()] = mFileStream.tellp();
    }
}

void CourseCatalog::addNewCourse() {
    CoursePtr course = make_shared<Course>();  // Create a shared_ptr for Course
    string name, title, instructor;
    int count;

    // Prompting the user to input course information
    cin.ignore();

    cout << "Enter course name: ";
    getline(cin, name);
    course -> setCourseName(name);

    cout << "Enter course title: ";
    getline(cin, title);
    course -> setCourseTitle(title);

    cout << "Enter course instructor: ";
    getline(cin, instructor);
    course -> setInstructor(instructor);

    cout << "Enter number of students: ";
    cin >> count;
    course -> setStudentCount(count);

    // Adding the name to the course map
    mCourses[name] = course;
}

void CourseCatalog::listCourses() {
    cout << "Courses" << endl;
    cout << string(70, '=') << endl;

    // Iterating over the map and printing out the CourseName, CourseTitle, Instructor
    // and NumberOfStudents in a row.
    for (auto &entry : mCourses) {
        CoursePtr course = entry.second;
        cout << course -> getCourseName() << "  " << course -> getCourseTitle() << " " << course -> getInstructor() << " (" << course -> getStudentCount() << ")" << endl;
    }

    cout << string(70, '=') << endl;
}

void CourseCatalog::removeCourse() {
    string courseName;
    cout << "Enter the name of the course to remove: ";
    cin.ignore();
    getline(cin, courseName);

    // Removing the course based on a name selection from user input courseName
    auto it = mCourses.find(courseName);
    if (it != mCourses.end()) {
        mCourses.erase(it);
        cout << "Removing " << courseName << endl;
    } else {
        cout << "Course " << courseName << " does not exist." << endl;
    }
}

void CourseCatalog::editCourseName() {
    string currentName, newName;
    cout << "Enter the name of the course to rename: ";
    cin.ignore();
    getline(cin, currentName);

    auto it = mCourses.find(currentName);
    if (it != mCourses.end()) {
        CoursePtr course = it -> second;
        cout << "Enter the new name for the course: ";
        getline(cin, newName);

        // Check if the new name already exists
        if (mCourses.find(newName) == mCourses.end()) {
            // Update the course name within the Course object
            course->setCourseName(newName);

            // Update the course name in the map
            mCourses[newName] = course;
            mCourses.erase(it);

            cout << currentName << " renamed to " << newName << endl;
        } else {
            cout << "Course with name " << newName << " already exists." << endl;
        }
    } else {
        cout << "Course " << currentName << " does not exist." << endl;
    }
}

void CourseCatalog::editCourseTitle() {
    string courseName, newTitle;
    cout << "Enter the name of the course to edit the title of: ";
    cin.ignore();
    getline(cin, courseName);

    auto it = mCourses.find(courseName);
    if (it != mCourses.end()) {
        CoursePtr course = it->second;
        cout << "Enter the new title for the course: ";
        getline(cin, newTitle);

        // Update the course title
        course -> setCourseTitle(newTitle);

        cout << courseName << " title changed to: " << newTitle << endl;
    } else {
        cout << "Course " << courseName << " does not exist." << endl;
    }
}

void CourseCatalog::editCourseInstructor() {
    string courseName, newInstructor;
    cout << "Enter the name of the course to edit the instructor name for: ";
    cin.ignore();
    getline(cin, courseName);

    auto it = mCourses.find(courseName);
    if (it != mCourses.end()) {
        CoursePtr course = it->second;
        cout << "Enter the new instructor name for the course: ";
        getline(cin, newInstructor);

        // Update the course instructor
        course -> setInstructor(newInstructor);

        cout << courseName << " Instructor changed to: " << newInstructor << endl;
    } else {
        cout << "Course " << courseName << " does not exist." << endl;
    }
}

void CourseCatalog::editCourseEnrollment() {
    string courseName;
    int newEnrollment;
    cout << "Enter the name of the course to edit enrollment for: ";
    cin.ignore();
    getline(cin, courseName);

    auto it = mCourses.find(courseName);
    if (it != mCourses.end()) {
        CoursePtr course = it->second;
        cout << "Enter the new enrollment for the course: ";
        cin >> newEnrollment;

        // Update the course enrollment
        course -> setStudentCount(newEnrollment);

        cout << courseName << " Enrollment changed to: " << newEnrollment << endl;
    } else {
        cout << "Course " << courseName << " does not exist." << endl;
    }
}

// Add this member function to CourseCatalog
void CourseCatalog::saveCourse(Course &course) {
    mFileStream.clear(); // Clear any error flags
    mFileStream.seekp(0); // Move the write position to the beginning

    // Write course data to the file with appropriate padding
    mFileStream << std::left << std::setfill('\0')
                << std::setw(32) << course.getCourseName()
                << std::setw(32) << course.getCourseTitle()
                << std::setw(32) << course.getInstructor()
                << std::setw(3) << course.getStudentCount() << "\r";

    // Update the offset map
    mNameToIndexMap[course.getCourseName()] = mFileStream.tellp();
}

// Add this member function to CourseCatalog
void CourseCatalog::loadDataFromFile() {
    // Set the read position to the beginning of the file
    mFileStream.seekg(0);

    string line;
    while (getline(mFileStream, line)) {
        stringstream ss(line);
        string name, title, instructor;
        int count;

        // Use getline without '\0' as delimiter
        getline(ss, name, ',');
        getline(ss, title, ',');
        getline(ss, instructor, ',');
        ss >> count;


        // Ignore the newline character
        mFileStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Create a new course and add it to the map
        CoursePtr course = make_shared<Course>();
        course->setCourseName(name);
        course->setCourseTitle(title);
        course->setInstructor(instructor);
        course->setStudentCount(count);

        mCourses[name] = course;
    }
}

// Add a destructor to CourseCatalog
CourseCatalog::~CourseCatalog() {
    // Destructor: Save data when the object is destroyed
    for (const auto &entry : mCourses) {
        saveCourse(*entry.second);
    }
    mFileStream.close(); // Close the file when the object is destroyed
}