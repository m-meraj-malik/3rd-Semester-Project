#include<iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<map>
#include<utility> //pair
#include<algorithm>
#include "Design_Lab.h"
#include "Date_h.h"
#include "Faculty.h"
#include "User.h"
using namespace std;

// -----------------------------------------------------------
// GLOBAL CONSTANTS AND VARIABLES
// -----------------------------------------------------------

// Time table configuration constants
int maxLecturesPerDay = 8;    // Maximum number of lectures that can be scheduled per day
int numberOfDays = 5;         // Number of working days in the week (Monday to Friday)

// Global vectors for data storage
vector<Faculty> FacultyRegistrations;  // Stores all faculty members who have registered but not yet approved
vector<Course> AllCourses;             // Stores all courses available in the university system

// Time unit mapping: Maps lecture slot numbers to their start and end times
// Each entry: {slot_number, {start_time, end_time}}
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

// Days of the week mapping: Maps day numbers to their names
// Used for displaying and scheduling classes
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
// Array of color names for console output
const string Colour[9] = {"Black", "Blue", "Green", "Cyan", "Red", "Purple", "Yellow", "White", "Gray"};
int Font = 6;          // Default font color (Yellow)
int Background = 0;    // Default background color (Black)

// -----------------------------------------------------------
// ADMIN LOGIN CREDENTIALS
// -----------------------------------------------------------
// Structure to store admin login credentials
struct Admin_Login_Credentials {
    string Admin_UserName;  // Admin username
    int Admin_Password;     // Admin password (stored as integer for simplicity)
};

// Initialize default admin credentials
Admin_Login_Credentials Admin1 = {"Admin123", 456};

// -----------------------------------------------------------
// USER CLASS IMPLEMENTATION
// -----------------------------------------------------------

// Parameterized constructor for User class
// Initializes all user attributes with provided values
User::User(string& userID, string& password, string& name, string& email, string& gender, 
          string& phone, string& department, string userType, string& regDte) : 
    userID(userID), password(password), name(name), email(email), gender(gender), 
    phone(phone), department(department), userType(userType), registrationDate(regDte) { }

// Default constructor
User::User() { }

// Display user profile information
void User::displayProfile() const {
    cout << "Name: " << name << endl;
    cout << "Gender: " << gender << endl;
    cout << "Email: " << email << endl;
    cout << "Phone: " << phone << endl;
    cout << "Department: " << department << endl;
    cout << "User Type: " << userType
         << "\nApproval Status: " << (isApproved ? "Approved\n" : "Pending\n")
         << "Registration Date: " << registrationDate << endl;
}

// Setter for password
void User::setPassword(const string& pass) { password = pass; }

// Setter for user ID
void User::setUserID(const string& usrID) { userID = usrID; }

// Setter for name
void User::setName(const string& nam) { name = nam; }

// Setter for gender
void User::setGender(const string& gen) { gender = gen; }

// Setter for email
void User::setEmail(const string& em) { email = em; }

// Setter for phone number
void User::setPhone(const string& ph ) { phone = ph; }

// Setter for department
void User::setDepartment(const string& dep) { department = dep; }

// Setter for unique ID (usually roll number for students, employee ID for faculty)
void User::setUniqueID(const string& UniID) { uniqueID = UniID; }

// Set approval status based on input string
// Accepts various forms of "yes" (case-insensitive)
void User::Approval(const string status) {
    // Check if status indicates approval (case-insensitive)
    if(status == "YES" || status == "Yes" || status == "yes" || 
       status == "yEs" || status == "YeS" || status == "yES" || 
       status == "YEs" || status == "yeS") {
        isApproved = true;
    }
    else {
        isApproved = false;
    }
}

// Getter for name
string User::getName() const { return name; }

// Getter for gender
string User::getGender() const { return gender; }

// Getter for email
string User::getEmail() const { return email; }

// Getter for phone number
string User::getPhone() const { return phone; }

// Getter for department
string User::getDepartment() const { return department; }

// Check if user is approved
bool User::ApprovalStatus() const { return isApproved; }

// Getter for user type (Faculty, Student, etc.)
string User::getUserType() const { return userType; }

// Getter for unique ID
string User::getUniqueID() const { return uniqueID; }

// Getter for registration date
string User::getRegistrationDate() const { return registrationDate; }

// Authenticate user by comparing input credentials with stored credentials
bool User::authenticate(const string& inputUserName, const string& inputPassword) {
    return (userID == inputUserName && password == inputPassword);
}

// Change user password after verifying old password
bool User::ChangePassword(string& oldPass, string& newPass) {
    if(oldPass == password) {
        password = newPass;
        return true;  // Password changed successfully
    }
    else {
        return false; // Old password doesn't match
    }
}

// -----------------------------------------------------------
// FACULTY CLASS IMPLEMENTATION
// -----------------------------------------------------------

// Parameterized constructor for Faculty class
// Inherits from User class and adds designation
Faculty::Faculty(string& ID, string& pass, string& nam, string& em, string& gen, 
                string& ph, string& dept, string& regDte, string& desig) : 
    User(ID, pass, nam, em, gen, ph, dept, "Faculty", regDte), designation(desig) { }

// Default constructor
Faculty::Faculty() { }

// Getter for designation (Professor, Assistant Professor, etc.)
string Faculty::getDesignation() const { return designation; }

// Setter for designation
void Faculty::setDesignation(const string& desig) { designation = desig; }

// Set weekly availability for classes
// Allows faculty to mark which time slots they are available each day
void Faculty::setWeeklyAvailability() {
    int choice;
    bool s = 0;
    
    cout << "Set Your Weekly Availability: " << endl;
    
    // Display day options
    for(int i = 1; i <= numberOfDays; i++) {
        cout << i << ". Set Availability Hours For " << DAYS[i] << ": \n";
    }
    
    cout << "0. Exit\nEnter Your Choice: ";
    cin >> choice;
    
    // Process availability for selected day
    if(choice >= 1 && choice <= 5) {
        cout << "Set Your Availability on " << DAYS[choice] << endl;
        cout << "Enter 0 for Unavailable and 1 for Available" << endl;
        
        // Get availability for each time slot
        for(int i = 1; i <= maxLecturesPerDay; i++) {
            cout << i << ". From " << UNIT[i].Start_Time << " to " 
                 << UNIT[i].End_Time << " : ";
            cin >> s;
            
            // Store availability in the faculty's schedule
            AVAILABLE[choice - 1].push_back({{UNIT[i].Start_Time, UNIT[i].End_Time}, s});
        }
    }
    else {
        return; // Exit if invalid choice
    }
}

// Get weekly availability (currently returns availability for Sunday only)
// TODO: This should be modified to return complete weekly availability
vector<Faculty_Available> Faculty::getWeeklyAvailability() {
    return AVAILABLE[6];  // Index 6 corresponds to Sunday
}

// Display availability for a specific day
void Faculty::displayAvailabilityByDay(const int& day) {
    if(day > 0 && day <= 6) {
        cout << "Availability of " << getName() << " on " << DAYS[day] << endl;
    }
    else { 
        cout << "Invalid Day" << endl; 
        return; 
    }
    
    // Display availability for each time slot
    for(int i = 1; i <= maxLecturesPerDay; i++) {
        cout << i << ". From " << AVAILABLE[day - 1][i].t.Start_Time << " to " 
             << AVAILABLE[day - 1][i].t.End_Time << " : " 
             << (AVAILABLE[day - 1][0].isAvailable ? "Available" : "Not Available") << endl;
    }
}

// Add a qualification to faculty's profile
void Faculty::setQualifications(string qual) {
    qualifications.push_back(qual);
}

// Remove a specific qualification
void Faculty::removeQualifications(string qual) {
    // Search for qualification and remove it
    for(int i = 0; i < qualifications.size(); i++) {
        if(qualifications[i] == qual) {
            qualifications.erase(qualifications.begin() + i);
            return;  // Exit after removing first occurrence
        }
    }
}

// Get all qualifications
vector<string> Faculty::getQualifications() {
    return qualifications;
}

// Display all qualifications
void Faculty::displayQualifications() {
    cout << "Qualifications: " << endl;
    
    if(qualifications.empty()) {
        cout << "No Qualifications Added" << endl;
        return;
    }
    
    // Display each qualification with numbering
    for(int i = 0; i < qualifications.size(); i++) {
        cout << i + 1 << ". " << qualifications[i] << endl;
    }
}

// Add a specialized course
void Faculty::setSpecializedCourses(string C) {
    specializedCourses.push_back(C);
}

// Remove a specialized course
void Faculty::removeSpecializedCourses(string C) {
    for(int i = 0; i < specializedCourses.size(); i++) {
        if(specializedCourses[i] == C) {
            specializedCourses.erase(specializedCourses.begin() + i);
            return;  // Exit after removing first occurrence
        }
    }
}

// Get all specialized courses
vector<string> Faculty::getSpecializedCourses() {
    return specializedCourses;
}

// Add an assigned course (called by department when assigning courses)
void Faculty::addAssignedCourses(Course& COUR) {
    assignedCourses.push_back(COUR);
}

// Check if a specific course is assigned to this faculty
bool Faculty::checkAssignedCourse(string Course_name) {
    for(int i = 0; i < assignedCourses.size(); i++) {
        if(assignedCourses[i].courseName == Course_name) {
            return true;  // Course is assigned
        }
    }
    return false;  // Course is not assigned
}

// Get all assigned courses
vector<Course> Faculty::getAssignedCourses() {
    return assignedCourses;
}

// Display all assigned courses
// TODO: This function has a logic error - the condition is reversed
void Faculty::displayAssignedCourses() {
    if(assignedCourses.empty()) {  // Should be if(!assignedCourses.empty())
        cout << "Sr. No \t Course Name \t\t Course Code" << endl;
        for(int i = 0; i < assignedCourses.size(); i++) {
            cout << i + 1 << ". " << assignedCourses[i].courseName 
                 << "  " << assignedCourses[i].courseID << endl;
        }
    }
    else {
        cout << "No Course Assigned" << endl;
    }
}

// Calculate total teaching hours
// Labs count as 3 hours per credit hour, theory as 1 hour per credit hour
int Faculty::getCurrentTeachingHours() {
    int total = 0;
    for(int i = 0; i < assignedCourses.size(); i++) {
        if(assignedCourses[i].CourseType == "Lab") {
            total += ((assignedCourses[i].credit_hours) * 3);
        }
        if(assignedCourses[i].CourseType == "Theory") {
            total += (assignedCourses[i].credit_hours);
        }
    }
    return total;
}

// -----------------------------------------------------------
// MAIN FUNCTION
// -----------------------------------------------------------
int main() {
    int option;

    // Application Title Banner
    cout << "\t\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
         << "\t\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
         << "\t\t\t:::                                                       :::\n"
         << "\t\t\t:::     WELCOME TO TIME TABLE MANAGEMENT APPLICATION      :::\n"
         << "\t\t\t:::                                                       :::\n"
         << "\t\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
         << "\t\t\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n" << endl;
    
    // Display project team members
    cout << "-------------------------" << endl;
    cout << "-\tPrepared By: \t-\n\n"
         << "-\t24-MCT-06\t-\n"
         << "-\t24-MCT-08\t-\n"
         << "-\t24-MCT-13\t-\n"
         << "-\t24-MCT-16\t-\n"
         << "-\t24-MCT-50\t-\n" << endl;
    cout << "-------------------------" << endl;
    
    // User choice to continue or exit
    cout << "\n\n -----------------------------------\n"
         << "| Enter 1 to continue and 0 to exit |\n"
         << " -----------------------------------" << endl;

    cin >> option;

    if(option == 1)
        HomePage();    // Start the application
    else
        return 0;      // Exit the application
}

// -----------------------------------------------------------
// MAIN HOME PAGE SCREEN
// -----------------------------------------------------------
void HomePage() {
Loop1:
    Clear();  // Clear console screen
    int option = 3;
    SetColor(Font, Background);  // Set console colors

    // Display main application title
    cout << "\t\t\t -------------------------------------------------------------- \n"
         << "\t\t\t|                                                              |\n"
         << "\t\t\t|               University Time Table Management               |\n"
         << "\t\t\t|                                                              |\n"
         << "\t\t\t -------------------------------------------------------------- " << endl;

    // Display menu options
    cout << "1. Admin Mode\n"
         << "2. Faculty Mode\n"
         << "3. Student Mode\n"
         << "4. Settings\n"
         << "Select your option: ";

    cin >> option;

    // Handle user selection
    if(option == 1) {
        Admin_HomePage();  // Go to admin section
    }
    else if(option == 2) {
        // Faculty mode - TODO: Implement Faculty_HomePage()
        // Currently empty - need to add faculty login/registration functionality
    }
    else if(option == 3) {
        // Student mode - TODO: Implement Student_HomePage()
        // Currently empty - need to add student login/registration functionality
    }
    else if(option == 4) {
        ChangeTheme();  // Go to settings to change colors
    }
    else {
        cout << "Not Valid Command!" << endl;
        goto Loop1;  // Invalid input, redisplay menu
    }
}

// -----------------------------------------------------------
// CHANGE APPLICATION THEME (Font + Background Colors)
// -----------------------------------------------------------
void ChangeTheme() {
    Clear();
    int opt;
    int font_color, background_color;

    // Display theme change header
    cout << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_"
         << "|             Change Theme            |"
         << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << endl << endl;

    // Display color options
    cout << "Select Your Desired Color For Font and Background: " << endl;
    cout << "Black = 0\nBlue = 1\nGreen = 2\nCyan = 3\nRed = 4\nPurple = 5\nYellow = 6\nWhite = 7\nGray = 8" << endl;

    // Get font color choice
    cout << "Enter Color Number for Font (Enter 9 for default): ";
    cin >> font_color;

    // Get background color choice
    cout << "Enter Color Number for Background (Enter 9 for default): ";
    cin >> background_color;

    // FONT COLOR PROCESSING
    if(font_color >= 0 && font_color <= 8) {
        Font = font_color;  // Set to selected color
    }
    else if(font_color == 9) {
        Font = 6;  // Default (Yellow)
        cout << "Updated to Default" << endl;
    }
    else {
        cout << "Invalid Font Color! Using Default." << endl;
    }

    // BACKGROUND COLOR PROCESSING
    if(background_color >= 0 && background_color <= 8) {
        Background = background_color;  // Set to selected color
    }
    else if(background_color == 9) {
        Background = 0;  // Default (Black)
        cout << "Updated to Default" << endl;
    }
    else {
        cout << "Invalid Background Color! Using Default." << endl;
    }

    // Display update confirmation
    cout << Colour[font_color] << " is Updated as your Font Color" << endl;
    cout << Colour[background_color] << " is Updated as your Background Color" << endl;

    // Navigation options
    cout << "Enter 1 to Go to HomePage and 0 to exit" << endl;
    cin >> opt;

    if(opt == 1)
        HomePage();  // Return to home page
    else
        return;      // Exit
}

// -----------------------------------------------------------
// ADMIN MENU SCREEN
// -----------------------------------------------------------
void Admin_HomePage() {
    Clear();
    SetColor(Font, Background);

    int option;

    // Display admin homepage header
    cout << "\t\t\t ------------------------------------------------------\n"
         << "\t\t\t|                                                      |\n"
         << "\t\t\t|                    Admin HomePage                    |\n"
         << "\t\t\t|                                                      |\n"
         << "\t\t\t ------------------------------------------------------\n" << endl;

    // Admin menu options
    cout << "1. Login\n"
         << "2. Go Back to Home Page\n"
         << "3. Exit\n"
         << "Select your option: ";

    cin >> option;

    // Handle admin menu selection
    if(option == 1) {
        Admin_Login();  // Go to admin login
    }
    else if(option == 2) {
        HomePage();     // Return to main homepage
    }
    else if(option == 3) {
        return;         // Exit application
    }
    else {
        cout << "Invalid Command!" << endl;
        Admin_HomePage();  // Invalid input, redisplay admin menu
    }
}

// -----------------------------------------------------------
// ADMIN LOGIN SCREEN
// -----------------------------------------------------------
void Admin_Login() {
    Clear();
    SetColor(Font, Background);

    string username;
    int password, option;

    // Display login prompt
    cout << "Login" << endl;
    cout << "Enter UserName: ";
    cin >> username;

    cout << "Enter Password: ";
    cin >> password;

    // Check admin credentials
    if(username == Admin1.Admin_UserName && password == Admin1.Admin_Password) {
        // Successful login
        Admin_After_Login();  // Go to admin dashboard
    }
    else {
        // Failed login
        cout << "Incorrect UserName or Password" << endl;

        // Display error recovery options
        cout << "1. Try Again\n"
             << "2. Admin Home Page\n"
             << "3. Main Home Page\n"
             << "4. Exit\n";

        cout << "Select your option: ";
        cin >> option;

        // Handle error recovery selection
        if(option == 1)
            Admin_Login();     // Retry login
        else if(option == 2)
            Admin_HomePage();  // Go back to admin homepage
        else if(option == 3)
            HomePage();        // Return to main homepage
        else if(option == 4)
            return;            // Exit application
        else {
            cout << "Invalid Command!" << endl;
            Admin_Login();     // Invalid input, retry login
        }
    }
}

// -----------------------------------------------------------
// ADMIN DASHBOARD (After Login)
// -----------------------------------------------------------
void Admin_After_Login() {
    Clear();
    SetColor(Font, Background);
    int option, option3;
    
    // Display welcome message
    cout << "Welcome Dear Admin!" << endl;
    
    // Admin dashboard options
    cout << "1. Add New Department\n"
         << "2. Remove Existing Department\n"
         << "3. Schedule Setting\n"
         << "4. Lecture Schedule\n"
         << "5. Admin Account Setting\n"
         << "6. Back\n"
         << "7. Admin Home Page\n"
         << "8. Main Home Page\n"
         << "9. Exit" << endl;
    
    cin >> option;

    // Handle admin dashboard selections
    if(option == 1) {
        // Add New Department - TODO: Implement this functionality
        // Should create a new department object and add to Time_Table_Incharge vector
    }
    else if(option == 2) {
        // Remove Existing Department - TODO: Implement this functionality
        // Should display departments and allow admin to remove one
    }
    else if(option == 3) {
        // Schedule Setting: Modify daily schedule configuration
        int Temp;
        cout << "Modify Daily Schedule" << endl;
        
        // Set maximum lectures per day
        cout << "Set Maximum Lectures Per Day: ";
        cin >> Temp;
        maxLecturesPerDay = Temp;
        
        // Set number of working days
        cout << "Set Number of Days: ";
        cin >> Temp;
        numberOfDays = Temp;
        
        Admin_After_Login();  // Return to admin dashboard
    }
    else if(option == 4) {
        // Lecture Schedule: Define time slots for each lecture period
        cout << "Set Daily Schedule of Lectures " << endl;
        UNIT.clear();  // Clear existing time slots
        
        // Get time slots for each lecture period
        for(int i = 1; i <= maxLecturesPerDay; i++) {
            cout << "For Lecture#" << i << endl;
            cout << "Enter Start Time: ";
            cin >> UNIT[i].Start_Time;
            cout << "Enter End Time: ";
            cin >> UNIT[i].End_Time;
            cout << endl;
        }
        
        Admin_After_Login();  // Return to admin dashboard
    }
    else if(option == 5) {
        // Admin Account Setting: Change admin credentials
        Clear();
        SetColor(4, 0);  // Change to red font on black background
        
        int option1, existingPassword, newPassword;
        string existingUserName, newUserName;
        
        cout << "Account Setting" << endl;
        cout << "1. Change UserName\n"
             << "2. Change Password\n"
             << "3. Change UserName and Password\n";
        cout << "Select your option" << endl;
        
        cin >> option1;

        if(option1 == 1) {
            // Change username only
            cout << "Enter Your Existing UserName: ";
            cin >> existingUserName;
            
            if(existingUserName == Admin1.Admin_UserName) {
                cout << "Enter New UserName: ";
                cin >> newUserName;
                Admin1.Admin_UserName = newUserName;
                cout << "UserName Changed Successfully" << endl;
                Admin_After_Login();
            }
            else {
                cout << "Existing User Name is Incorrect." << endl;
                Admin_After_Login();
            }
        }
        else if(option1 == 2) {
            // Change password only
            cout << "Enter Your Existing Password: ";
            cin >> existingPassword;
            
            if(existingPassword == Admin1.Admin_Password) {
                cout << "Enter New Password: ";
                cin >> newPassword;
                Admin1.Admin_Password = newPassword;
                cout << "Password Changed Successfully" << endl;
                Admin_After_Login();
            }
            else {
                cout << "Existing Password is Incorrect." << endl;
                Admin_After_Login();
            }
        }
        else if(option1 == 3) {
            // Change both username and password
            cout << "Enter Your Existing UserName: ";
            cin >> existingUserName;
            cout << "Enter Your Existing Password: ";
            cin >> existingPassword;
            
            if(existingUserName == Admin1.Admin_UserName && existingPassword == Admin1.Admin_Password) {
                cout << "Enter New UserName: ";
                cin >> newUserName;
                Admin1.Admin_UserName = newUserName;
                
                cout << "Enter New Password: ";
                cin >> newPassword;
                Admin1.Admin_Password = newPassword;
                
                cout << "UserName & Password Changed Successfully" << endl;
                Admin_After_Login();
            }
            else {
                cout << "Existing User Name or Password is Incorrect." << endl;
                Admin_After_Login();
            }
        }
        else {
            cout << "Not Valid Option Selected...." << endl;
            Admin_After_Login();
        }
    }
    else if(option == 6) {
        Admin_Login();  // Go back to login screen
    }
    else if(option == 7) {
        Admin_HomePage();  // Go back to admin homepage
    }
    else if(option == 8) {
        HomePage();  // Go back to main homepage
    }
    else if(option == 9) {
        return;  // Exit application
    }
    else {
        cout << "No Valid Option Selected..." << endl;
        Admin_After_Login();  // Invalid input, redisplay admin dashboard
    }
}