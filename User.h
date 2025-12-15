#ifndef USER_H
#define USER_H

#include<string>
using namespace std;

class User{
	protected:
		string userID;
		string password;
		string uniqueID = "---";
		string name;
		string email;
		string gender;
		string phone;
		string department;
		string userType;
		bool isApproved = false;
		string registrationDate;
	public:
		User(string& userID, string& password, string& name, string& email, string& gender, string& phone, string& department, string userType, string& regDte);
		User();

		virtual ~User() = default;
		void displayProfile() const;

		void setPassword(const string& pass);
		void setUserID(const string& usrID);
		void setName(const string& nam);
		void setGender(const string& gen);
		void setEmail(const string& em);
		void setPhone(const string& ph );
		void setDepartment(const string& dep);
        void setUniqueID(const string& UniID);
		void Approval(const string status);

		string getName() const;
		string getGender() const;
		string getEmail() const;
		string getPhone() const;
		string getDepartment() const;
		bool ApprovalStatus() const;
		string getUserType() const;
		string getUniqueID() const;
		string getRegistrationDate() const;

		bool authenticate(const string& inputUserName, const string& inputPassword);

		bool ChangePassword(string& oldPass, string& newPass);
};

#endif
