// -----------------------------------------------------------
// STRUCTURES.H
// Contains all structure definitions used in the project
// -----------------------------------------------------------

#ifndef STRUCTURES_H        // Header guard to prevent multiple inclusion
#define STRUCTURES_H

#include<string>            // Required for string data type
using namespace std;

// -----------------------------------------------------------
// FORWARD DECLARATIONS
// -----------------------------------------------------------

// Faculty class is used as a pointer inside structures
class Faculty;

// Forward declaration of Slot and Course structures
struct Slot;
struct Course;

// -----------------------------------------------------------
// STRUCTURE: UnitTime
// Stores start and end time of a lecture or lab
// -----------------------------------------------------------
struct UnitTime {
    string Start_Time;      // Lecture start time (e.g., 8:30)
    string End_Time;        // Lecture end time (e.g., 9:20)
};

// -----------------------------------------------------------
// STRUCTURE: Faculty_Available
// Represents availability of faculty for a specific time slot
// -----------------------------------------------------------
struct Faculty_Available {
    UnitTime t;             // Time duration of the slot
    bool isAvailable;       // Availability status (true = available)
};

// -----------------------------------------------------------
// STRUCTURE: Course
// Represents a university course
// -----------------------------------------------------------
struct Course {
    string courseID;            // Unique course code (e.g., CS101)
    string courseName;          // Name of the course
    int credit_hours;           // Credit hours of the course
    string department;          // Department offering the course
    int semester;               // Semester in which course is offered
    string CourseType;          // Type of course (Theory / Lab)
    Faculty* assignedFaculty;   // Pointer to assigned faculty
    Slot* ClassSchedule;        // Pointer to scheduled class slot
    bool isScheduled;           // Scheduling status
};

// -----------------------------------------------------------
// STRUCTURE: Slot
// Represents a scheduled class slot in timetable
// -----------------------------------------------------------
struct Slot {
    UnitTime Times;             // Start and end time of the slot
    string Day;                 // Day of the week (Monday, Tuesday, etc.)
    pair<int, int> SlotNo;      // Slot number range (start, end)
    Faculty* Instructor;        // Assigned faculty for the slot
    int semester;               // Semester for which slot is assigned
    string section = "A";       // Section name (default is A)
    Course SUBJECT;             // Course being taught in this slot
    bool SlotStatus;            // Slot status (true = approved/active)
};



#endif   // End of STRUCTURES_H
