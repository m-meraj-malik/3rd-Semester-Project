#ifndef STRUCTURES_H
#define STRUCTURES_H

#include<string>
using namespace std;

class Faculty;

struct Slot;
struct Course;
// ////Structure Declarations
struct UnitTime{
	string Start_Time;
	string End_Time;
};

struct Faculty_Available
{
	UnitTime t;
	bool isAvailable; 
};

struct Course{
		string courseID;
		string courseName;
		int credit_hours;
		string department;
		int semester;
		string CourseType;	//Theory , Lab
		Faculty* assignedFaculty;
		Slot* ClassSchedule;
		bool isScheduled;
};

struct Slot{
	UnitTime Times;
	string Day;
	pair<int, int> SlotNo; //Start, End
	Faculty* Instructor;
	int semester;
	string section = "A";
    Course SUBJECT;
	bool SlotStatus;
};

// struct FacultyComplaints
// {
// 	string subject;
// 	string complain;
// 	Faculty* Faculty_A;
// 	string dept;
// 	bool status;
// };

// struct StudentComplaints
// {
// 	string subject;
// 	string complain;
// 	Student* Student_A;
// 	string dept;
// 	bool status;
// };
	

#endif
