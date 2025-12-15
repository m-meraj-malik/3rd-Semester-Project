#ifndef FACULTY_H
#define FACULTY_H

#include "User.h"
#include "Structures.h"
#include<vector>
#include<string>
#include<iomanip>
#include<map>
#include<algorithm>
using namespace std;

class Department;
class Student;

class Faculty : public User{
	private:
		string designation;
		vector<string> qualifications;
		vector<string> specializedCourses;
		vector<Faculty_Available> AVAILABLE[6];
		vector<Course> assignedCourses;
		//vector<Slot> MySlots;

	public:
		Faculty(string& ID, string& pass, string& nam, string& em, string& gen, string& ph, string& dept, string& regDte, string& desig);
		Faculty();

		string getDesignation() const;
		void setDesignation(const string& desig);

		void setWeeklyAvailability();
		vector<Faculty_Available> getWeeklyAvailability();
		void displayAvailabilityByDay(const int& day);
		void setQualifications(string qual);
		void removeQualifications(string qual);
		vector<string> getQualifications();
        void displayQualifications();
		void setSpecializedCourses(string C);
		void removeSpecializedCourses(string C);
		vector<string> getSpecializedCourses();
        void addAssignedCourses(Course& COUR); //Department Side
		bool checkAssignedCourse(string Course_name);
		vector<Course> getAssignedCourses();
		void displayAssignedCourses();
		int getCurrentTeachingHours();
		void displayDepartmentTimeTableIncharge();
		string getDepartmentTimeTableIncharge();
		void AddSlot();
		void removeSlot();
		void pendingSlots();
		void ApprovedSlots();
		void addComplain();
		void ComplaintStatus();
		void displayDailySchedule(const int& day);
		void displayTimeTable();
		map<string, vector<Slot>> getTimeTable();
 	//Timetable generateDepartmentTimetable(string semester);
};

#endif
