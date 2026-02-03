#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "Structures.h"
#include<vector>
#include<string>
#include<iomanip>
#include<map>
#include<algorithm>
using namespace std;

class Faculty;
class Student;


class Department {
 private:
    string departmentID;
    string password;
    string departmentName;
    string headOfDepartment;
	string TimeTableIncharge;
    vector<Faculty> facultyMembers;
    vector<Student> enrolledStudents;
    vector<string> programs;
 public:
    // Constructor
    Department(string& id, string& pass, string& name, string& hod, string& incharge);
    Department();
    ~Department() { };
    
    
	// Basic Getters
    string getDepartmentID();
    string getDepartmentName();
    string getHeadOfDepartment();
	string getTimetableIncharge();

	//Basic Setters
	void setDepartmentID(string id);
    void setDepartmentName(string nam);
    void setHeadOfDepartment(string hod);
	void setTimetableIncharge(string incharge);
    void setDepartmentPassword(string& password);

	//Login
	bool DepartmentLogin(string name, string pass);

    bool changePassword(string& oldpass, string& newpass);

	void ApproveFaculty();			
    void FacultyStatistics();

	// Departmental Data
	void ViewDepartmentProfile();
	void displayFacultyMembers();
	void displayCourses();
	void displayEnrolledStudents();
	
	void addFaculty(Faculty faculty);

	void removeFaculty(string facultyID);
	Faculty* getFacultyByID(string& facultyID);
	Faculty getFacultyByName(string& Name);

	void addCourse(Course course);
	void removeCourse(string ID);
	vector<Course> getCourseBySemester(int n);

	vector<Course> getCourseByFaculty(Faculty FACULTY);

    void StudentsStatistics();
	void ApproveStudent();
	void displayEnrolledStudentsBySemester(const int& sem);

        // Display Department's Complete Timetable
    void displayDepartmentTimetable();

    // Display Timetable for Specific Semester
    void displaySemesterTimetable(int semester);
          

    // Display Faculty-wise Timetable
    void displayFacultyTimetable(string facultyName);

    // Print Complete Department Schedule
    void printDepartmentSchedule();
    
	// Program Management
    void exportDepartmentTimetableToCSV();
    void exportSemesterTimetableToCSV(int semester);
    void exportFacultyTimetableToCSV(const string& facultyName);
 };
 
#endif
