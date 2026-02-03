#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "Structures.h"
#include<vector>
#include<string>
#include<iomanip>
#include<map>
#include<algorithm>
using namespace std;

class Department;
class Faculty;

class Student : public User{
	private:
		int semester;
		string section = "A";
		vector<Slot> studentTimetable;
		///vector<Course> registeredCourses;
		//PersonalTimetable personalTimetable;
		//vector<Complaint> complaints;
	public:
		// Constructor
		Student(string& ID, string& pass, string& nam, string& em, string& gen, string& ph, string& dept, string& regDte, int& sem);
		Student();

		void setSemester(int sem);
		int getSemester();

		void ViewCourses();
		vector<Course> getCourses();
		int getTotalCreditHours();
		pair<string, string> getFacultyByCourse(string ID);
		void ViewCourseDetailsByCourseID(string ID);
		void displayCourseSchedulByID(string ID);
		void addStudentComplain();
		void ComplaintStatus();
		void generateTimetable();
		void displayTimetableByDay(int& day_1);
		void displayTimetable();

		//IN Tabular Form
		void displayTimetableTable();
		void exportTimetableToCSV();
		void exportTabularTimetableToCSV();
};

#endif
