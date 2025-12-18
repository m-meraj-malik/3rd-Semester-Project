// -----------------------------------------------------------
// USER.H
// Header file for User class
// -----------------------------------------------------------

#ifndef USER_H          // Header guard to prevent multiple inclusions
#define USER_H

#include<string>        // Required for using string data type
using namespace std;

// -----------------------------------------------------------
// USER CLASS DECLARATION
// This class represents a generic user in the system
// (Admin, Faculty, Student can inherit or use this class)
// -----------------------------------------------------------
class User {

protected:
    // -------------------------
    // USER ATTRIBUTES
    // -------------------------

    string userID;              // Username / login ID of the user
    string password;            // Password for authentication
    string uniqueID = "---";    // Unique identifier (Roll No / Employee ID)
    string name;                // Full name of the user
    string email;               // Email address
    string gender;              // Gender of the user
    string phone;               // Contact phone number
    string department;          // Department name
    string userType;            // Type of user (Admin / Faculty / Student)
    bool isApproved = false;    // Approval status (true = approved, false = pending)
    string registrationDate;    // Date when user registered

public:
    // -------------------------------------------------------
    // CONSTRUCTORS
    // -------------------------------------------------------

    // Parameterized constructor
    // Initializes all user attributes at the time of object creation
    User(string& userID, string& password, string& name, string& email,
         string& gender, string& phone, string& department,
         string userType, string& regDte);

    // Default constructor
    // Allows creation of empty user object
    User();

    // -------------------------------------------------------
    // DISPLAY FUNCTION
    // -------------------------------------------------------

    // Displays complete profile information of the user
    void displayProfile() const;

    // -------------------------------------------------------
    // SETTER FUNCTIONS
    // Used to update user information
    // -------------------------------------------------------

    void setPassword(const string& pass);      // Set or update password
    void setUserID(const string& usrID);       // Set user login ID
    void setName(const string& nam);            // Set user's name
    void setGender(const string& gen);          // Set gender
    void setEmail(const string& em);            // Set email address
    void setPhone(const string& ph );           // Set phone number
    void setDepartment(const string& dep);      // Set department
    void setUniqueID(const string& UniID);      // Set unique ID (Roll/Employee No)

    // Sets approval status based on input string (YES / NO)
    void Approval(const string status);

    // -------------------------------------------------------
    // GETTER FUNCTIONS
    // Used to retrieve user information
    // -------------------------------------------------------

    string getName() const;             // Get user's name
    string getGender() const;           // Get gender
    string getEmail() const;            // Get email
    string getPhone() const;            // Get phone number
    string getDepartment() const;       // Get department
    bool ApprovalStatus() const;        // Check approval status
    string getUserType() const;         // Get user type
    string getUniqueID() const;         // Get unique ID
    string getRegistrationDate() const; // Get registration date

    // -------------------------------------------------------
    // AUTHENTICATION & SECURITY FUNCTIONS
    // -------------------------------------------------------

    // Authenticates user by comparing input credentials
    bool authenticate(const string& inputUserName,
                      const string& inputPassword);

    // Changes password after verifying old password
    bool ChangePassword(string& oldPass, string& newPass);
};

#endif   // End of USER_H
