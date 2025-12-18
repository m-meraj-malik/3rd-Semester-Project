// -----------------------------------------------------------
// FACULTY.H
// Header file for Faculty class
// -----------------------------------------------------------

#ifndef FACULTY_H        // Header guard to prevent multiple inclusion
#define FACULTY_H

// -----------------------------------------------------------
// REQUIRED HEADER FILES
// -----------------------------------------------------------
#include "User.h"        // Base class User
#include "Structures.h"  // Structures like Course, Slot, Faculty_Available
#include<vector>         // For dynamic arrays
#include<string>         // For string data type
#include<iomanip>        // For formatted output
#include<map>            // For map container
#include<algorithm>     // For algorithms like find, sort

using namespace std;

// -----------------------------------------------------------
// FORWARD DECLARATIONS
// These classes are used as references/pointers elsewhere
// -----------------------------------------------------------
class Department;
class Student;

// -----------------------------------------------------------
// FACULTY CLASS
// Inherits from User class
// Represents faculty members in the university
// -----------------------------------------------------------
class Faculty : public User {

private:
    // -------------------------
    // FACULTY ATTRIBUTES
    // -------------------------

    string designation;                    // Designation (Professor, Lecturer, etc.)
    vector<string> qualifications;         // Academic qualifications list
    vector<string> specializedCourses;     // Courses faculty specializes in

    // Weekly availability for faculty
    // Index represents day (0 = Monday, 5 = Saturday)
    vector<Faculty_Available> AVAILABLE[6];

    // List of courses officially assigned to faculty
    vector<Course> assignedCourses;

    // Reserved for future use (time slots assigned to faculty)
    // vector<Slot> MySlots;

public:
    // -------------------------------------------------------
    // CONSTRUCTORS
    // -------------------------------------------------------

    // Parameterized constructor
    // Initializes faculty along with base User attributes
    Faculty(string& ID, string& pass, string& nam, string& em,
            string& gen, string& ph, string& dept,
            string& regDte, string& desig);

    // Default constructor
    Faculty();

    // -------------------------------------------------------
    // DESIGNATION FUNCTIONS
    // -------------------------------------------------------

    // Returns faculty designation
    string getDesignation() const;

    // Sets faculty designation
    void setDesignation(const string& desig);

    // -------------------------------------------------------
    // AVAILABILITY FUNCTIONS
    // -------------------------------------------------------

    // Allows faculty to set weekly availability
    void setWeeklyAvailability();

    // Returns availability (currently implementation-dependent)
    vector<Faculty_Available> getWeeklyAvailability();

    // Displays availability for a specific day
    void displayAvailabilityByDay(const int& day);

    // -------------------------------------------------------
    // QUALIFICATION MANAGEMENT
    // -------------------------------------------------------

    // Add qualification to faculty profile
    void setQualifications(string qual);

    // Remove a qualification
    void removeQualifications(string qual);

    // Get list of qualifications
    vector<string> getQualifications();

    // Display all qualifications
    void displayQualifications();

    // -------------------------------------------------------
    // SPECIALIZED COURSES MANAGEMENT
    // -------------------------------------------------------

    // Add a specialized course
    void setSpecializedCourses(string C);

    // Remove a specialized course
    void removeSpecializedCourses(string C);

    // Get list of specialized courses
    vector<string> getSpecializedCourses();

    // -------------------------------------------------------
    // COURSE ASSIGNMENT
    // -------------------------------------------------------

    // Add course assigned by department
    void addAssignedCourses(Course& COUR);

    // Check whether a course is assigned to faculty
    bool checkAssignedCourse(string Course_name);

    // Get all assigned courses
    vector<Course> getAssignedCourses();

    // Display assigned courses
    void displayAssignedCourses();

    // Calculate total teaching hours
    int getCurrentTeachingHours();

    // -------------------------------------------------------
    // DEPARTMENT & TIMETABLE FUNCTIONS (FUTURE USE / PARTIAL)
    // -------------------------------------------------------

    // Display department time-table incharge
    void displayDepartmentTimeTableIncharge();

    // Return department time-table incharge
    string getDepartmentTimeTableIncharge();

    // Slot management
    void AddSlot();
    void removeSlot();
    void pendingSlots();
    void ApprovedSlots();

    // Complaint management
    void addComplain();
    void ComplaintStatus();

    // -------------------------------------------------------
    // TIMETABLE DISPLAY FUNCTIONS
    // -------------------------------------------------------

    // Display daily schedule for given day
    void displayDailySchedule(const int& day);

    // Display full timetable
    void displayTimeTable();

    // Return complete timetable structure
    map<string, vector<Slot>> getTimeTable();

    // Timetable generateDepartmentTimetable(string semester);
};

#endif   // End of FACULTY_H
