#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<map>
#include<utility> //pair
#include<algorithm>
#include "Design_Lab.h"
#include "Date_h.h"
#include "User.h"
#include "Department.h"
#include "Structures.h"
using namespace std;


int maxLecturesPerDay = 8;
int numberOfDays = 5;
//
//
//// //Variables
vector<Faculty> FacultyRegistrations;
//// vector<Faculty> ApprovedFaculty;
vector<Student> StudentRegistrations;
vector<Department> Time_Table_Incharge;
//// //vector<Slot> ConfirmedSlots;
vector<Slot> MySlots;
vector<FacultyComplaints> FACULTY_COMPLAINTS;
vector<StudentComplaints> STUDENT_COMPLAINTS;
vector<Course> AllCourses;
map<int, UnitTime> UNIT = {
	{1, {"8:30", "9:20"}},
	{2, {"9:20", "10:10"}},
	{3, {"10:10", "11:00"}},
	{4, {"11:00", "11:50"}},
	{5, {"11:50", "12:40"}},
	{6, {"12:40", "1:30"}},
	{7, {"1:30", "2:20"}},
	{8, {"2:20", "3:30"}},
};
map<int, string> DAYS = {
	{1, "Monday"},
	{2, "Tuesday"},
	{3, "Wednesday"},
	{4, "Thursday"},
	{5, "Friday"},
	{6, "Saturday"},
	{7, "Sunday"},
};



// -----------------------------------------------------------
// COLOR SETTINGS (Font + Background)
// -----------------------------------------------------------
const string Colour[9] = {"Black", "Blue", "Green", "Cyan", "Red", "Purple", "Yellow", "White", "Gray"};
int Font = 6;          // Default font color (Yellow)
int Background = 0;    // Default background color (Black)

// -----------------------------------------------------------
// ADMIN LOGIN CREDENTIALS
// -----------------------------------------------------------
struct Admin_Login_Credentials {
    string Admin_UserName;
    int Admin_Password;
};
Admin_Login_Credentials Admin1 = {"Admin123", 456};

// -----------------------------------------------------------
// USER CLASS (Base Class)
// -----------------------------------------------------------
// Handles all common data and functionality for users (faculty/student)



//--------------------
//--------------------
//User Class Functions
//--------------------
//--------------------
User::User(string& userID, string& password, string& name, string& email, string& gender, string& phone, string& department, string userType, string& regDte) : userID(userID), password(password), name(name), email(email), gender(gender), phone(phone), department(department), userType(userType), registrationDate(regDte) { }
User::User() { }

// Display user profile info

void User::displayProfile() const {
			cout<<"Name: "<<name<<endl;
			cout<<"Gender: "<<gender<<endl;
			cout<<"Email: "<<email<<endl;
			cout<<"Phone: "<<phone<<endl;
			cout<<"Department: "<<department<<endl;
			cout<<"User Type: "<<userType
				<<"\nApproval Status: "<< (isApproved ? "Approved\n" : "Pending\n")
            	<<"Registration Date: "<<registrationDate<<endl;
	}


    // Authentication and password management


void User::setPassword(const string& pass) { password = pass; }
void User::setUserID(const string& usrID) { userID = usrID; }
void User::setName(const string& nam) { name = nam; }
void User::setGender(const string& gen) { gender = gen; }
void User::setEmail(const string& em) { email = em; }
void User::setPhone(const string& ph ) { phone = ph; }
void User::setDepartment(const string& dep) { department = dep; }
void User::setUniqueID(const string& UniID) { uniqueID = UniID; }
void User::Approval(const string status) {
	if(status == "YES" || status == "Yes" || status == "yes" || status == "yEs" || status == "YeS" || status == "yES" || status == "YEs" || status == "yeS")
	{
		isApproved = true;
	}
	else{
		isApproved = false;
		}
	}
	
string User::getName() const { return name; }
string User::getGender() const { return gender; }
string User::getEmail() const { return email; }
string User::getPhone() const { return phone; }
string User::getDepartment() const { return department; }
bool User::ApprovalStatus() const { return isApproved; }
string User::getUserType() const { return userType; }
string User::getUniqueID() const { return uniqueID; }
string User::getRegistrationDate() const { return registrationDate; }

bool User::authenticate(const string& inputUserName, const string& inputPassword)
	{
		return (userID == inputUserName && password == inputPassword);
	}

bool User::ChangePassword(string& oldPass, string& newPass)
	{
		if(oldPass == password)
		{
			password = newPass;
			return true;
		}
		else
		{
			return false;
		}
	}
// -----------------------------------------------------------
// FACULTY CLASS (Derived from User)
// -----------------------------------------------------------
// Handles faculty-specific functions like availability, qualifications, courses, and timetable


    //--------------------
//--------------------
//Faculty Class Functions
//--------------------
//--------------------
Faculty::Faculty(string& ID, string& pass, string& nam, string& em, string& gen, string& ph, string& dept, string& regDte, string& desig) : User(ID, pass, nam, em, gen, ph, dept, "Faculty", regDte), designation(desig) { }
Faculty::Faculty()	{ }


// Functions include:
// - Weekly availability management
// - Adding/removing qualifications & specialized courses
// - Assigning courses
// - Slot management (adding/removing class slots)
// - Viewing daily schedule and weekly timetable
// - Managing complaints
// - Displaying timetable for department or student purposes



string Faculty::getDesignation() const { return designation; }
void Faculty::setDesignation(const string& desig) { designation = desig; }

void Faculty::setWeeklyAvailability()
	{
		int choice;
		bool s=0;
		cout<<"Set Your Weekly Availability: "<<endl;
        for(int i=1; i<=numberOfDays; i++)
        {
            cout<<i<<". Set Availabilty Hours For "<<DAYS[i]<<": \n";
        }
		cout<<"0. Exit\nEnter Your Choice: ";
		cin>>choice;
		if(choice >= 1 && choice <=5)
		{
			cout<<"Set Your Availability on "<<DAYS[choice]<<endl;
			cout<<"Enter 0 for Unavailable and 1 for Available"<<endl;
			for(int i=1; i<=maxLecturesPerDay; i++)
			{
				cout<<i<<". From "<<UNIT[i].Start_Time<<" to "<<UNIT[i].End_Time<<" : ";
				cin>>s;
				AVAILABLE[choice-1].push_back({{UNIT[i].Start_Time, UNIT[i].End_Time}, s});
			}
		}
		else{
			return;
		}
	}
vector<Faculty_Available> Faculty::getWeeklyAvailability()
	{
		return AVAILABLE[6];
	}
void Faculty::displayAvailabilityByDay(const int& day)
	{
        if(day > 0 && day <=6)
        {
            cout<<"Availability of "<<getName()<<" on "<<DAYS[day]<<endl;
        }
		else { cout<<"Invalid Day"<<endl; return; }
		for(int i=1; i<=maxLecturesPerDay; i++)
		{
			cout<<i<<". From "<<AVAILABLE[day-1][i].t.Start_Time<<" to "<<AVAILABLE[day-1][i].t.End_Time<<" : "<<(AVAILABLE[day-1][0].isAvailable ? "Available" : "Not Available")<<endl;
		}
	}
void Faculty::setQualifications(string qual)
	{
		qualifications.push_back(qual);
	}
void Faculty::removeQualifications(string qual)
	{
		for(int i=0; i<qualifications.size(); i++)
		{
			if(qualifications[i] == qual)
			{
				qualifications.erase(qualifications.begin() + i);
			}
		}
	}
vector<string> Faculty::getQualifications()
	{
		return qualifications;
	}
void Faculty::displayQualifications()
    {
        cout<<"Qualifications: "<<endl;
        for(int i=0; i<qualifications.size(); i++)
		{
			cout<<i+1<<". "<<qualifications[i]<<endl;
		}
        if(qualifications.empty())
        {
            cout<<"No Qualifications Added"<<endl;
        }
    }

void Faculty::setSpecializedCourses(string C)
	{
		specializedCourses.push_back(C);
	}
void Faculty::removeSpecializedCourses(string C)
	{
		for(int i=0; i<specializedCourses.size(); i++)
		{
			if(specializedCourses[i] == C)
			{
				specializedCourses.erase(specializedCourses.begin() + i);
			}
		}
	}
vector<string> Faculty::getSpecializedCourses()
	{
		return specializedCourses;
	}
void Faculty::addAssignedCourses(Course& COUR) //Department Side
    {
        assignedCourses.push_back(COUR);
    }
bool Faculty::checkAssignedCourse(string Course_name)
	{
		for(int i=0; i<assignedCourses.size(); i++)
		{
			if(assignedCourses[i].courseName == Course_name)
			{
				return true;
			}
		}
		return false;
	}
vector<Course> Faculty::getAssignedCourses()
	{
		return assignedCourses;
	}
void Faculty::displayAssignedCourses()
	{
		if(assignedCourses.empty())
		{
			cout<<"Sr. No \t Course Name \t\t Course Code"<<endl;
			for(int i=0; i<assignedCourses.size(); i++)
			{
				cout<<i+1<<". "<<assignedCourses[i].courseName<<"  "<<assignedCourses[i].courseID<<endl;
			}
		}
		else{
			cout<<"No Course Assigned"<<endl;
		}
	}
int Faculty::getCurrentTeachingHours()
	{
		int total = 0;
		for(int i=0; i<assignedCourses.size(); i++)
		{
			if(assignedCourses[i].CourseType == "Lab")
			{
				total += ((assignedCourses[i].credit_hours)*3);
			}
			if(assignedCourses[i].CourseType == "Theory")
			{
				total += (assignedCourses[i].credit_hours);
			}
		}
		return total;
	}
void Faculty::displayDepartmentTimeTableIncharge()
	{
		if(Time_Table_Incharge.empty())
		{
			cout<<"No Department Incharge"<<endl;
			return;
		}
		for(int i=0; i<Time_Table_Incharge.size(); i++)
		{
			Department d = Time_Table_Incharge[i];			
			if(d.getDepartmentName() == string(department) )
			{
				cout<<"Time Table Incharge: "<<Time_Table_Incharge[i].getTimetableIncharge()<<endl;
			}
		}
	}
string Faculty::getDepartmentTimeTableIncharge()
	{
		for(int i=0; i<Time_Table_Incharge.size(); i++)
		{
			if(Time_Table_Incharge[i].getDepartmentName() == department )
			{
				return Time_Table_Incharge[i].getTimetableIncharge();
			}
		}
		return "Invalid!!!";
	}
void Faculty::AddSlot()
  // 1. Show courses not scheduled yet
    // 2. Select day and time slot based on availability
    // 3. Save slot info in MySlots
    
	{
		int course, dataa_int, dataa_int2;
		string dataa;
		bool check = false;
		Slot s1;
		cout<<"List of Courses Which are Not Scheduled: "<<endl;
		for(int i=0; i<assignedCourses.size(); i++)
		{
			if(assignedCourses[i].assignedFaculty->getUniqueID() == getUniqueID())
			{
				if(!assignedCourses[i].isScheduled)
				{
				cout<<i+1<<". "<<assignedCourses[i].courseName<<endl;
				check = true;
				}
			}
		}
		if(!check)
		{
			cout<<"No Course Schedule Pending"<<endl;
			return;
		}
		cout<<"Select the course to add slot: ";
		cin>>course;
		s1.SUBJECT = assignedCourses[course-1];
		s1.Instructor = this;
		dataa = getDepartment();
		for(int i=0; i<Time_Table_Incharge.size(); i++)
		{
			if(Time_Table_Incharge[i].getDepartmentName() == dataa)
			{
				s1.DEPT = &Time_Table_Incharge[i];
				//break;
			}
		}
		s1.SlotStatus = false;
		cout<<"SELECT DAY FOR CLASS: \n"
			<<"1. Mon, 2. Tue, 3. Wed, 4. Thu, 5. Fri"<<endl;
		cout<<"Select day: ";
		cin>>dataa_int;
		s1.Day = DAYS[dataa_int];
		cout<<"Free Slots on "<<DAYS[dataa_int];
		for(int i=0; i<AVAILABLE[dataa_int-1].size(); i++)
		{
			if(AVAILABLE[dataa_int-1][i].isAvailable == true)
			{
				for(const auto& Pair : UNIT)
				{
					if(Pair.second.Start_Time == AVAILABLE[dataa_int-1][i].t.Start_Time && Pair.second.End_Time == AVAILABLE[dataa_int-1][i].t.End_Time)
					{
						cout<<Pair.first<<" ";
					}
				}
			}
		}
		cout<<"Select Start Slot No: ";
		cin>>dataa_int2;
		s1.SlotNo.first = dataa_int2;
		s1.Times.Start_Time = UNIT[dataa_int2].Start_Time;
		cout<<"Select End Slot Number: ";
		cin>>dataa_int2;
		s1.SlotNo.second = dataa_int2;
		s1.Times.End_Time = UNIT[dataa_int2].End_Time;
		cout<<"Select Semester(1-8): ";
		cin>>dataa_int2;
		s1.semester = dataa_int2;
        MySlots.push_back(s1);
		//s1.section;
	}
void Faculty::removeSlot()
	{
		int option;
		cout<<"Select Slots to Remove: "<<endl;
		for(int i=0; i<MySlots.size(); i++)
		{
			if(MySlots[i].Instructor->getName() == getName())
			{
				if(!MySlots[i].SlotStatus)
				{
					cout<<i<<". "<<MySlots[i].SUBJECT.courseName<<" at"<<MySlots[i].DEPT->getDepartmentName()<<" Department on "<<MySlots[i].Day<<" from "<<MySlots[i].Times.Start_Time<<" to "<<MySlots[i].Times.End_Time<<endl;
				}
			}
		}
		cout<<"Select Your Option: ";
		cin>>option;
		MySlots.erase(MySlots.begin() + option);
	}
void Faculty::pendingSlots()
	{
		int a=1;
		bool pending=false;
		for(int i=0; i<MySlots.size(); i++)
		{
			if(MySlots[i].Instructor->getName() == getName())
			{
				if(!MySlots[i].SlotStatus)
				{
					cout<<a<<". "<<MySlots[i].SUBJECT.courseName<<" at"<<MySlots[i].DEPT->getDepartmentName()<<" Department on "<<MySlots[i].Day<<" from "<<MySlots[i].Times.Start_Time<<" to "<<MySlots[i].Times.End_Time<<endl;
					a++;
					pending = true;
				}
			}
		}
		if(!pending)
		{
			cout<<"No Slots Pending For Approval"<<endl;
		}
	}
void Faculty::ApprovedSlots()
	{
		int a=1;
		bool approved=false;
		for(int i=0; i<MySlots.size(); i++)
		{
			if(MySlots[i].Instructor->getName() == getName())
			{
				if(MySlots[i].SlotStatus)
				{
					cout<<a<<". "<<MySlots[i].SUBJECT.courseName<<" at"<<MySlots[i].DEPT->getDepartmentName()<<" Department on "<<MySlots[i].Day<<" from "<<MySlots[i].Times.Start_Time<<" to "<<MySlots[i].Times.End_Time<<endl;
					a++;
					approved = true;
				}
			}
		}
		if(!approved)
		{
			cout<<"No Approved Slot Available"<<endl;
		}
	}
void Faculty::addComplain()
	{
		FacultyComplaints Comp;
		cout<<"Write Subject of Complaint: ";
		getline(cin, Comp.subject);
		cout<<"Write Complain: ";
		getline(cin, Comp.complain);
		Comp.Faculty_A = this;
		Comp.dept = getDepartment();
		Comp.status = false;
		FACULTY_COMPLAINTS.push_back(Comp);
	}
void Faculty::ComplaintStatus()
	{
		int count =1;
		for(int i=0; i<FACULTY_COMPLAINTS.size(); i++)
		{
			if(FACULTY_COMPLAINTS[i].Faculty_A == this)
			{
				cout<<count<<". "<<FACULTY_COMPLAINTS[i].subject<<"\t STATUS: "<< (FACULTY_COMPLAINTS[i].status ? "Resolved" : "Pending")<<endl;
				count++;
			}
		}
	}
void Faculty::displayDailySchedule(const int& day)
	{
		vector<Slot> dailySlots;
		for(const auto& slot : MySlots)
		{
			if(slot.DEPT->getDepartmentName() == department)
			{
				if(slot.Instructor == this)
				{
					if(slot.Day == DAYS[day] && slot.SlotStatus)
					{
						dailySlots.push_back(slot);
					}
				}
			}
		}
		sort(dailySlots.begin(), dailySlots.end(), [](const Slot& a, const Slot& b){
			return a.SlotNo.first < b.SlotNo.first;
		});

		cout<<"Schedule for "<<DAYS[day]<<": "<<endl;
		if(dailySlots.empty())
		{
			cout<<"No Classes Scheduled."<<endl;
			return;
		}
		int count = 1;
		for(auto& slot : dailySlots)
		{
			cout<<count<<"- "<<"From ("<<slot.Times.Start_Time<<" - "<<slot.Times.End_Time<<")\n"
				<<"\t"<<slot.SUBJECT.courseName<<" ("<<slot.SUBJECT.courseID<<" at "<<slot.DEPT->getDepartmentName()<<" (Semester#"<<slot.SUBJECT.semester<<endl<<endl;
		}
	}
void Faculty::displayTimeTable()
	{
		map<string, vector<Slot>> dayMap;
		for(const auto& slot : MySlots)
		{
			if(slot.DEPT->getDepartmentName() == department)
			{
				if(slot.Instructor == this)
				{
					if(slot.SlotStatus)
					{
						dayMap[slot.Day].push_back(slot);
					}
				}
			}
		}

		vector<string> dayOrder = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
		cout<<"Weekly TimeTable for "<<getName()<<":\n";
		cout<<"========================================\n";
		for(auto& day : dayOrder)
		{
			if(dayMap.find(day) != dayMap.end())
			{
				sort(dayMap[day].begin(), dayMap[day].end(), [](const Slot& a, const Slot& b){
				return a.SlotNo.first < b.SlotNo.first;
			});
				
			cout<<"\n"<<day<<":\n";
				for(auto& slot : dayMap[day])
				{
					cout<<"  "<<slot.Times.Start_Time<<" - "<<slot.Times.End_Time<<" : "<<slot.SUBJECT.courseName<<" ("<<slot.DEPT->getDepartmentName()<<", Semester: "<<slot.semester<<")"<<endl;
				}
			}
		}

		bool empty = true;
		for(auto& PAIR : dayMap)
		{
			if(!PAIR.second.empty()) empty = false;
		}
		if(empty)
		{
			cout<<"No classes scheduled for the week."<<endl;
		}
	}
map<string, vector<Slot>> Faculty::getTimeTable()
	{
		map<string, vector<Slot>> schedule;
		for(const auto& slot : MySlots)
		{
			if(slot.SlotStatus)
			{
				schedule[slot.Day].push_back(slot);
			}
		}
		for(auto& PAIR : schedule)
		{
			sort(PAIR.second.begin(), PAIR.second.end(), [](const Slot& a, const Slot& b){
				return a.SlotNo.first < b.SlotNo.second;
			});
		}
		return schedule;
	}





//--------------------
//--------------------
//Student Class Functions
//--------------------
//--------------------
// Constructor
Student::Student(string& ID, string& pass, string& nam, string& em, string& gen, string& ph, string& dept, string& regDte, int& sem) : User(ID, pass, nam, em, gen, ph, dept, "Student", regDte), semester(sem) {
	}

Student::Student() 	{ }

void Student::setSemester(int sem)	{ semester = sem; }
int Student::getSemester() 	{ return semester; }

void Student::ViewCourses()
	{
		int count = 1;
		bool test = false;
		for(int i=0; i<AllCourses.size(); i++)
		{
			if(AllCourses[i].department == getDepartment())
			{
				if(AllCourses[i].semester == semester)
				{
					cout<<count++<<". "<<AllCourses[i].courseName<<"\t["<<AllCourses[i].courseID<<"]\t("<<AllCourses[i].CourseType<<")"<<endl;
					test = true;
				}
			}
		}
		if(!test)
		{
			cout<<"No course Available"<<endl;
		}

	}
vector<Course> Student::getCourses()
	{
		vector<Course> C1;
		bool test = false;
		for(int i=0; i<AllCourses.size(); i++)
		{
			if(AllCourses[i].department == getDepartment())
			{
				if(AllCourses[i].semester == semester)
				{
					C1.push_back(AllCourses[i]);
					test = true;
				}
			}
		}
		if(!test)
		{
			cout<<"No course Available"<<endl;
		}
		return C1;
	}
int Student::getTotalCreditHours()
	{
		int Credit = 0;
		for(int i=0; i<AllCourses.size(); i++)
		{
			if(AllCourses[i].department == getDepartment())
			{
				if(AllCourses[i].semester == semester)
				{
					Credit += AllCourses[i].credit_hours;
				}
			}
		}
		return Credit;
	}
pair<string, string> Student::getFacultyByCourse(string ID)
	{
		pair<string, string> CourseTeacher;
		for(int i=0; i<AllCourses.size(); i++)
		{
			if(AllCourses[i].department == getDepartment())
			{
				if(AllCourses[i].semester == semester)
				{
					if(AllCourses[i].courseID == ID)
					{
						return {AllCourses[i].assignedFaculty->getName(), AllCourses[i].assignedFaculty->getUniqueID()};
					}
				}
			}
		}
		return {"0", "0"};
	}
void Student::ViewCourseDetailsByCourseID(string ID)
	{
		Course C1;
		bool Exist = 0;
		for(int i=0; i<AllCourses.size(); i++)
		{
			if(AllCourses[i].department == getDepartment())
			{
				if(AllCourses[i].semester == semester)
				{
					if(AllCourses[i].courseID == ID)
					{
						Exist = 1;
						C1 = AllCourses[i];
					}
				}
			}
		}
		if(!Exist)
		{
			cout<<"No Such Course Exist"<<endl;
			return;
		}
		cout<<"Course#"<<ID<<endl;
		cout<<"Course Name: "<<C1.courseName<<"\n"
			<<"Instructor: "<<C1.assignedFaculty->getName()<<"\n"
			<<"Course Type: "<<C1.CourseType<<"\n"
			<<"Credit Hours: "<<C1.credit_hours<<"\n"
			<<"Class Schedule: ";
			if(C1.ClassSchedule->SlotStatus)
				cout<<"On "<<C1.ClassSchedule->Day<<" from "<<C1.ClassSchedule->Times.Start_Time<<" to "<<C1.ClassSchedule->Times.End_Time<<" at "<<C1.ClassSchedule->DEPT->getDepartmentName()<<endl;
			else
				cout<<"Course Not Scheduled Yet"<<endl;
	}
void Student::displayCourseSchedulByID(string ID)
	{
		Course C1;
		bool Exist = 0;
		for(int i=0; i<AllCourses.size(); i++)
		{
			if(AllCourses[i].department == getDepartment())
			{
				if(AllCourses[i].semester == semester)
				{
					if(AllCourses[i].courseID == ID)
					{
						Exist = 1;
						C1 = AllCourses[i];
					}
				}
			}
		}
		if(!Exist)
		{
			cout<<"No Such Course Exist"<<endl;
			return;
		}
		cout<<"Class Schedule: ";
			if(C1.ClassSchedule->SlotStatus)
				cout<<"On "<<C1.ClassSchedule->Day<<" from "<<C1.ClassSchedule->Times.Start_Time<<" to "<<C1.ClassSchedule->Times.End_Time<<" at "<<C1.ClassSchedule->DEPT->getDepartmentName()<<endl;
			else
				cout<<"Course Not Scheduled Yet"<<endl;
	}
void Student::addStudentComplain()
	{
		StudentComplaints Comp;
		cout<<"Write Subject of Complaint: ";
		getline(cin, Comp.subject);
		cout<<"Write Complain: ";
		getline(cin, Comp.complain);
		Comp.Student_A = this;
		Comp.dept = getDepartment();
		Comp.status = false;
		STUDENT_COMPLAINTS.push_back(Comp);
	}
void Student::ComplaintStatus()
	{
		int count =1;
		for(int i=0; i<STUDENT_COMPLAINTS.size(); i++)
		{
			if(STUDENT_COMPLAINTS[i].Student_A == this)
			{
				cout<<count<<". "<<STUDENT_COMPLAINTS[i].subject<<"\t STATUS: "<< (STUDENT_COMPLAINTS[i].status ? "Resolved" : "Pending")<<endl;
				count++;
			}
		}
	}
void Student::generateTimetable()
	{
		studentTimetable.clear();
		for(int i=0; i<MySlots.size(); i++)
		{
			if(MySlots[i].DEPT->getDepartmentName() == department && MySlots[i].SlotStatus)
			{
				if(MySlots[i].semester == semester)
				{
					studentTimetable.push_back(MySlots[i]);
				}
			}
		}
	}
void Student::displayTimetableByDay(int& day_1)
	{
		generateTimetable();

		vector<Slot> dailySlots;
		for(const auto& slot : studentTimetable)
		{
			if(slot.Day == DAYS[day_1] && slot.SlotStatus)
			{
				dailySlots.push_back(slot);
			}
		}
		sort(dailySlots.begin(), dailySlots.end(), [](const Slot& a, const Slot& b){
			return a.SlotNo.first < b.SlotNo.first;
		});
		//Display
		cout<<"\n Daily Timetable for "<<DAYS[day_1]<<" - "<<": \n";
		cout<<"=================================================="<<endl;
		if(dailySlots.empty()) {
			cout<<"No classes scheduled for "<<DAYS[day_1]<<"."<<endl;
			return;
		}
		for(const auto& slot : dailySlots) {
			cout<<slot.Times.Start_Time<<" - "<<slot.Times.End_Time<<" : ";
			cout<<slot.SUBJECT.courseName<<" ("<<slot.SUBJECT.courseID<<")"<<endl;
			cout<<"Instructor: "<<slot.Instructor->getName()<<endl;
			cout<<"Course Type: "<<slot.SUBJECT.CourseType<<"\n\n";
		}
	}
void Student::displayTimetable()
	{
		generateTimetable();
		vector<string> dayOrder = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
		cout<<"\nWeekly TimeTable for "<<getName()<<endl
			<<"Roll No: "<<uniqueID<<" | Semester: "<<semester<<endl
			<<"Department: "<<department<<endl;
		cout<<"====================================================="<<endl;
		bool hasClass = false;
		for(const auto& day : dayOrder)
		{
			vector<Slot> dailySlots;
			for(const auto& slot : studentTimetable)
			{
				if(slot.Day == day && slot.SlotStatus)
				{
					dailySlots.push_back(slot);
				}
			}
			sort(dailySlots.begin(), dailySlots.end(), [](const Slot& a, const Slot& b){
				return a.SlotNo.first < b.SlotNo.first;
			});
				
			if(!dailySlots.empty())
			{
				hasClass = true;
				cout<<endl<<day<<": "<<endl;
				cout<<"---------------"<<endl;

				for(const auto& slot : dailySlots)
				{
					cout<<" "<<slot.Times.Start_Time<<" - "<<slot.Times.End_Time
						<<" : "<<slot.SUBJECT.courseName
						<<" ["<<slot.SUBJECT.CourseType<<"]"
						<<" - "<<slot.Instructor->getName()<<endl;
				}
			}
		}
		if(!hasClass)
		{
			cout<<endl<<"No classes scheduled for the week.\n";
		}
	}

		//IN Tabular Form
void Student::displayTimetableTable()
	{
		generateTimetable();
		vector<string> dayOrder = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
		cout<<"\n======================================================\n";
		cout<<"                  TIMETABLE - SEMESTER "<<semester<<endl;
		cout<<"Name: "<<getName()<<" | Roll No: "<<uniqueID<<endl
			<<"Department: "<<department<<endl;
		cout<<"\n======================================================\n";

			//Header
		cout<<setw(12)<<left<<"Day/Time";
		for(int i=1; i<=maxLecturesPerDay; i++)
		{
			cout<<setw(15)<<UNIT[i].Start_Time + "-" + UNIT[i].End_Time;
		}
		cout<<endl;

			//Table Rows
		for(const auto& day : dayOrder)
		{
			cout<<setw(12)<<left<<day;
			for(int slotNum = 1; slotNum<=maxLecturesPerDay; slotNum++)
			{
				string cellContent = "FREE";
				for(const auto& slot : studentTimetable)
				{
					if(slot.Day == day && slot.SlotStatus && slotNum >= slot.SlotNo.first && slotNum <= slot.SlotNo.second)
					{
						cellContent = slot.SUBJECT.courseName;
						break;
					}
				}
				cout<<setw(15)<<left<<cellContent;
			}
			cout<<endl;
		}
		cout<<"======================================================"<<endl;
	}

// -----------------------------------------------------------
// CHANGE APPLICATION THEME (Font + Background Colors)
// -----------------------------------------------------------
void ChangeTheme() {
    Clear();
    int opt;
    int font_color, background_color;

    cout << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_"
         << "|             Change Theme            |"
         << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << endl << endl;

    cout << "Select Your Desired Color For Font and Background: " << endl;
    cout << "Black = 0\nBlue = 1\nGreen = 2\nCyan = 3\nRed = 4\nPurple = 5\nYellow = 6\nWhite = 7\nGray = 8" << endl;

    cout << "Enter Color Number for Font (Enter 9 for default): ";
    cin >> font_color;

    cout << "Enter Color Number for Background (Enter 9 for default): ";
    cin >> background_color;

    // FONT COLOR
    if(font_color >= 0 && font_color <= 8) {
        Font = font_color;
    }
    else if(font_color == 9) {
        Font = 6;  // Default
        cout << "Updated to Default" << endl;
    }
    else {
        cout << "Invalid Font Color! Using Default." << endl;
    }

    // BACKGROUND COLOR
    if(background_color >= 0 && background_color <= 8) {
        Background = background_color;
    }
    else if(background_color == 9) {
        Background = 0;  // Default
        cout << "Updated to Default" << endl;
    }
    else {
        cout << "Invalid Background Color! Using Default." << endl;
    }

    cout << Colour[font_color] << " is Updated as your Font Color" << endl;
    cout << Colour[background_color] << " is Updated as your Background Color" << endl;

    cout << "Enter 1 to Go to HomePage and 0 to exit" << endl;
    cin >> opt;

    if(opt == 1)
        HomePage();
    else
        return;
}

// -----------------------------------------------------------
// ADMIN MENU SCREEN
// -----------------------------------------------------------
void Admin_HomePage() {
    Clear();
    SetColor(Font, Background);

    int option;

    cout << "\t\t\t ------------------------------------------------------\n"
         << "\t\t\t|                                                      |\n"
         << "\t\t\t|                    Admin HomePage                    |\n"
         << "\t\t\t|                                                      |\n"
         << "\t\t\t ------------------------------------------------------\n" << endl;

    cout << "1. Login\n"
         << "2. Go Back to Home Page\n"
         << "3. Exit\n"
         << "Select your option: ";

    cin >> option;

    if(option == 1) {
        Admin_Login();
    }
    else if(option == 2) {
        HomePage();
    }
    else if(option == 3) {
        return;
    }
    else {
        cout << "Invalid Command!" << endl;
        Admin_HomePage();
    }
}

