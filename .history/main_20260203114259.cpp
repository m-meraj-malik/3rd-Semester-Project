#include<iostream>           // Standard Input/Output stream library
#include<iomanip>            // Input/Output manipulation for formatting
#include<string>             // String class and operations
#include<vector>             // Dynamic array container
#include<map>                // Associative container (key-value pairs)
#include<utility>            // Pair and tuple utilities
#include<algorithm>          // Algorithms like sort, find, etc.
#include "Design_Lab.h"      // Custom UI/design functions header
#include "Date_h.h"          // Date handling utilities header
#include "Faculty.h"         // Faculty class definition
#include "Student.h"         // Student class definition
#include "User.h"            // Base User class definition
#include "Department.h"      // Department class definition
#include "Structures.h"      // Data structures (Slot, Course, etc.)
#include <fstream>           // File stream operations
#include <sstream>           // String stream operations
using namespace std;         // Standard namespace directive


int maxLecturesPerDay = 8;   // Maximum number of lectures allowed per day
int numberOfDays = 5;    // Number of working days (Monday to Friday)


//// //Variables
DateTimeUtils DateTime;      // Date and time utility object instance
vector<Faculty> FacultyRegistrations;
//// vector<Faculty> ApprovedFaculty;
vector<Student> StudentRegistrations;
vector<Department> Time_Table_Incharge;
//vector<Slot> ConfirmedSlots;
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
    string Admin_Password;
};
Admin_Login_Credentials Admin1 = {"Admin123", "456"};




//--------------------
//--------------------
//User Class Functions
//--------------------
//--------------------
User::User(string& userID, string& password, string& name, string& email, string& gender, string& phone, string& department, string userType, string& regDte) : userID(userID), password(password), name(name), email(email), gender(gender), phone(phone), department(department), userType(userType), registrationDate(regDte) { }
User::User() { }

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
	
void User::setPassword(const string& pass) { password = pass; }
void User::setUserID(const string& usrID) { userID = usrID; }
void User::setName(const string& nam) { name = nam; }
void User::setGender(const string& gen) { gender = gen; }
void User::setEmail(const string& em) { email = em; }
void User::setPhone(const string& ph ) { phone = ph; }
void User::setDepartment(const string& dep) { department = dep; }
void User::setUniqueID(const string& UniID) { uniqueID = UniID; }
void User::setRegistrationDate(const string& regDte) { registrationDate = regDte; }
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
string User::getUsrId() const { return userID; }
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
	
	
	
	

//--------------------
//--------------------
//Faculty Class Functions
//--------------------
//--------------------
Faculty::Faculty(string& ID, string& pass, string& nam, string& em, string& gen, string& ph, string& dept, string& regDte, string& desig) : User(ID, pass, nam, em, gen, ph, dept, "Faculty", regDte), designation(desig) { }
Faculty::Faculty()	{ }

string Faculty::getDesignation() const { return designation; }
void Faculty::setDesignation(const string& desig) { designation = desig; }

void Faculty::setWeeklyAvailability()
	{
		int choice;
		cout<<"Set Your Weekly Availability: "<<endl;
        for(int i=1; i<=numberOfDays; i++)
        {
            cout<<i<<". Set Availabilty Hours For "<<DAYS[i]<<": \n";
        }
		cout<<"0. Exit\nEnter Your Choice: ";
        while(!(cin>>choice) || (choice<0 || choice > numberOfDays)) {
            cin.clear();
            cin.ignore();
            cout<< "Invalid Choice! Enter a Number between 0 and "<<numberOfDays<<": ";
        }
		if(choice != 0)
		{
			cout<<"Set Your Availability on "<<DAYS[choice]<<endl;
			cout<<"Enter 0 for Unavailable and 1 for Available"<<endl;
            //Initialize AVAILABLE for this day if needed
            if(AVAILABLE->size() < choice) {
                AVAILABLE->resize(choice);
            }
            AVAILABLE[choice-1].clear(); //Clear Previous Entries

			for(int i=1; i<=maxLecturesPerDay; i++)
			{
                bool s;
				cout<<i<<". From "<<UNIT[i].Start_Time<<" to "<<UNIT[i].End_Time<<" : ";
				while(!(cin>>choice) || (choice<0 || choice > numberOfDays)) {
                    cin.clear();
                    cin.ignore();
                    cout<< "Invalid Input! Enter 0 or 1."<<endl;
                }
				AVAILABLE[choice-1].push_back({{UNIT[i].Start_Time, UNIT[i].End_Time}, s});
			}
		}
		else{
			return;
		}
	}
vector<Faculty_Available> Faculty::getWeeklyAvailability()
	{
		vector<Faculty_Available> weekly;
        for(const auto& dAY : AVAILABLE) {
            weekly.insert(weekly.end(), dAY.begin(), dAY.end());
        }
        return weekly;
	}
void Faculty::displayAvailabilityByDay(const int& day)
	{
        if(day > 0 && day <=numberOfDays)
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
        COUR.assignedFaculty = this;
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
		if(!assignedCourses.empty())
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
        bool deptFound = false;
		for(int i=0; i<Time_Table_Incharge.size(); i++)
		{
			if(Time_Table_Incharge[i].getDepartmentName() == dataa)
			{
				s1.DEPT = &Time_Table_Incharge[i];
                deptFound = true;
				break;
			}
		}
        if(!deptFound) {
            cout<<"Error: Department Not Found"<<endl;
            return;
        }
		s1.SlotStatus = false;
		cout<<"SELECT DAY FOR CLASS: \n";
        for(int i=1; i<=numberOfDays; i++)
        {
            cout<<i<<". "<<DAYS[i]<<endl;
        }
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
		s1.semester = assignedCourses[course-1].semester;
        MySlots.push_back(s1);
		//s1.section;
	}
void Faculty::removeSlot()
	{
        vector<int> mySlotIndices;
        for(int i=0; i<MySlots.size(); i++)
		{
			if(MySlots[i].Instructor && MySlots[i].Instructor->getName() == getName())
			{
				if(!MySlots[i].SlotStatus)
				{
					cout<<mySlotIndices.size()<<". "<<MySlots[i].SUBJECT.courseName<<" at"<<MySlots[i].DEPT->getDepartmentName()<<" Department on "<<MySlots[i].Day<<" from "<<MySlots[i].Times.Start_Time<<" to "<<MySlots[i].Times.End_Time<<endl;
                    mySlotIndices.push_back(i);
				}
			}
		}
        if(mySlotIndices.empty()) {
            cout<<"No Slots to remove"<<endl;
            return;
        }

		int option;
		cout<<"Select Slot Number to Remove: "<<endl;
		cin>>option;
        if(option >= 0 && option < mySlotIndices.size()) {
            int actualIndex = mySlotIndices[option];
            MySlots.erase(MySlots.begin() + actualIndex);
            cout<<"Slot Removed Successfully!"<<endl;
        }
        else {
            cout<<"Invalid Option"<<endl;
        }
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
    void Faculty::exportTimetableToCSV() {
        string filename = "Faculty_" + name + "_Timetable.csv";
        ofstream file(filename);
        
        if (!file.is_open()) {
            cout << "Error creating CSV file!" << endl;
            return;
        }
        
        // Write CSV header
        file << "Day,Start Time,End Time,Course Name,Course ID,Course Type,Semester,Department,Instructor,Status\n";
        
        // Get timetable
        auto timetable = getTimeTable();
        
        for (const auto& dayPair : timetable) {
            for (const auto& slot : dayPair.second) {
                file << slot.toCSV() << "\n";
            }
        }
        
        file.close();
        cout << "✓ Timetable exported to " << filename << endl;
        cout << "File saved in the program's directory." << endl;
    }
    
    void Faculty::exportDailyScheduleToCSV(int day) {
        string filename = "Faculty_" + name + "_" + DAYS[day] + "_Schedule.csv";
        ofstream file(filename);
        
        if (!file.is_open()) {
            cout << "Error creating CSV file!" << endl;
            return;
        }
        
        file << "Start Time,End Time,Course Name,Course ID,Department,Semester\n";
        
        vector<Slot> dailySlots;
        // ... (copy code from displayDailySchedule to collect slots for the day)
        
        for (const auto& slot : dailySlots) {
            file << slot.Times.Start_Time << ","
                 << slot.Times.End_Time << ","
                 << slot.SUBJECT.courseName << ","
                 << slot.SUBJECT.courseID << ","
                 << slot.DEPT->getDepartmentName() << ","
                 << slot.semester << "\n";
        }
        
        file.close();
        cout << "✓ Daily schedule exported to " << filename << endl;
    }





//--------------------
//--------------------
//Student Class Functions
//--------------------
//--------------------
// Constructor
Student::Student(string& ID, string& pass, string& nam, string& em, string& gen, string& ph, string& dept, string& regDte, int& sem) : User(ID, pass, nam, em, gen, ph, dept, "Student", regDte), semester(sem) {
	}

Student::Student() 	{ userType = "Student"; }

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
            if(C1.ClassSchedule && C1.ClassSchedule->SlotStatus)
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
    void Student::exportTimetableToCSV() {
        string filename = "Student_" + name + "_Sem" + to_string(semester) + "_Timetable.csv";
        ofstream file(filename);
        
        if (!file.is_open()) {
            cout << "Error creating CSV file!" << endl;
            return;
        }
        
        file << "Day,Start Time,End Time,Course Name,Course ID,Instructor,Course Type\n";
        
        generateTimetable();
        
        for (const auto& slot : studentTimetable) {
            if (slot.SlotStatus) {
                file << slot.Day << ","
                     << slot.Times.Start_Time << ","
                     << slot.Times.End_Time << ","
                     << slot.SUBJECT.courseName << ","
                     << slot.SUBJECT.courseID << ","
                     << slot.Instructor->getName() << ","
                     << slot.SUBJECT.CourseType << "\n";
            }
        }
        
        file.close();
        cout << "✓ Timetable exported to " << filename << endl;
    }
    
    void Student::exportTabularTimetableToCSV() {
        string filename = "Student_" + name + "_Tabular_Timetable.csv";
        ofstream file(filename);
        
        if (!file.is_open()) {
            cout << "Error creating CSV file!" << endl;
            return;
        }
        
        generateTimetable();
        vector<string> dayOrder = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
        
        // Write header
        file << "Day/Time";
        for (int i = 1; i <= maxLecturesPerDay; i++) {
            file << "," << UNIT[i].Start_Time + "-" + UNIT[i].End_Time;
        }
        file << "\n";
        
        // Write data
        for (const auto& day : dayOrder) {
            file << day;
            for (int slotNum = 1; slotNum <= maxLecturesPerDay; slotNum++) {
                string cellContent = "FREE";
                for (const auto& slot : studentTimetable) {
                    if (slot.Day == day && slot.SlotStatus && 
                        slotNum >= slot.SlotNo.first && slotNum <= slot.SlotNo.second) {
                        cellContent = slot.SUBJECT.courseName;
                        break;
                    }
                }
                file << "," << cellContent;
            }
            file << "\n";
        }
        
        file.close();
        cout << "✓ Tabular timetable exported to " << filename << endl;
    }
	
	
	
	
	
//--------------------
//--------------------
//Department Class Functions
//--------------------
//--------------------
// Constructor
Department::Department(string& id, string& pass, string& name, string& hod, string& incharge) : departmentID(id), password(pass), departmentName(name), headOfDepartment(hod), TimeTableIncharge(incharge) { }
Department::Department() { }
// Basic Getters
string Department::getDepartmentID() { return departmentID; }
string Department::getDepartmentName() { return departmentName; }
string Department::getHeadOfDepartment() { return headOfDepartment; }
string Department::getTimetableIncharge() { return TimeTableIncharge; }

//Basic Setters
void Department::setDepartmentID(string id) { departmentID = id; }
void Department::setDepartmentName(string nam) { departmentName = nam; }
void Department::setHeadOfDepartment(string hod) { headOfDepartment = hod; }
void Department::setTimetableIncharge(string incharge) { TimeTableIncharge = incharge; }
void Department::setDepartmentPassword(string& password) { this->password = password; }
//Login
bool Department::DepartmentLogin(string name, string pass)
{
	if(departmentID == name && password == pass)
	{
		return true;
	}
	return false;
}

bool Department::changePassword(string& oldpass, string& newpass)
{
    if(oldpass == password)
    {
        password = newpass;
        return 1;
    }
    return 0;
}

void Department::ApproveFaculty()
{
	bool approve = 0;
	for(int i=0, count=1; i<FacultyRegistrations.size(); i++)
	{
		if(FacultyRegistrations[i].getDepartment() == departmentName)
		{
			if(!FacultyRegistrations[i].ApprovalStatus())
			{
				cout<<"Faculty: "<<count<<endl;
				cout<<"Name: "<<FacultyRegistrations[i].getName()<<endl;
				cout<<"Email: "<<FacultyRegistrations[i].getEmail()<<endl;
				cout<<"Unique ID: "<<FacultyRegistrations[i].getUniqueID()<<endl;
				cout<<"Gender: "<<FacultyRegistrations[i].getGender()<<endl;
				cout<<"Phone: "<<FacultyRegistrations[i].getPhone()<<endl;
				cout<<"Registration Date: "<<FacultyRegistrations[i].getRegistrationDate()<<endl;
				cout<<"Enter 1 to Approve and 0 to Reject: ";
				cin>>approve;
				if(approve == 1)
				{
					cout<<"Approved "<<FacultyRegistrations[i].getName()<<" as Faculty Member"<<endl;
					FacultyRegistrations[i].Approval("Yes");
					facultyMembers.push_back(FacultyRegistrations[i]);
				}
			}
		}
	}
}
void Department::FacultyStatistics()
{
    int reg=0, app=0;
    for(int i=0; i<FacultyRegistrations.size(); i++)
    {
        if(FacultyRegistrations[i].getDepartment() == departmentName)
        {
            reg += 1;
            if(FacultyRegistrations[i].ApprovalStatus()) //isApproved
            {
                app += 1;
            }
        }
    }
    cout<<"Total Number of Registrations: "<<reg<<endl;
    cout<<"Total Approved Faculty Registrations: "<<app<<endl;
    cout<<"Pending Faculty Approvals: "<<reg-app<<endl;
}

// Departmental Data
void Department::ViewDepartmentProfile()
{
    int count = 0;
	cout<<"Name of Department: "<<departmentName<<endl;
	cout<<"Head of Department: "<<headOfDepartment<<endl;
	cout<<"Total Number of Students: "<<enrolledStudents.size()<<endl;
	cout<<"Total Number of Faculty Members: "<<facultyMembers.size()<<endl;
	cout<<"Number of Offered Courses: ";
	for(int i=0; i<AllCourses.size(); i++)
    {
        if(AllCourses[i].department == departmentName)
        {
            count += 1;
        }
    }
    cout<<count<<endl;
	cout<<"Degree Programs: ";
	for(string& P : programs)
	{
		cout<<P<<" ";
	} cout<<endl;
}
void Department::displayFacultyMembers()
{
	cout<<"Faculty Members of "<<departmentName<<" Department"<<endl;
	for(int i=0; i<facultyMembers.size(); i++)
	{
		cout<<i+1<<". "<<facultyMembers[i].getName()<<endl;
	}
}
void Department::displayCourses()
{
	cout<<"Courses Per Semester: "<<endl;
	for(int i=1; i<=8; i++)
	{
		cout<<"Courses of Semester#"<<i<<endl;
		for(int j=0; j<AllCourses.size(); j++)
		{
            if(AllCourses[j].department == departmentName)
            {
                if(AllCourses[j].semester == i)
				{
					cout<<j+1<<". "<<AllCourses[j].courseName<<endl;
				}
            }
			cout<<endl;
		}
	}
}
void Department::displayEnrolledStudents()
{
	for(int i=0, count = 1; i<enrolledStudents.size(); i++)
	{
		if(enrolledStudents[i].ApprovalStatus())
		{
			cout<<count<<". "<<enrolledStudents[i].getName()<<endl;
			count++;
		}
	}
}
	
void Department::addFaculty(Faculty faculty)
{
	facultyMembers.push_back(faculty);
}

void Department::removeFaculty(string facultyID)
{
	for(int i=0; i<facultyMembers.size(); i++)
	{
		if(facultyMembers[i].getUniqueID() == facultyID)
		{
			auto it = facultyMembers.begin();
			facultyMembers.erase(it+i);
		}
	}
}
Faculty* Department::getFacultyByID(string& facultyID)
{
	for(auto& faculty : facultyMembers)
	{
		if(faculty.getUniqueID() == facultyID)
		{
			return &faculty;
		}
	}
	cout<<"Invalid Faculty ID."<<endl;
	return nullptr;
}
Faculty Department::getFacultyByName(string& Name)
{
	for(int i=0; i<facultyMembers.size(); i++)
	{
		if(facultyMembers[i].getName() == Name)
		{
			return facultyMembers[i];
		}
	}
	cout<<"Invalid Faculty Name."<<endl;
	return facultyMembers[0];
}

void Department::addCourse(Course course)
{
	AllCourses.push_back(course);
}
void Department::removeCourse(string ID)
{
	for(int i=0; i<AllCourses.size(); i++)
	{
        if(AllCourses[i].department == departmentName)
        {
            if(AllCourses[i].courseID == ID)
			{
				auto it = AllCourses.begin();
				AllCourses.erase(it+i);
			}
        }
	}
}
vector<Course> Department::getCourseBySemester(int n)
{
	vector<Course> newVec;
	for(int i=0; i<AllCourses.size(); i++)
	{
        if(AllCourses[i].department == departmentName)
        {
            if(AllCourses[i].semester == n)
			{
				newVec.push_back(AllCourses[i]);
			}
        }
	}
	return newVec;
}

vector<Course> Department::getCourseByFaculty(Faculty FACULTY)
{
	vector<Course> newVec;
	for(int i=0; i<AllCourses.size(); i++)
	{
        if(AllCourses[i].department == departmentName)
        {
            if(AllCourses[i].assignedFaculty->getUniqueID() == FACULTY.getUniqueID())
			{
				newVec.push_back(AllCourses[i]);
			}
        }
	}
	return newVec;
}

void Department::StudentsStatistics()
{
    int reg=0, app=0;
    for(int i=0; i<StudentRegistrations.size(); i++)
    {
        if(StudentRegistrations[i].getDepartment() == departmentName)
        {
            reg += 1;
            if(StudentRegistrations[i].ApprovalStatus()) //isApproved
            {
                app += 1;
            }
        }
    }
    cout<<"Total Number of Registrations: "<<reg<<endl;
    cout<<"Total Approved Student Registrations: "<<app<<endl;
    cout<<"Pending Student Approvals: "<<reg-app<<endl;
}
void Department::ApproveStudent()
{
	bool approve = 0;
	for(int i=0, count=1; i<StudentRegistrations.size(); i++)
	{
		if(StudentRegistrations[i].getDepartment() == departmentName)
		{
			if(!StudentRegistrations[i].ApprovalStatus())
			{
				cout<<"Student: "<<count<<endl;
				cout<<"Name: "<<StudentRegistrations[i].getName()<<endl;
				cout<<"Email: "<<StudentRegistrations[i].getEmail()<<endl;
				cout<<"Unique ID: "<<StudentRegistrations[i].getUniqueID()<<endl;
				cout<<"Gender: "<<StudentRegistrations[i].getGender()<<endl;
				cout<<"Phone: "<<StudentRegistrations[i].getPhone()<<endl;
				cout<<"Registration Date: "<<StudentRegistrations[i].getRegistrationDate()<<endl;
				cout<<"Enter 1 to Approve and 0 to Reject: ";
				cin>>approve;
				if(approve == 1)
				{
					cout<<"Approved "<<StudentRegistrations[i].getName()<<" as Student"<<endl;
					StudentRegistrations[i].Approval("Yes");
					enrolledStudents.push_back(StudentRegistrations[i]);
				}
			}
		}
	}
}
void Department::displayEnrolledStudentsBySemester(const int& sem)
{
	int count = 1;
	bool check = false;
	for(int i=0, count = 1; i<enrolledStudents.size(); i++)
	{
		if(enrolledStudents[i].ApprovalStatus() && enrolledStudents[i].getSemester() == sem)
		{
			cout<<count<<". "<<enrolledStudents[i].getName()<<"\t("<<enrolledStudents[i].getUniqueID()<<")"<<endl;
			count++;
			check = true;
		}
	}
	if(!check){
		cout<<"No Students Available"<<endl;
	}
}

        // Display Department's Complete Timetable
void Department::displayDepartmentTimetable() {
    cout << "\n====================================================================\n";
    cout << "           DEPARTMENT TIMETABLE - " << departmentName << "\n";
    cout << "====================================================================\n";

        // Display by semester
    for (int sem = 1; sem <= 8; sem++) {
        displaySemesterTimetable(sem);
    }
}

     // Display Timetable for Specific Semester
    void Department::displaySemesterTimetable(int semester) {
        vector<Slot> semesterSlots;
        
        // Collect all slots for this semester from all courses
        for (const auto& course : AllCourses) {
            if (course.department == departmentName && course.semester == semester && course.isScheduled && course.ClassSchedule->SlotStatus) {
                semesterSlots.push_back(*course.ClassSchedule);
            }
        }

        if (semesterSlots.empty()) {
            return;  // No classes for this semester
        }

        cout << "\nSEMESTER " << semester << " TIMETABLE:\n";
        cout << "==============================================\n";

        // No need to group by section since only 1 section per semester
        // Group by day and sort
        map<string, vector<Slot>> daySlots;
        for (const auto& slot : semesterSlots) {
            daySlots[slot.Day].push_back(slot);
        }

        vector<string> dayOrder = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
        
        for (const auto& day : dayOrder) {
            if (daySlots.find(day) != daySlots.end()) {
                // Sort by time
                sort(daySlots[day].begin(), daySlots[day].end(),
                     [](const Slot& a, const Slot& b) {
                         return a.SlotNo.first < b.SlotNo.first;
                     });

                cout << "\n" << day << ":\n";
                cout << string(40, '-') << "\n";
                
                for (const auto& slot : daySlots[day]) {
                    cout << "  " << slot.Times.Start_Time << " - " << slot.Times.End_Time;
                    cout << " : " << slot.SUBJECT.courseName;
                    cout << " (" << slot.SUBJECT.courseID << ")";
                    cout << "\n     Instructor: " << slot.Instructor->getName();
                    cout << " | Type: " << slot.SUBJECT.CourseType;
                    cout << " | Credits: " << slot.SUBJECT.credit_hours << "\n";
                }
            }
        }
        cout << "\n";
    }

 // Display Faculty-wise Timetable
    void Department::displayFacultyTimetable(string facultyName) {
        cout << "\nTIMETABLE FOR FACULTY: " << facultyName << "\n";
        cout << "==============================================\n";

        // Find the faculty
        Faculty* targetFaculty = nullptr;
        for (auto& faculty : facultyMembers) {
            if (faculty.getName() == facultyName) {
                targetFaculty = &faculty;
                break;
            }
        }

        if (!targetFaculty) {
            cout << "Faculty not found in department.\n";
            return;
        }

        // Collect all slots taught by this faculty
        vector<Slot> facultySlots;
        for (const auto& course : AllCourses) {
            if (course.department == departmentName && course.isScheduled && course.ClassSchedule->SlotStatus && course.assignedFaculty->getUniqueID() == targetFaculty->getUniqueID()) {
                facultySlots.push_back(*course.ClassSchedule);
            }
        }

        if (facultySlots.empty()) {
            cout << "No classes assigned to this faculty.\n";
            return;
        }

        // Group by day and sort
        map<string, vector<Slot>> daySlots;
        for (const auto& slot : facultySlots) {
            daySlots[slot.Day].push_back(slot);
        }

        vector<string> dayOrder = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
        
        for (const auto& day : dayOrder) {
            if (daySlots.find(day) != daySlots.end()) {
                // Sort by time
                sort(daySlots[day].begin(), daySlots[day].end(),
                     [](const Slot& a, const Slot& b) {
                         return a.SlotNo.first < b.SlotNo.first;
                     });

                cout << "\n" << day << ":\n";
                cout << string(40, '-') << "\n";
                
                for (const auto& slot : daySlots[day]) {
                    cout << "  " << slot.Times.Start_Time << " - " << slot.Times.End_Time;
                    cout << " : " << slot.SUBJECT.courseName;
                    cout << " | Sem " << slot.semester;
                    cout << " | Type: " << slot.SUBJECT.CourseType << "\n";
                }
            }
        }
    }



    // Print Complete Department Schedule (Alternative format)
    void Department::printDepartmentSchedule() {
        cout << "\n==============================================\n";
        cout << "COMPLETE DEPARTMENT SCHEDULE - " << departmentName << "\n";
        cout << "==============================================\n";

        vector<string> dayOrder = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
        
        for (const auto& day : dayOrder) {
            cout << "\n" << day << ":\n";
            cout << string(80, '-') << "\n";

            // Collect all slots for this day
            vector<Slot> daySlots;
            for (const auto& course : AllCourses) {
                if (course.department == departmentName && course.isScheduled && course.ClassSchedule->Day == day && course.ClassSchedule->SlotStatus) {
                    daySlots.push_back(*course.ClassSchedule);
                }
            }

            // Sort by time and semester
            sort(daySlots.begin(), daySlots.end(), [](const Slot& a, const Slot& b) {
                if (a.SlotNo.first != b.SlotNo.first)
                    return a.SlotNo.first < b.SlotNo.first;
                return a.semester < b.semester;
            });

            if (daySlots.empty()) {
                cout << "No classes scheduled.\n";
                continue;
            }

            // Display in tabular format
            cout << setw(15) << left << "Time";
            cout << setw(30) << left << "Course";
            cout << setw(10) << left << "Semester";
            cout << setw(25) << left << "Instructor";
            cout << setw(10) << left << "Type";
            cout << "\n";
            
            for (const auto& slot : daySlots) {
                cout << setw(15) << left << (slot.Times.Start_Time + "-" + slot.Times.End_Time);
                cout << setw(30) << left << (slot.SUBJECT.courseName + " (" + slot.SUBJECT.courseID + ")");
                cout << setw(10) << left << ("Sem " + to_string(slot.semester));
                cout << setw(25) << left << slot.Instructor->getName();
                cout << setw(10) << left << slot.SUBJECT.CourseType;
                cout << "\n";
            }
        }
    }
    void Department::exportDepartmentTimetableToCSV() {
        string filename = "Department_" + departmentName + "_Timetable.csv";
        ofstream file(filename);
        
        if (!file.is_open()) {
            cout << "Error creating CSV file!" << endl;
            return;
        }
        
        file << "Day,Start Time,End Time,Course Name,Course ID,Semester,Instructor,Type,Credit Hours\n";
        
        for (int sem = 1; sem <= 8; sem++) {
            vector<Slot> semesterSlots;
            // Collect slots for this semester
            for (const auto& course : AllCourses) {
                if (course.department == departmentName && 
                    course.semester == sem && 
                    course.isScheduled && 
                    course.ClassSchedule->SlotStatus) {
                    semesterSlots.push_back(*course.ClassSchedule);
                }
            }
            
            for (const auto& slot : semesterSlots) {
                file << slot.Day << ","
                     << slot.Times.Start_Time << ","
                     << slot.Times.End_Time << ","
                     << slot.SUBJECT.courseName << ","
                     << slot.SUBJECT.courseID << ","
                     << "Sem " << slot.semester << ","
                     << slot.Instructor->getName() << ","
                     << slot.SUBJECT.CourseType << ","
                     << slot.SUBJECT.credit_hours << "\n";
            }
        }
        
        file.close();
        cout << "Department timetable exported to " << filename << endl;
    }
    
    void Department::exportSemesterTimetableToCSV(int semester) {
        string filename = departmentName + "_Sem" + to_string(semester) + "_Timetable.csv";
        ofstream file(filename);
        
        if (!file.is_open()) {
            cout << "Error creating CSV file!" << endl;
            return;
        }
        
        file << "Day,Start Time,End Time,Course Name,Course ID,Instructor,Type,Room\n";
        
        vector<Slot> semesterSlots;
        // Collect slots for this semester
        for (const auto& course : AllCourses) {
            if (course.department == departmentName && 
                course.semester == semester && 
                course.isScheduled && 
                course.ClassSchedule->SlotStatus) {
                semesterSlots.push_back(*course.ClassSchedule);
            }
        }
        
        // Group by day
        map<string, vector<Slot>> daySlots;
        for (const auto& slot : semesterSlots) {
            daySlots[slot.Day].push_back(slot);
        }
        
        for (const auto& dayPair : daySlots) {
            for (const auto& slot : dayPair.second) {
                file << slot.Day << ","
                     << slot.Times.Start_Time << ","
                     << slot.Times.End_Time << ","
                     << slot.SUBJECT.courseName << ","
                     << slot.SUBJECT.courseID << ","
                     << slot.Instructor->getName() << ","
                     << slot.SUBJECT.CourseType << ","
                     << "Room " << slot.semester << "01\n"; // You can modify room logic
            }
        }
        
        file.close();
        cout << "✓ Semester timetable exported to " << filename << endl;
    }
    
    void Department::exportFacultyTimetableToCSV(const string& facultyName) {
        string filename = facultyName + "_Timetable.csv";
        ofstream file(filename);
        
        if (!file.is_open()) {
            cout << "Error creating CSV file!" << endl;
            return;
        }
        
        file << "Day,Start Time,End Time,Course Name,Course ID,Semester,Type\n";
        
        Faculty* targetFaculty = nullptr;
        // Find faculty
        for (auto& faculty : facultyMembers) {
            if (faculty.getName() == facultyName) {
                targetFaculty = &faculty;
                break;
            }
        }
        
        if (!targetFaculty) {
            cout << "Faculty not found!" << endl;
            return;
        }
        
        // Collect faculty slots
        vector<Slot> facultySlots;
        for (const auto& course : AllCourses) {
            if (course.department == departmentName && 
                course.isScheduled &&
                course.ClassSchedule->SlotStatus && 
                course.assignedFaculty->getUniqueID() == targetFaculty->getUniqueID()) {
                facultySlots.push_back(*course.ClassSchedule);
            }
        }
        
        for (const auto& slot : facultySlots) {
            file << slot.Day << ","
                 << slot.Times.Start_Time << ","
                 << slot.Times.End_Time << ","
                 << slot.SUBJECT.courseName << ","
                 << slot.SUBJECT.courseID << ","
                 << "Sem " << slot.semester << ","
                 << slot.SUBJECT.CourseType << "\n";
        }
        
        file.close();
        cout << "Faculty timetable exported to " << filename << endl;
    }
    string Slot::toCSV() const {
        stringstream ss;
        ss << Day << ","
           << Times.Start_Time << ","
           << Times.End_Time << ","
           << SUBJECT.courseName << ","
           << SUBJECT.courseID << ","
           << SUBJECT.CourseType << ","
           << semester << ","
           << DEPT->getDepartmentName() << ","
           << Instructor->getName() << ","
           << (SlotStatus ? "Approved" : "Pending");
        return ss.str();
    }













// -----------------------------------------------------------
// FUNCTION DECLARATIONS
// -----------------------------------------------------------
void initializeData();
void HomePage();
void Admin_HomePage();
void ChangeTheme();
void Admin_Login();
void Admin_After_Login();
void Faculty_HomePage();
void Student_HomePage();
void StudentOptionsPage(int vectorNumber);
void displayStudentRegistrationForm();
void handleStudentLogin();
void Student_HomePage();
void Faculty_Login();
void handleTimetableInchargeLogin();
void Faculty_Registration();
void FacultyOptionsPage(int vectorNumber);
void TimeTableInchargeOptionsPage(int vectorNumber);
void DepartmentLoginOptionsPage(int vectorNumber);
void displayFacultyRegistrationForm();
void handleFacultyLogin();

// -----------------------------------------------------------
// MAIN FUNCTION
// -----------------------------------------------------------
int main() {
    int option;
	void initializeData();
    // Application Title
    cout << "\t\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
         << "\t\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
         << "\t\t\t:::                                                       :::\n"
         << "\t\t\t:::     WELCOME TO TIME TABLE MANAGEMENT APPLICATION      :::\n"
         << "\t\t\t:::                                                       :::\n"
         << "\t\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
         << "\t\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n" << endl;
	
		cout<<"-------------------------"<<endl;
		cout<<"|\tPrepared By: \t|\n"
        <<"-------------------------\n"
		<<"|\t24-MCT-06\t|\n"
		<<"|\t24-MCT-08\t|\n"
		<<"|\t24-MCT-13\t|\n"
		<<"|\t24-MCT-16\t|\n"
		<<"|\t24-MCT-50\t|"<<endl;
		cout<<"-------------------------"<<endl;
    // User choice
    cout << "\n\n -----------------------------------\n"
         << "| Enter 1 to continue and 0 to exit |\n"
         << " -----------------------------------" << endl;

    cin >> option;

    if(option == 1)
        HomePage();
    else
        return 0;
}

// void initializeData()
// {
// 	string UserId, Password, NAme, Email, Gender, Phone, depart, regDate, desig, HOD, Incharge;
// 	int Semester;
// 	UserId = "Mechatronics";
// 	Password = "MCT-24";
// 	NAme = "Mecha";
// 	HOD = "ABC";
// 	Incharge = "DEF";

// 	Department tempDepartment(UserId, Password, NAme, HOD, Incharge);
// 	Time_Table_Incharge.push_back(tempDepartment);

// 	UserId = "ABCD";
// 	Password = "123";
// 	NAme = "ABCD";
// 	Email = "agddgfd@hdh";
// 	Gender = "Male";
// 	Phone = "4654544747";
// 	depart = "Mechatronics";
// 	regDate = "4/11/25";
// 	desig = "Assistant Professor";
// 	Faculty tempFaculty(UserId, Password, NAme, Email, Gender, Phone, depart, regDate, desig);
//     tempFaculty.Approval("Yes");
// 	FacultyRegistrations.push_back(tempFaculty);

// 	UserId = "Ahmed";
// 	Password = "123";
// 	NAme = "Ahmed";
// 	Email = "agddgfd@hdh";
// 	Gender = "Male";
// 	Phone = "4654544747";
// 	depart = "Mechatronics";
// 	regDate = "4/11/25";
// 	Semester = 3;
// 	Student tempStudent(UserId, Password, NAme, Email, Gender, Phone, depart, regDate, Semester);
//     tempStudent.Approval("Yes");
// 	StudentRegistrations.push_back(tempStudent);
// }

// -----------------------------------------------------------
// MAIN HOME PAGE SCREEN
// -----------------------------------------------------------
void HomePage() {
    int option;

    do {
        Clear();
        SetColor(Font, Background);

    cout << "\t\t\t -------------------------------------------------------------- \n"
         << "\t\t\t|                                                              |\n"
         << "\t\t\t|               University Time Table Management               |\n"
         << "\t\t\t|                                                              |\n"
         << "\t\t\t -------------------------------------------------------------- " << endl;

    cout << "1. Admin Mode\n"
         << "2. Faculty Mode\n"
         << "3. Student Mode\n"
         << "4. Settings\n"
         << "5. Exit\n"
         << "Select your option: ";

    if(!(cin >> option))  {
        cin.clear(); //Clear Error Flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');   //Discard Bad Input
        cout<< "Invalid Input! Please Enter a Number."<<endl;
        continue;
    }

    switch(option) {
        case 1: Admin_HomePage(); break;
        case 2: Faculty_HomePage(); break;
        case 3: Student_HomePage(); break;
        case 4: ChangeTheme(); break;
        case 5: return;
        default: 
            cout<<"Invalid Option! Please Try Again."<<endl;
            break;
    }
  } while(true);
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

// -----------------------------------------------------------
// ADMIN LOGIN SCREEN
// -----------------------------------------------------------
void Admin_Login() {
    Clear();
    SetColor(Font, Background);

    string username, password;
    int option;

    cout << "+_+_+_+_+_+_+_ Login _+_+_+_+_+_+_+\n\n" << endl;
    cout << "-> Enter UserName: ";
    cin >> username;

    cout << "-> Enter Password: ";
    cin >> password;

    // Check admin login
    if(username == Admin1.Admin_UserName && password == Admin1.Admin_Password) {
        // Admin Gains Access
        Admin_After_Login();
    }
    else {
        cout << "Incorrect UserName or Password" << endl;

        // Error recovery options
        cout << "1. Try Again\n"
             << "2. Admin Home Page\n"
             << "3. Main Home Page\n"
             << "4. Exit\n";

        cout << "Select your option: ";
        cin >> option;

        if(option == 1)
            Admin_Login();
        else if(option == 2)
            Admin_HomePage();
        else if(option == 3)
            HomePage();
        else if(option == 4)
            return;
        else {
            cout << "Invalid Command!" << endl;
            Admin_Login();
        }
    }
}


void Admin_After_Login(){
	Clear();
    SetColor(Font, Background);
	int option, option3;
	cout << "\t\t\t ------------------------------------------------------\n"
         << "\t\t\t|                                                      |\n"
         << "\t\t\t|                  Welcome Dear Admin!                 |\n"
         << "\t\t\t|                                                      |\n"
         << "\t\t\t ------------------------------------------------------\n" << endl;
	cout<<"1. Add New Department\n"
		<<"2. Remove Existing Department\n"
		<<"3. Schedule Setting\n"
		<<"4. Lecture Schedule\n"
		<<"5. Admin Account Setting\n"
		<<"6. Back\n"
		<<"7. Admin Home Page\n"
		<<"8. Main Home Page\n"
		<<"9. Exit"<<endl;
	cin>>option;
	if(option == 1)
	{
        Clear();
        SetColor(Font, Background);
		Department D1;
		string temp_Var;
		cout << "\n\n========================================" << endl;
        cout << "       New Department Registration" << endl;
        cout << "========================================" << endl;
		cout<<"-> Enter UserName of Department: ";
		cin>>temp_Var;
		D1.setDepartmentID(temp_Var);
		cout<<"-> Enter Password of Department: ";
		cin>>temp_Var;
		D1.setDepartmentPassword(temp_Var);
		cout<<"-> Enter the Name of Department: ";
		cin.ignore();
        getline(cin, temp_Var);
		D1.setDepartmentName(temp_Var);
		cout<<"-> Enter the Name of Head of Department: ";
		cin.ignore();
        getline(cin, temp_Var);
		D1.setHeadOfDepartment(temp_Var);
		cout<<"-> Enter Name of TimeTable Incharge: ";
		cin.ignore();
        getline(cin, temp_Var);
		D1.setTimetableIncharge(temp_Var);
		Time_Table_Incharge.push_back(D1);
		cout<<"\n---[ Department Added Successfully ]---"<<endl;
		cout<<"Press 1 to Back and any other key to Exit"<<endl;
		cin>>option3;
		if(option3 == 1)
			Admin_After_Login();
		else
			return;
	}
	else if(option == 2)
	{
        Clear();
        SetColor(Font, Background);
		int Department_to_Remove;
		cout << "\n\n========================================" << endl;
        cout << "           Remove Department " << endl;
        cout << "========================================" << endl;
		for(int i=0; i<Time_Table_Incharge.size(); i++)
		{
			cout<<i+1<<". "<<Time_Table_Incharge[i].getDepartmentName()<<endl;
		}
		cout<<"Select Department to Remove: "<<endl;
		cin>>Department_to_Remove;
		if(Department_to_Remove > 0 && Department_to_Remove <= Time_Table_Incharge.size())
		{
			Time_Table_Incharge.erase(Time_Table_Incharge.begin() + Department_to_Remove + 1);
			cout<<"Department Removed Successfully!"<<endl;
			cout<<"Press 1 to Back and any other key to Exit"<<endl;
			cin>>option3;
			if(option3 == 1)
				Admin_After_Login();
			else
				return;
		}
		else{
			cout<<"Incorrect Index Selected..."<<endl;
			cout<<"Press 1 to Back and any other key to Exit"<<endl;
			cin>>option3;
			if(option3 == 1)
				Admin_After_Login();
			else
				return;
		}
	}
	else if(option == 3)
	{
        Clear();
        SetColor(Font, Background);
		int Temp;
        cout << "\n\n========================================" << endl;
        cout << "         Modify Daily Schedule " << endl;
        cout << "========================================" << endl;
		cout<<"Set Maximum Lectures Per Day: ";
		cin>>Temp;
		maxLecturesPerDay = Temp;
		cout<<"Set Number of Days: ";
		cin>>Temp;
        if(numberOfDays <= 7)
		    numberOfDays = Temp;
		Admin_After_Login();
	}
	else if(option == 4)
	{
        Clear();
        SetColor(Font, Background);
        cout << "\n\n========================================" << endl;
        cout << "     Set Daily Schedule of Lectures " << endl;
        cout << "========================================" << endl;
		UNIT.clear();
		for(int i=1; i<=maxLecturesPerDay; i++)
		{
			cout<<"For Lecture#"<<i<<endl;
			cout<<"Enter Start Time: ";
			cin>>UNIT[i].Start_Time;
			cout<<"Enter End Time: ";
			cin>>UNIT[i].End_Time;
			cout<<endl;
		}
		Admin_After_Login();
	}
	else if(option == 5)
	{
		Clear();
    	SetColor(4, 0);
		int option1;
        string existingPassword, newPassword;
		string existingUserName, newUserName;
    	cout<<"Account Setting"<<endl;
		cout<<"1. Change UserName\n"
			<<"2. Change Password\n"
			<<"3. Change UserName and Password\n"
            <<"4. Back";
		cout<<"Select your option"<<endl;
		cin>>option1;
		if(option1==1)
		{
			cout<<"Enter Your Existing UserName: ";
			cin>>existingUserName;
			if(existingUserName == Admin1.Admin_UserName)
			{
				cout<<"Enter New UserName: ";
				cin>>newUserName;
				Admin1.Admin_UserName = newUserName;
				cout<<"UserName Changed Successfully"<<endl;
				Admin_After_Login();
			}
			else{
				cout<<"Existing User Name is Incorrect."<<endl;
				Admin_After_Login();
			}
		}
		else if(option1==2)
		{
			cout<<"Enter Your Existing Password: ";
			cin>>existingPassword;
			if(existingPassword == Admin1.Admin_Password)
			{
				cout<<"Enter New Password: ";
				cin>>newPassword;
				Admin1.Admin_Password = newPassword;
				cout<<"Password Changed Successfully"<<endl;
				Admin_After_Login();
			}
			else{
				cout<<"Existing Password is Incorrect."<<endl;
				Admin_After_Login();
			}
		}
		else if(option1==3)
		{
			cout<<"Enter Your Existing UserName: ";
			cin>>existingUserName;
			cout<<"Enter Your Existing Password: ";
			cin>>existingPassword;
			if(existingUserName == Admin1.Admin_UserName && existingPassword == Admin1.Admin_Password)
			{
				cout<<"Enter New UserName: ";
				cin>>newUserName;
				Admin1.Admin_UserName = newUserName;
				cout<<"Enter New Password: ";
				cin>>newPassword;
				Admin1.Admin_Password = newPassword;
				cout<<"UserName & Password Changed Successfully"<<endl;
				Admin_After_Login();
			}
			else{
				cout<<"Existing User Name or Password is Incorrect."<<endl;
				Admin_After_Login();
			}
		}
		else{
			cout<<"Not Valid Option Selected...."<<endl;
			Admin_After_Login();
		}

	}
	else if(option == 6)
	{
		Admin_Login();
	}
	else if(option == 7)
	{
		Admin_HomePage();
	}
	else if(option == 8)
	{
		HomePage();
	}
	else if(option == 9)
	{
		return;
	}
	else
	{
		cout<<"No Valid Option Selected..."<<endl;
		Admin_After_Login();
	}
}

// -----------------------------------------------------------
// UPDATE FACULTY HOMEPAGE FUNCTION
// -----------------------------------------------------------
void Faculty_HomePage() {
    Clear();
    SetColor(Font, Background);

    int option;

    cout << "\t\t\t ------------------------------------------------------\n"
         << "\t\t\t|                                                      |\n"
         << "\t\t\t|                  Faculty HomePage                    |\n"
         << "\t\t\t|                                                      |\n"
         << "\t\t\t ------------------------------------------------------\n" << endl;

    cout << "1. Login (For Time Table Incharge)\n"
         << "2. Login (For Faculty)\n"
         << "3. Register (For Faculty)\n"
         << "4. Go Back to Home Page\n"
         << "5. Exit\n"
         << "Select your option: ";

    cin >> option;

    if (option == 1) {
        handleTimetableInchargeLogin();
    }
    else if (option == 2) {
        handleFacultyLogin();
    }
    else if (option == 3) {
        displayFacultyRegistrationForm();
        Faculty_HomePage();
    }
    else if (option == 4) {
        HomePage();
    }
    else if (option == 5) {
        return;
    }
    else {
        cout << "Invalid Command!" << endl;
        Faculty_HomePage();
    }
}


// -----------------------------------------------------------
// FACULTY REGISTRATION FORM
// -----------------------------------------------------------
void displayFacultyRegistrationForm() {
    Clear();
    SetColor(Font, Background);
    
    cout << "\n========================================" << endl;
    cout << "      FACULTY REGISTRATION FORM" << endl;
    cout << "========================================\n" << endl;
    
    Faculty f1;
    string tempA;
    
    // Username
    LocationF:
    cout << "-> Enter Username: ";
    cin >> tempA;
    for (int i = 0; i < FacultyRegistrations.size(); i++) {
        if (FacultyRegistrations[i].getUsrId() == tempA) {
            cout << "This UserName Already Exists. Try Another UserName." << endl;
            goto LocationF;
        }
    }
    f1.setUserID(tempA);
    
    // Password
    cout << "-> Enter Password: ";
    cin >> tempA;
    f1.setPassword(tempA);
    
    // Personal Information
    cout << "-> Enter Your Full Name: ";
    cin.ignore();
    getline(cin, tempA);
    f1.setName(tempA);
    
    cout << "-> Enter Email: ";
    cin >> tempA;
    f1.setEmail(tempA);
    
    cout << "-> Enter Gender (Male/Female): ";
    cin >> tempA;
    f1.setGender(tempA);
    
    cout << "-> Enter Phone Number: ";
    cin >> tempA;
    f1.setPhone(tempA);
    
    // Department Selection
    cout << "\nSelect Your Department:" << endl;
    cout << "------------------------" << endl;
    for (int i = 0; i < Time_Table_Incharge.size(); i++) {
        cout << i + 1 << ". " << Time_Table_Incharge[i].getDepartmentName() << endl;
    }
    
    int deptChoice;
    cout << "\nEnter department number: ";
    cin >> deptChoice;
    
    if (deptChoice < 1 || deptChoice > Time_Table_Incharge.size()) {
        cout << "Invalid department selection!" << endl;
        return;
    }
    
    tempA = Time_Table_Incharge[deptChoice - 1].getDepartmentName();
    f1.setDepartment(tempA);
    
    // Designation
    cout << "Enter Designation (Professor/Assistant Professor/Lecturer): ";
    cin.ignore();
    getline(cin, tempA);
    f1.setDesignation(tempA);
    
    // Qualifications
    int qualCount;
    cout << "How many qualifications do you have? ";
    cin >> qualCount;
    cin.ignore();
    for (int i = 0; i < qualCount; i++) {
        cout << "Enter qualification " << i + 1 << ": ";
        getline(cin, tempA);
        f1.setQualifications(tempA);
    }
    
    // Specialized Courses
    int courseCount;
    cout << "How many specialized courses do you teach? ";
    cin >> courseCount;
    cin.ignore();
    for (int i = 0; i < courseCount; i++) {
        cout << "Enter specialized course " << i + 1 << ": ";
        getline(cin, tempA);
        f1.setSpecializedCourses(tempA);
    }
    
    // Faculty ID
    cout << "Enter Your Faculty ID (e.g., FAC-001): ";
    cin >> tempA;
    f1.setUniqueID(tempA);
    
    // Registration Date
    tempA = DateTime.getCurrentDate();
    f1.setRegistrationDate(tempA);
    
    // Set approval to pending
    f1.Approval("No");
    
    // Add to registrations
    FacultyRegistrations.push_back(f1);
    
    cout << "\n========================================" << endl;
    cout << "REGISTRATION SUCCESSFUL!" << endl;
    cout << "========================================" << endl;
    cout << "\nYour registration has been submitted." << endl;
    cout << "Please wait for department approval." << endl;
    cout << "\nRegistration Details:" << endl;
    cout << "---------------------" << endl;
    cout << "Name: " << f1.getName() << endl;
    cout << "Username: " << f1.getUsrId() << endl;
    cout << "Department: " << f1.getDepartment() << endl;
    cout << "Designation: " << f1.getDesignation() << endl;
    cout << "Faculty ID: " << f1.getUniqueID() << endl;
    cout << "Registration Date: " << f1.getRegistrationDate() << endl;
    cout << "========================================\n" << endl;
    
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

// -----------------------------------------------------------
// FACULTY LOGIN HANDLER
// -----------------------------------------------------------
void handleFacultyLogin() {
    Clear();
    SetColor(Font, Background);
    
    cout << "\n========================================" << endl;
    cout << "        FACULTY LOGIN" << endl;
    cout << "========================================" << endl;
    
    string usrNam, usrpass;
    bool isRegistered = false;
    int facultyIndex = -1;
    
    cout << "Enter Username: ";
    cin >> usrNam;
    cout << "Enter Password: ";
    cin >> usrpass;
    
    // Check credentials
    for (int i = 0; i < FacultyRegistrations.size(); i++) {
        if (FacultyRegistrations[i].authenticate(usrNam, usrpass)) {
            if (FacultyRegistrations[i].ApprovalStatus()) {
                isRegistered = true;
                facultyIndex = i;
                break;
            }
            else {
                cout << "\nYour account is pending approval." << endl;
                cout << "Please contact your department for approval." << endl;
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                return;
            }
        }
    }
    
    if (isRegistered && facultyIndex != -1) {
        cout << "\nLogin successful!" << endl;
        FacultyOptionsPage(facultyIndex);
    }
    else {
        cout << "\nIncorrect Username or Password!" << endl;
        cout << "\nOptions:" << endl;
        cout << "1. Try Again" << endl;
        cout << "2. Register New Account" << endl;
        cout << "3. Back to Home Page" << endl;
        
        int choice;
        cout << "\nEnter choice: ";
        cin >> choice;
        
        if (choice == 1) {
            handleFacultyLogin();
        }
        else if (choice == 2) {
            displayFacultyRegistrationForm();
            Faculty_HomePage();
        }
        else if (choice == 3) {
            HomePage();
        }
    }
}

// -----------------------------------------------------------
// TIMETABLE INCHARGE LOGIN
// -----------------------------------------------------------
void handleTimetableInchargeLogin() {
    Clear();
    SetColor(Font, Background);
    
    cout << "\n========================================" << endl;
    cout << "    TIMETABLE INCHARGE LOGIN" << endl;
    cout << "========================================\n" << endl;
    
    string deptName, password;
    bool found = false;
    int deptIndex = -1;
    
    cout << "-> Enter Department Name: ";
    cin >> deptName;
    cout << "-> Enter Password: ";
    cin >> password;
    
    // Check credentials
    for (int i = 0; i < Time_Table_Incharge.size(); i++) {
        if (Time_Table_Incharge[i].DepartmentLogin(deptName, password)) {
            found = true;
            deptIndex = i;
            break;
        }
    }
    
    if (found) {
        cout << "\n Login successful!" << endl;
        TimeTableInchargeOptionsPage(deptIndex);
    }
    else {
        cout << "\nInvalid department name or password!" << endl;
        cout << "\nOptions:" << endl;
        cout << "1. Try Again" << endl;
        cout << "2. Back to Home Page" << endl;
        cout << "3. Exit" << endl;
        
        int choice;
        cout << "\nEnter choice: ";
        cin >> choice;
        
        if (choice == 1) {
           handleTimetableInchargeLogin();
        }
        else if (choice == 2) {
            HomePage();
        }
        else if (choice == 3) {
            return;
        }
    }
}



// -----------------------------------------------------------
// FACULTY OPTIONS PAGE
// -----------------------------------------------------------
void FacultyOptionsPage(int vectorNumber) {
    Clear();
    SetColor(Font, Background);
    int opt;
    
    cout << "Faculty Mode" << endl;
    string FacultyNAME = FacultyRegistrations[vectorNumber].getName();
    cout << "Welcome" << FacultyNAME << "!" << endl;
    
    do {
        Clear();
        SetColor(Font, Background);
        
        cout << "\n========================================" << endl;
        cout << "        FACULTY DASHBOARD" << endl;
        cout << "========================================" << endl;
        cout << "Name: " << FacultyRegistrations[vectorNumber].getName() << endl;
        cout << "Department: " << FacultyRegistrations[vectorNumber].getDepartment() << endl;
        cout << "Designation: " << FacultyRegistrations[vectorNumber].getDesignation() << endl;
        cout << "Teaching Hours: " << FacultyRegistrations[vectorNumber].getCurrentTeachingHours() << " hours/week" << endl;
        cout << "========================================\n" << endl;
        
        cout << "1. Display Profile" << endl;
        cout << "2. Change Password" << endl;
        cout << "3. View/Edit Qualifications" << endl;
        cout << "4. View/Edit Specialized Courses" << endl;
        cout << "5. Set Weekly Availability" << endl;
        cout << "6. View Weekly Availability" << endl;
        cout << "7. View Assigned Courses" << endl;
        cout << "8. Add New Slot for Course" << endl;
        cout << "9. Remove Slot" << endl;
        cout << "10. View Pending Slots" << endl;
        cout << "11. View Approved Slots" << endl;
        cout << "12. Add Complaint" << endl;
        cout << "13. Check Complaint Status" << endl;
        cout << "14. View Daily Schedule" << endl;
        cout << "15. View Weekly Timetable" << endl;
        cout << "16. Export Weekly Timetable to CSV" << endl;
        cout << "17. Export Daily Schedule to CSV" << endl;
        cout << "18. View Department Timetable Incharge" << endl;
        cout << "19. HomePage" << endl;
        cout << "20. Logout" << endl;
        cout << "\nSelect your option: ";
        cin >> opt;
        
        if (opt == 1) {
            // Display Profile
            Clear();
            SetColor(3, 0);
            cout << "\n========================================" << endl;
            cout << "         FACULTY PROFILE" << endl;
            cout << "========================================" << endl;
            FacultyRegistrations[vectorNumber].displayProfile();
            cout << "Designation: " << FacultyRegistrations[vectorNumber].getDesignation() << endl;
            cout << "Faculty ID: " << FacultyRegistrations[vectorNumber].getUniqueID() << endl;
            cout << "Current Teaching Hours: " << FacultyRegistrations[vectorNumber].getCurrentTeachingHours() << endl;
            cout << "========================================\n" << endl;
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 2) {
            // Change Password
            Clear();
            SetColor(2, 0);
            string existingPass, newPass;
            cout << "\n========================================" << endl;
            cout << "        CHANGE PASSWORD" << endl;
            cout << "========================================" << endl;
            
            cout << "Enter Your Existing Password: ";
            cin >> existingPass;
            cout << "Enter New Password: ";
            cin >> newPass;
            
            if (FacultyRegistrations[vectorNumber].ChangePassword(existingPass, newPass)) {
                cout << "\n Password Changed Successfully!" << endl;
            }
            else {
                cout << "\n Incorrect Existing Password! Try Again!" << endl;
            }
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 3) {
            // View/Edit Qualifications
            Clear();
            SetColor(6, 0);
            int qualOpt;
            do {
                Clear();
                cout << "\n========================================" << endl;
                cout << "      QUALIFICATIONS MANAGEMENT" << endl;
                cout << "========================================" << endl;
                
                FacultyRegistrations[vectorNumber].displayQualifications();
                
                cout << "\nOptions:" << endl;
                cout << "1. Add Qualification" << endl;
                cout << "2. Remove Qualification" << endl;
                cout << "3. Back to Main Menu" << endl;
                cout << "Select option: ";
                cin >> qualOpt;
                
                if (qualOpt == 1) {
                    string qual;
                    cout << "Enter new qualification: ";
                    cin.ignore();
                    getline(cin, qual);
                    FacultyRegistrations[vectorNumber].setQualifications(qual);
                    cout << " Qualification added successfully!" << endl;
                }
                else if (qualOpt == 2) {
                    string qual;
                    cout << "Enter qualification to remove: ";
                    cin.ignore();
                    getline(cin, qual);
                    FacultyRegistrations[vectorNumber].removeQualifications(qual);
                    cout << "Qualification removed successfully!" << endl;
                }
                
                if (qualOpt != 3) {
                    cout << "\nPress Enter to continue...";
                    cin.get();
                }
            } while (qualOpt != 3);
        }
        else if (opt == 4) {
            // View/Edit Specialized Courses
            Clear();
            SetColor(5, 0);
            int courseOpt;
            do {
                Clear();
                cout << "\n========================================" << endl;
                cout << "   SPECIALIZED COURSES MANAGEMENT" << endl;
                cout << "========================================" << endl;
                
                vector<string> courses = FacultyRegistrations[vectorNumber].getSpecializedCourses();
                cout << "Specialized Courses:" << endl;
                for (int i = 0; i < courses.size(); i++) {
                    cout << i + 1 << ". " << courses[i] << endl;
                }
                if (courses.empty()) {
                    cout << "No specialized courses added." << endl;
                }
                
                cout << "\nOptions:" << endl;
                cout << "1. Add Specialized Course" << endl;
                cout << "2. Remove Specialized Course" << endl;
                cout << "3. Back to Main Menu" << endl;
                cout << "Select option: ";
                cin >> courseOpt;
                
                if (courseOpt == 1) {
                    string course;
                    cout << "Enter new specialized course: ";
                    cin.ignore();
                    getline(cin, course);
                    FacultyRegistrations[vectorNumber].setSpecializedCourses(course);
                    cout << "Specialized course added successfully!" << endl;
                }
                else if (courseOpt == 2) {
                    string course;
                    cout << "Enter course to remove: ";
                    cin.ignore();
                    getline(cin, course);
                    FacultyRegistrations[vectorNumber].removeSpecializedCourses(course);
                    cout << "Specialized course removed successfully!" << endl;
                }
                
                if (courseOpt != 3) {
                    cout << "\nPress Enter to continue...";
                    cin.get();
                }
            } while (courseOpt != 3);
        }
        else if (opt == 5) {
            // Set Weekly Availability
            Clear();
            SetColor(4, 0);
            cout << "\n========================================" << endl;
            cout << "      SET WEEKLY AVAILABILITY" << endl;
            cout << "========================================" << endl;
            
            FacultyRegistrations[vectorNumber].setWeeklyAvailability();
            cout << "\n Availability set successfully!" << endl;
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 6) {
            // View Weekly Availability
            Clear();
            SetColor(7, 0);
            int day;
            cout << "\n========================================" << endl;
            cout << "      WEEKLY AVAILABILITY" << endl;
            cout << "========================================" << endl;
            
            cout << "Enter day number (1-"<<numberOfDays<<"): ";
            cin >> day;
            
            if (day >= 1 && day <= 5) {
                FacultyRegistrations[vectorNumber].displayAvailabilityByDay(day);
            }
            else {
                cout << "Invalid day number!" << endl;
            }
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 7) {
            // View Assigned Courses
            Clear();
            SetColor(2, 0);
            cout << "\n========================================" << endl;
            cout << "      ASSIGNED COURSES" << endl;
            cout << "========================================" << endl;
            
            FacultyRegistrations[vectorNumber].displayAssignedCourses();
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 8) {
            // Add New Slot for Course
            Clear();
            SetColor(3, 0);
            cout << "\n========================================" << endl;
            cout << "        ADD NEW SLOT" << endl;
            cout << "========================================" << endl;
            
            FacultyRegistrations[vectorNumber].AddSlot();
            cout << "\n Slot added successfully! Waiting for approval." << endl;
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 9) {
            // Remove Slot
            Clear();
            SetColor(4, 0);
            cout << "\n========================================" << endl;
            cout << "        REMOVE SLOT" << endl;
            cout << "========================================" << endl;
            
            FacultyRegistrations[vectorNumber].removeSlot();
            cout << "\nSlot removed successfully!" << endl;
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 10) {
            // View Pending Slots
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "        PENDING SLOTS" << endl;
            cout << "========================================" << endl;
            
            FacultyRegistrations[vectorNumber].pendingSlots();
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 11) {
            // View Approved Slots
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "        APPROVED SLOTS" << endl;
            cout << "========================================" << endl;
            
            FacultyRegistrations[vectorNumber].ApprovedSlots();
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 12) {
            // Add Complaint
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "        ADD COMPLAINT" << endl;
            cout << "========================================" << endl;
            
            cin.ignore();
            FacultyRegistrations[vectorNumber].addComplain();
            cout << "\nComplaint submitted successfully!" << endl;
            
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        else if (opt == 13) {
            // Check Complaint Status
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "      COMPLAINT STATUS" << endl;
            cout << "========================================" << endl;
            
            FacultyRegistrations[vectorNumber].ComplaintStatus();
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 14) {
            // View Daily Schedule
            Clear();
            SetColor(Font, Background);
            int day;
            cout << "\n========================================" << endl;
            cout << "      DAILY SCHEDULE" << endl;
            cout << "========================================" << endl;
            
            cout << "Enter day number (1-5 for Monday-Friday): ";
            cin >> day;
            
            if (day >= 1 && day <= 5) {
                FacultyRegistrations[vectorNumber].displayDailySchedule(day);
            }
            else {
                cout << "Invalid day number!" << endl;
            }
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 15) {
            // View Weekly Timetable
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "      WEEKLY TIMETABLE" << endl;
            cout << "========================================" << endl;
            
            FacultyRegistrations[vectorNumber].displayTimeTable();
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 16) {
    // Export Weekly Timetable to CSV
    Clear();
    SetColor(Font, Background);
    cout << "\n==========================================" << endl;
    cout << "   EXPORT WEEKLY TIMETABLE TO CSV" << endl;
    cout << "==========================================" << endl;
    FacultyRegistrations[vectorNumber].exportTimetableToCSV();
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}
else if (opt == 17) {
    // Export Daily Schedule to CSV
    Clear();
    SetColor(Font, Background);
    cout << "\n==========================================" << endl;
    cout << "   EXPORT DAILY SCHEDULE TO CSV" << endl;
    cout << "==========================================" << endl;
    int day;
    cout << "Enter day number (1-5 for Monday-Friday): ";
    cin >> day;
    if (day >= 1 && day <= 5) {
        FacultyRegistrations[vectorNumber].exportDailyScheduleToCSV(day);
    } else {
        cout << "Invalid day number!" << endl;
    }
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}
        else if (opt == 18) {
            // View Department Timetable Incharge
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "  DEPARTMENT TIMETABLE INCHARGE" << endl;
            cout << "========================================" << endl;
            
            FacultyRegistrations[vectorNumber].displayDepartmentTimeTableIncharge();
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 19) {
            HomePage();
        }
        else if (opt == 20) {
            // Logout
            cout << "\nLogging out..." << endl;
            return;
        }
        else {
            cout << "\nInvalid option! Please try again." << endl;
            //this_thread::sleep_for(chrono::seconds(1));
        }
        
    } while (opt != 19);
}

// -----------------------------------------------------------
// TIMETABLE INCHARGE OPTIONS PAGE
// -----------------------------------------------------------
void TimeTableInchargeOptionsPage(int vectorNumber) {
    Clear();
    SetColor(Font, Background);
    int opt;
    
    cout << "Timetable Incharge Mode" << endl;
    string DeptNAME = Time_Table_Incharge[vectorNumber].getDepartmentName();
    cout << "Welcome to " << DeptNAME << " Department!" << endl;
    
    do {
        Clear();
        SetColor(Font, Background);
        
        cout << "\n========================================" << endl;
        cout << "    TIMETABLE INCHARGE DASHBOARD" << endl;
        cout << "========================================" << endl;
        cout << "Department: " << Time_Table_Incharge[vectorNumber].getDepartmentName() << endl;
        cout << "Head of Department: " << Time_Table_Incharge[vectorNumber].getHeadOfDepartment() << endl;
        cout << "Timetable Incharge: " << Time_Table_Incharge[vectorNumber].getTimetableIncharge() << endl;
        cout << "========================================\n" << endl;
        
        cout << "1. View Department Profile" << endl;
        cout << "2. Change Password" << endl;
        cout << "3. Approve Faculty Registrations" << endl;
        cout << "4. Approve Student Registrations" << endl;
        cout << "5. Faculty Statistics" << endl;
        cout << "6. Student Statistics" << endl;
        cout << "7. View Faculty Members" << endl;
        cout << "8. View Enrolled Students" << endl;
        cout << "9. View Courses" << endl;
        cout << "10. Add Course" << endl;
        cout << "11. Remove Course" << endl;
        cout << "12. View Courses by Semester" << endl;
        cout << "13. View Courses by Faculty" << endl;
        cout << "14. View Students by Semester" << endl;
        cout << "15. Approve/Reject Slots" << endl;
        cout << "16. View Department Timetable" << endl;
        cout << "17. View Semester Timetable" << endl;
        cout << "18. View Faculty Timetable" << endl;
        cout << "19. View Complaints" << endl;
        cout << "20. Export Department Timetable to CSV" << endl;
        cout << "21. Export Semester Timetable to CSV" << endl;
        cout << "22. Export Faculty Timetable to CSV" << endl;
        cout << "23. HomePage" <<endl;
        cout << "24. Logout" << endl;
        cout << "\nSelect your option: ";
        cin >> opt;
        
        if (opt == 1) {
            // View Department Profile
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "      DEPARTMENT PROFILE" << endl;
            cout << "========================================" << endl;
            
            Time_Table_Incharge[vectorNumber].ViewDepartmentProfile();
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 2) {
            // Change Password
            Clear();
            SetColor(Font, Background);
            string oldPass, newPass;
            cout << "\n========================================" << endl;
            cout << "        CHANGE PASSWORD" << endl;
            cout << "========================================" << endl;
            
            cout << "Enter Old Password: ";
            cin >> oldPass;
            cout << "Enter New Password: ";
            cin >> newPass;
            
            if (Time_Table_Incharge[vectorNumber].changePassword(oldPass, newPass)) {
                cout << "\nPassword Changed Successfully!" << endl;
            }
            else {
                cout << "\nIncorrect Old Password!" << endl;
            }
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 3) {
            // Approve Faculty Registrations
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "   APPROVE FACULTY REGISTRATIONS" << endl;
            cout << "========================================" << endl;
            
            Time_Table_Incharge[vectorNumber].ApproveFaculty();
            cout << "\nFaculty approval process completed!" << endl;
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 4) {
            // Approve Student Registrations
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "   APPROVE STUDENT REGISTRATIONS" << endl;
            cout << "========================================" << endl;
            
            Time_Table_Incharge[vectorNumber].ApproveStudent();
            cout << "\nStudent approval process completed!" << endl;
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 5) {
            // Faculty Statistics
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "      FACULTY STATISTICS" << endl;
            cout << "========================================" << endl;
            
            Time_Table_Incharge[vectorNumber].FacultyStatistics();
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 6) {
            // Student Statistics
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "      STUDENT STATISTICS" << endl;
            cout << "========================================" << endl;
            
            Time_Table_Incharge[vectorNumber].StudentsStatistics();
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 7) {
            // View Faculty Members
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "      FACULTY MEMBERS" << endl;
            cout << "========================================" << endl;
            
            Time_Table_Incharge[vectorNumber].displayFacultyMembers();
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 8) {
            // View Enrolled Students
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "      ENROLLED STUDENTS" << endl;
            cout << "========================================" << endl;
            
            Time_Table_Incharge[vectorNumber].displayEnrolledStudents();
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 9) {
            // View Courses
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "      DEPARTMENT COURSES" << endl;
            cout << "========================================" << endl;
            
            Time_Table_Incharge[vectorNumber].displayCourses();
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 10) {
            // Add Course
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "        ADD NEW COURSE" << endl;
            cout << "========================================" << endl;
            
            Course newCourse;
            string temp;
            int tempInt;
            
            cout << "Enter Course Name: ";
            cin.ignore();
            getline(cin, temp);
            newCourse.courseName = temp;
            
            cout << "Enter Course ID: ";
            getline(cin, temp);
            newCourse.courseID = temp;
            
            cout << "Enter Course Type (Theory/Lab): ";
            getline(cin, temp);
            newCourse.CourseType = temp;
            
            cout << "Enter Credit Hours: ";
            cin >> tempInt;
            newCourse.credit_hours = tempInt;
            
            cout << "Enter Semester (1-8): ";
            cin >> tempInt;
            newCourse.semester = tempInt;
            
            newCourse.department = Time_Table_Incharge[vectorNumber].getDepartmentName();
            newCourse.isScheduled = false;
            newCourse.ClassSchedule = nullptr;
            
            // Assign faculty
            cout << "\nAvailable Faculty:" << endl;
            Time_Table_Incharge[vectorNumber].displayFacultyMembers();
            
            cout << "Enter Faculty Name to assign: ";
            cin.ignore();
            getline(cin, temp);
            
            // Find faculty and assign
            bool facultyFound = false;
            for (int i = 0; i < FacultyRegistrations.size(); i++) {
                if (FacultyRegistrations[i].getName() == temp && FacultyRegistrations[i].getDepartment() == Time_Table_Incharge[vectorNumber].getDepartmentName() && FacultyRegistrations[i].ApprovalStatus()) {
                    AllCourses.push_back(newCourse);
                    Course& addedCourse = AllCourses.back();
                    addedCourse.assignedFaculty = &FacultyRegistrations[i];
                    FacultyRegistrations[i].addAssignedCourses(addedCourse);
                    facultyFound = true;
                    cout << "Course assigned to "<<temp<<" successfully!"<<endl;
                    break;
                }
            }
            
            if(!facultyFound) {
                cout<<"Faculty not found or not approved! Course added without faculty assignment."<<endl;
                AllCourses.push_back(newCourse);
            }

            cout << "\nPress Enter to continue...";
            cin.get();
        }
        else if (opt == 11) {
            // Remove Course
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "        REMOVE COURSE" << endl;
            cout << "========================================" << endl;
            
            string courseID;
            cout << "Enter Course ID to remove: ";
            cin >> courseID;
            
            Time_Table_Incharge[vectorNumber].removeCourse(courseID);
            cout << "\nCourse removed successfully!" << endl;
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 12) {
            // View Courses by Semester
            Clear();
            SetColor(Font, Background);
            int semester;
            cout << "\n========================================" << endl;
            cout << "      COURSES BY SEMESTER" << endl;
            cout << "========================================" << endl;
            
            cout << "Enter Semester (1-8): ";
            cin >> semester;
            
            vector<Course> semesterCourses = Time_Table_Incharge[vectorNumber].getCourseBySemester(semester);
            
            cout << "\nCourses for Semester " << semester << ":" << endl;
            cout << "----------------------------------------" << endl;
            for (int i = 0; i < semesterCourses.size(); i++) {
                cout << i + 1 << ". " << semesterCourses[i].courseName 
                     << " (" << semesterCourses[i].courseID << ")" 
                     << " - " << semesterCourses[i].assignedFaculty->getName() << endl;
            }
            if (semesterCourses.empty()) {
                cout << "No courses found for this semester." << endl;
            }
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 13) {
            // View Courses by Faculty
            Clear();
            SetColor(Font, Background);
            string facultyName;
            cout << "\n========================================" << endl;
            cout << "      COURSES BY FACULTY" << endl;
            cout << "========================================" << endl;
            
            cout << "Enter Faculty Name: ";
            cin.ignore();
            getline(cin, facultyName);
            
            // Find faculty
            Faculty targetFaculty;
            bool found = false;
            for (int i = 0; i < FacultyRegistrations.size(); i++) {
                if (FacultyRegistrations[i].getName() == facultyName && 
                    FacultyRegistrations[i].getDepartment() == Time_Table_Incharge[vectorNumber].getDepartmentName()) {
                    targetFaculty = FacultyRegistrations[i];
                    found = true;
                    break;
                }
            }
            
            if (found) {
                vector<Course> facultyCourses = Time_Table_Incharge[vectorNumber].getCourseByFaculty(targetFaculty);
                
                cout << "\nCourses taught by " << facultyName << ":" << endl;
                cout << "----------------------------------------" << endl;
                for (int i = 0; i < facultyCourses.size(); i++) {
                    cout << i + 1 << ". " << facultyCourses[i].courseName 
                         << " (" << facultyCourses[i].courseID << ")" 
                         << " - Semester " << facultyCourses[i].semester << endl;
                }
                if (facultyCourses.empty()) {
                    cout << "No courses assigned to this faculty." << endl;
                }
            }
            else {
                cout << "Faculty not found in this department." << endl;
            }
            
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        else if (opt == 14) {
            // View Students by Semester
            Clear();
            SetColor(Font, Background);
            int semester;
            cout << "\n========================================" << endl;
            cout << "      STUDENTS BY SEMESTER" << endl;
            cout << "========================================" << endl;
            
            cout << "Enter Semester (1-8): ";
            cin >> semester;
            
            Time_Table_Incharge[vectorNumber].displayEnrolledStudentsBySemester(semester);
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 15) {
            // Approve/Reject Slots
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "      APPROVE/REJECT SLOTS" << endl;
            cout << "========================================" << endl;
            
            bool hasPending = false;
            vector<int> pendingIndices;
            
            cout << "Pending Slots for Approval:" << endl;
            cout << "----------------------------" << endl;
            
            for (int i = 0; i < MySlots.size(); i++) {
                if (MySlots[i].DEPT->getDepartmentName() == Time_Table_Incharge[vectorNumber].getDepartmentName() && !MySlots[i].SlotStatus) {
                    cout << pendingIndices.size() + 1 << ". " << MySlots[i].SUBJECT.courseName 
                         << " by " << MySlots[i].Instructor->getName()
                         << " on " << MySlots[i].Day 
                         << " (" << MySlots[i].Times.Start_Time << " - " << MySlots[i].Times.End_Time << ")"
                         << " - Semester " << MySlots[i].semester << endl;
                    pendingIndices.push_back(i);
                    hasPending = true;
                }
            }
            
            if (!hasPending) {
                cout << "No pending slots for approval." << endl;
            }
            else {
                int slotChoice;
                char approveChoice;
                
                cout << "\nSelect slot number to approve/reject (0 to cancel): ";
                cin >> slotChoice;
                
                if (slotChoice > 0 && slotChoice <= pendingIndices.size()) {
                    int slotIndex = pendingIndices[slotChoice - 1];
                    
                    cout << "\nApprove this slot? (Y/N): ";
                    cin >> approveChoice;
                    
                    if (approveChoice == 'Y' || approveChoice == 'y') {
                        MySlots[slotIndex].SlotStatus = true;
                        
                        // Update the course's schedule
                        for (int i = 0; i < AllCourses.size(); i++) {
                            if (AllCourses[i].courseID == MySlots[slotIndex].SUBJECT.courseID &&
                                AllCourses[i].department == Time_Table_Incharge[vectorNumber].getDepartmentName()) {
                                AllCourses[i].ClassSchedule = &MySlots[slotIndex];
                                AllCourses[i].isScheduled = true;
                                break;
                            }
                        }
                        
                        cout << "Slot approved successfully!" << endl;
                    }
                    else {
                        MySlots.erase(MySlots.begin() + slotIndex);
                        cout << "Slot rejected and removed!" << endl;
                    }
                }
            }
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 16) {
            // View Department Timetable
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "      DEPARTMENT TIMETABLE" << endl;
            cout << "========================================" << endl;
            
            Time_Table_Incharge[vectorNumber].displayDepartmentTimetable();
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 17) {
            // View Semester Timetable
            Clear();
            SetColor(Font, Background);
            int semester;
            cout << "\n========================================" << endl;
            cout << "      SEMESTER TIMETABLE" << endl;
            cout << "========================================" << endl;
            
            cout << "Enter Semester (1-8): ";
            cin >> semester;
            
            Time_Table_Incharge[vectorNumber].displaySemesterTimetable(semester);
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 18) {
            // View Faculty Timetable
            Clear();
            SetColor(Font, Background);
            string facultyName;
            cout << "\n========================================" << endl;
            cout << "      FACULTY TIMETABLE" << endl;
            cout << "========================================" << endl;
            
            cout << "Enter Faculty Name: ";
            cin.ignore();
            getline(cin, facultyName);
            
            Time_Table_Incharge[vectorNumber].displayFacultyTimetable(facultyName);
            
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        else if (opt == 19) {
            // View Complaints
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "      DEPARTMENT COMPLAINTS" << endl;
            cout << "========================================" << endl;
            
            int complaintType;
            cout << "1. Faculty Complaints" << endl;
            cout << "2. Student Complaints" << endl;
            cout << "Select complaint type: ";
            cin >> complaintType;
            
            if (complaintType == 1) {
                cout << "\nFaculty Complaints:" << endl;
                cout << "-------------------" << endl;
                for (int i = 0; i < FACULTY_COMPLAINTS.size(); i++) {
                    if (FACULTY_COMPLAINTS[i].dept == Time_Table_Incharge[vectorNumber].getDepartmentName()) {
                        cout << "Complaint #" << i + 1 << endl;
                        cout << "Subject: " << FACULTY_COMPLAINTS[i].subject << endl;
                        cout << "From: " << FACULTY_COMPLAINTS[i].Faculty_A->getName() << endl;
                        cout << "Status: " << (FACULTY_COMPLAINTS[i].status ? "Resolved" : "Pending") << endl;
                        cout << "-------------------" << endl;
                    }
                }
                
                // Option to resolve complaints
                int resolveChoice;
                cout << "\nEnter complaint number to resolve (0 to skip): ";
                cin >> resolveChoice;
                
                if (resolveChoice > 0 && resolveChoice <= FACULTY_COMPLAINTS.size()) {
                    FACULTY_COMPLAINTS[resolveChoice - 1].status = true;
                    cout << "Complaint marked as resolved!" << endl;
                }
            }
            else if (complaintType == 2) {
                cout << "\nStudent Complaints:" << endl;
                cout << "-------------------" << endl;
                for (int i = 0; i < STUDENT_COMPLAINTS.size(); i++) {
                    if (STUDENT_COMPLAINTS[i].dept == Time_Table_Incharge[vectorNumber].getDepartmentName()) {
                        cout << "Complaint #" << i + 1 << endl;
                        cout << "Subject: " << STUDENT_COMPLAINTS[i].subject << endl;
                        cout << "From: " << STUDENT_COMPLAINTS[i].Student_A->getName() << endl;
                        cout << "Status: " << (STUDENT_COMPLAINTS[i].status ? "Resolved" : "Pending") << endl;
                        cout << "-------------------" << endl;
                    }
                }
                
                // Option to resolve complaints
                int resolveChoice;
                cout << "\nEnter complaint number to resolve (0 to skip): ";
                cin >> resolveChoice;
                
                if (resolveChoice > 0 && resolveChoice <= STUDENT_COMPLAINTS.size()) {
                    STUDENT_COMPLAINTS[resolveChoice - 1].status = true;
                    cout << "Complaint marked as resolved!" << endl;
                }
            }
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 20) {
    // Export Department Timetable to CSV
    Clear();
    SetColor(Font, Background);
    cout << "\n==========================================" << endl;
    cout << "   EXPORT DEPARTMENT TIMETABLE TO CSV" << endl;
    cout << "==========================================" << endl;
    Time_Table_Incharge[vectorNumber].exportDepartmentTimetableToCSV();
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
    }
    else if (opt == 21) {
    // Export Semester Timetable to CSV
    Clear();
    SetColor(Font, Background);
    cout << "\n==========================================" << endl;
    cout << "   EXPORT SEMESTER TIMETABLE TO CSV" << endl;
    cout << "==========================================" << endl;
    int semester;
    cout << "Enter Semester (1-8): ";
    cin >> semester;
    if (semester >= 1 && semester <= 8) {
        Time_Table_Incharge[vectorNumber].exportSemesterTimetableToCSV(semester);
    } else {
        cout << "Invalid semester!" << endl;
    }
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
    }
    else if (opt == 22) {
    // Export Faculty Timetable to CSV
    Clear();
    SetColor(Font, Background);
    cout << "\n==========================================" << endl;
    cout << "   EXPORT FACULTY TIMETABLE TO CSV" << endl;
    cout << "==========================================" << endl;
    string facultyName;
    cout << "Enter Faculty Name: ";
    cin.ignore();
    getline(cin, facultyName);
    Time_Table_Incharge[vectorNumber].exportFacultyTimetableToCSV(facultyName);
    cout << "\nPress Enter to continue...";
    cin.get();
    }
        else if(opt == 23)
        {
            HomePage();
        }
        else if (opt == 24) {
            // Logout
            cout << "\nLogging out..." << endl;
            return;
        }
        else {
            cout << "\nInvalid option! Please try again." << endl;
        }
        
    } while (opt != 23);
}



void Student_HomePage()
{
    Clear();
    SetColor(Font, Background);
    
    cout << "\n ------------------------------------------ \n"
         << "|                                          |\n"
         << "|            STUDENT HOME PAGE             |\n"
         << "|                                          |\n"
         << " ------------------------------------------ \n";
    
    int option;
    cout << "\n1. Login as a Student\n"
         << "2. Register a new Student Account\n"
         << "3. Back to Main Menu\n"
         << "4. Exit\n"
         << "\nSelect Your Option: ";
    cin >> option;
    
    if (option == 1) {
        handleStudentLogin();
    }
    else if (option == 2) {
        displayStudentRegistrationForm();
        Student_HomePage();
    }
    else if (option == 3) {
        HomePage();
    }
    else if (option == 4) {
        return;
    }
    else {
        cout << "\nInvalid option!" << endl;
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        Student_HomePage();
    }
}

// -----------------------------------------------------------
// COMPLETE STUDENT MODULE IMPLEMENTATION
// -----------------------------------------------------------

void StudentOptionsPage(int vectorNumber)
{
    Clear();
    SetColor(Font, Background);
    int opt;
    
    cout << "Student Mode" << endl;
    string StudentNAME = StudentRegistrations[vectorNumber].getName();
    cout << "Welcome " << StudentNAME << "!" << endl;
    
    do {
        Clear();
        SetColor(Font, Background);
        
        cout << "\n========================================" << endl;
        cout << "        STUDENT DASHBOARD" << endl;
        cout << "========================================" << endl;
        cout << "Name: " << StudentRegistrations[vectorNumber].getName() << endl;
        cout << "Department: " << StudentRegistrations[vectorNumber].getDepartment() << endl;
        cout << "Semester: " << StudentRegistrations[vectorNumber].getSemester() << endl;
        cout << "========================================\n" << endl;
        
        cout << "1. Display Profile" << endl;
        cout << "2. Change Password" << endl;
        cout << "3. View All Courses" << endl;
        cout << "4. View Course Analytics" << endl;
        cout << "5. View Faculty by Course" << endl;
        cout << "6. View Course Details by ID" << endl;
        cout << "7. Display Course Schedule by CourseID" << endl;
        cout << "8. Add a new Complaint" << endl;
        cout << "9. Check Complaint Status" << endl;
        cout << "10. View TimeTable (Day-wise)" << endl;
        cout << "11. View Weekly TimeTable" << endl;
        cout << "12. View TimeTable (Tabular Form)" << endl;
        cout << "13. Export Weekly Timetable to CSV" << endl;
        cout << "14. Export Tabular Timetable to CSV" << endl;
        cout << "15. HomePage" << endl;
        cout << "16. Logout" << endl;
        cout << "\nSelect your option: ";
        cin >> opt;
        
        if (opt == 1) {
            // Display Profile
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "         STUDENT PROFILE" << endl;
            cout << "========================================" << endl;
            StudentRegistrations[vectorNumber].displayProfile();
            cout << "Semester: " << StudentRegistrations[vectorNumber].getSemester() << endl;
            cout << "Registration No: " << StudentRegistrations[vectorNumber].getUniqueID() << endl;
            cout << "========================================\n" << endl;
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 2) {
            // Change Password
            Clear();
            SetColor(Font, Background);
            string existingPass, newPass;
            cout << "\n========================================" << endl;
            cout << "        CHANGE PASSWORD" << endl;
            cout << "========================================" << endl;
            
            cout << "Enter Your Existing Password: ";
            cin >> existingPass;
            cout << "Enter New Password: ";
            cin >> newPass;
            
            if (StudentRegistrations[vectorNumber].ChangePassword(existingPass, newPass)) {
                cout << "\nPassword Changed Successfully!" << endl;
            }
            else {
                cout << "\nIncorrect Existing Password! Try Again!" << endl;
            }
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 3) {
            // View All Courses
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "       COURSES - SEMESTER " << StudentRegistrations[vectorNumber].getSemester() << endl;
            cout << "========================================" << endl;
            StudentRegistrations[vectorNumber].ViewCourses();
            cout << "========================================\n" << endl;
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 4) {
            // View Course Analytics
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "         COURSE ANALYTICS" << endl;
            cout << "========================================" << endl;
            
            int totalHours = StudentRegistrations[vectorNumber].getTotalCreditHours();
            vector<Course> courses = StudentRegistrations[vectorNumber].getCourses();
            
            cout << "Semester: " << StudentRegistrations[vectorNumber].getSemester() << endl;
            cout << "Total Credit Hours: " << totalHours << endl;
            cout << "Number of Courses: " << courses.size() << endl;
            cout << "\n--- Course Breakdown ---" << endl;
            
            int theoryCount = 0, labCount = 0;
            for (const auto& course : courses) {
                if (course.CourseType == "Theory") theoryCount++;
                else if (course.CourseType == "Lab") labCount++;
            }
            
            cout << "Theory Courses: " << theoryCount << endl;
            cout << "Lab Courses: " << labCount << endl;
            
            cout << "\n--- Department Statistics ---" << endl;
            cout << "Working Days: " << numberOfDays << " (Monday to Friday)" << endl;
            cout << "Lectures per Day: " << maxLecturesPerDay << endl;
            cout << "Total Available Slots per Week: " << numberOfDays * maxLecturesPerDay << endl;
            
            cout << "========================================\n" << endl;
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 5) {
            // View Faculty by Course
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "      FACULTY BY COURSE" << endl;
            cout << "========================================" << endl;
            
            // First show available courses
            StudentRegistrations[vectorNumber].ViewCourses();
            
            string courseID;
            cout << "\nEnter Course ID to view faculty (e.g., CS101): ";
            cin >> courseID;
            
            pair<string, string> facultyInfo = StudentRegistrations[vectorNumber].getFacultyByCourse(courseID);
            
            if (facultyInfo.first != "0" && facultyInfo.second != "0") {
                cout << "\n--- Faculty Details ---" << endl;
                cout << "Course ID: " << courseID << endl;
                cout << "Faculty Name: " << facultyInfo.first << endl;
                cout << "Faculty ID: " << facultyInfo.second << endl;
            }
            else {
                cout << "\nCourse not found or no faculty assigned!" << endl;
            }
            
            cout << "========================================\n" << endl;
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 6) {
            // View Course Details by ID
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "      COURSE DETAILS" << endl;
            cout << "========================================" << endl;
            
            // First show available courses
            StudentRegistrations[vectorNumber].ViewCourses();
            
            string courseID;
            cout << "\nEnter Course ID to view details (e.g., CS101): ";
            cin >> courseID;
            
            StudentRegistrations[vectorNumber].ViewCourseDetailsByCourseID(courseID);
            
            cout << "========================================\n" << endl;
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 7) {
            // Display Course Schedule by CourseID
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "      COURSE SCHEDULE" << endl;
            cout << "========================================" << endl;
            
            // First show available courses
            StudentRegistrations[vectorNumber].ViewCourses();
            
            string courseID;
            cout << "\nEnter Course ID to view schedule (e.g., CS101): ";
            cin >> courseID;
            
            StudentRegistrations[vectorNumber].displayCourseSchedulByID(courseID);
            
            cout << "========================================\n" << endl;
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 8) {
            // Add a new Complaint
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "      ADD COMPLAINT" << endl;
            cout << "========================================" << endl;
            
            cin.ignore(); // Clear input buffer
            StudentRegistrations[vectorNumber].addStudentComplain();
            
            cout << "\n Complaint submitted successfully!" << endl;
            cout << "Your complaint will be reviewed by the department." << endl;
            
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        else if (opt == 9) {
            // Check Complaint Status
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "      COMPLAINT STATUS" << endl;
            cout << "========================================" << endl;
            
            StudentRegistrations[vectorNumber].ComplaintStatus();
            
            cout << "========================================\n" << endl;
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 10) {
            // View TimeTable (Day-wise)
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "      DAILY TIMETABLE" << endl;
            cout << "========================================" << endl;
            
            int day;
            cout << "Select Day:" << endl;
            cout << "1. Monday" << endl;
            cout << "2. Tuesday" << endl;
            cout << "3. Wednesday" << endl;
            cout << "4. Thursday" << endl;
            cout << "5. Friday" << endl;
            cout << "\nEnter day number (1-5): ";
            cin >> day;
            
            if (day >= 1 && day <= 5) {
                StudentRegistrations[vectorNumber].displayTimetableByDay(day);
            }
            else {
                cout << "\nInvalid day selected!" << endl;
            }
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 11) {
            // View Weekly TimeTable
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "      WEEKLY TIMETABLE" << endl;
            cout << "========================================" << endl;
            
            StudentRegistrations[vectorNumber].displayTimetable();
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 12) {
            // View TimeTable (Tabular Form)
            Clear();
            SetColor(Font, Background);
            cout << "\n========================================" << endl;
            cout << "      TIMETABLE (TABULAR FORM)" << endl;
            cout << "========================================" << endl;
            
            StudentRegistrations[vectorNumber].displayTimetableTable();
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (opt == 13) {
    // Export Weekly Timetable to CSV
    Clear();
    SetColor(Font, Background);
    cout << "\n==========================================" << endl;
    cout << "   EXPORT WEEKLY TIMETABLE TO CSV" << endl;
    cout << "==========================================" << endl;
    StudentRegistrations[vectorNumber].exportTimetableToCSV();
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
    }
    else if (opt == 14) {
    // Export Tabular Timetable to CSV
    Clear();
    SetColor(Font, Background);
    cout << "\n==========================================" << endl;
    cout << "   EXPORT TABULAR TIMETABLE TO CSV" << endl;
    cout << "==========================================" << endl;
    StudentRegistrations[vectorNumber].exportTabularTimetableToCSV();
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
    }
        else if (opt == 15) {
            HomePage();
        }
        else if (opt == 16) {
            // Logout
            cout << "\nLogging out..." << endl;
            return;
        }
        else {
            cout << "\nInvalid option! Please try again." << endl;
            StudentOptionsPage(vectorNumber);
        }
        
    } while (opt != 15);
}

// -----------------------------------------------------------
// HELPER FUNCTIONS FOR STUDENT MODULE
// -----------------------------------------------------------

void displayStudentRegistrationForm() {
    Clear();
    SetColor(Font, Background);
    
    cout << "\n========================================" << endl;
    cout << "      STUDENT REGISTRATION FORM" << endl;
    cout << "========================================" << endl;
    
    Student s1;
    string tempA;
    int tempB;
    
    // Username
    LocationA:
    cout << "Enter Username: ";
    cin >> tempA;
    for (int i = 0; i < StudentRegistrations.size(); i++) {
        if (StudentRegistrations[i].getUsrId() == tempA) {
            cout << "This UserName Already Exists. Try Another UserName." << endl;
            goto LocationA;
        }
    }
    s1.setUserID(tempA);
    
    // Password
    cout << "Enter Password: ";
    cin >> tempA;
    s1.setPassword(tempA);
    
    // Personal Information
    cout << "Enter Your Full Name: ";
    cin.ignore();
    getline(cin, tempA);
    s1.setName(tempA);
    
    cout << "Enter Email: ";
    cin >> tempA;
    s1.setEmail(tempA);
    
    cout << "Enter Gender (Male/Female): ";
    cin >> tempA;
    s1.setGender(tempA);
    
    cout << "Enter Phone Number: ";
    cin >> tempA;
    s1.setPhone(tempA);
    
    // Department Selection
    cout << "\nSelect Your Department:" << endl;
    cout << "------------------------" << endl;
    for (int i = 0; i < Time_Table_Incharge.size(); i++) {
        cout << i + 1 << ". " << Time_Table_Incharge[i].getDepartmentName() << endl;
    }
    
    int deptChoice;
    cout << "\nEnter department number: ";
    cin >> deptChoice;
    
    if (deptChoice < 1 || deptChoice > Time_Table_Incharge.size()) {
        cout << "Invalid department selection!" << endl;
        return;
    }
    
    tempA = Time_Table_Incharge[deptChoice - 1].getDepartmentName();
    s1.setDepartment(tempA);
    
    // Semester
    cout << "Enter Semester (1-8): ";
    cin >> tempB;
    if (tempB < 1 || tempB > 8) {
        cout << "Invalid semester! Must be between 1-8." << endl;
        return;
    }
    s1.setSemester(tempB);
    
    // Registration Number
    cout << "Enter Your Registration Number (e.g., 24-MCT-XX): ";
    cin >> tempA;
    s1.setUniqueID(tempA);
    
    // Registration Date
    tempA = DateTime.getCurrentDate();
    s1.setRegistrationDate(tempA);
    
    // Set approval to pending
    s1.Approval("No");
    
    // Add to registrations
    StudentRegistrations.push_back(s1);
    
    cout << "\n========================================" << endl;
    cout << "REGISTRATION SUCCESSFUL!" << endl;
    cout << "========================================" << endl;
    cout << "\nYour registration has been submitted." << endl;
    cout << "Please wait for department approval." << endl;
    cout << "\nRegistration Details:" << endl;
    cout << "---------------------" << endl;
    cout << "Name: " << s1.getName() << endl;
    cout << "Username: " << s1.getUsrId() << endl;
    cout << "Department: " << s1.getDepartment() << endl;
    cout << "Semester: " << s1.getSemester() << endl;
    cout << "Registration No: " << s1.getUniqueID() << endl;
    cout << "Registration Date: " << s1.getRegistrationDate() << endl;
    cout << "========================================\n" << endl;
    
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void handleStudentLogin() {
    Clear();
    SetColor(Font, Background);
    
    cout << "\n========================================" << endl;
    cout << "        STUDENT LOGIN" << endl;
    cout << "========================================" << endl;
    
    string usrNam, usrpass;
    bool isRegistered = false;
    int studentIndex = -1;
    
    cout << "Enter Username: ";
    cin >> usrNam;
    cout << "Enter Password: ";
    cin >> usrpass;
    
    // Check credentials
    for (int i = 0; i < StudentRegistrations.size(); i++) {
        if (StudentRegistrations[i].authenticate(usrNam, usrpass)) {
            if (StudentRegistrations[i].ApprovalStatus()) {
                isRegistered = true;
                studentIndex = i;
                break;
            }
            else {
                cout << "\n Your account is pending approval." << endl;
                cout << "Please contact your department for approval." << endl;
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
                handleStudentLogin();
            }
        }
    }
    
    if (isRegistered && studentIndex != -1) {
        cout << "\nLogin successful!" << endl;
        StudentOptionsPage(studentIndex);
    }
    else {
        cout << "\nIncorrect Username or Password!" << endl;
        cout << "\nOptions:" << endl;
        cout << "1. Try Again" << endl;
        cout << "2. Register New Account" << endl;
        cout << "3. Back to Home Page" << endl;
        
        int choice;
        cout << "\nEnter choice: ";
        cin >> choice;
        
        if (choice == 1) {
            handleStudentLogin();
        }
        else if (choice == 2) {
            displayStudentRegistrationForm();
            Student_HomePage();
        }
        else if (choice == 3) {
            HomePage();
        }
    }
}
