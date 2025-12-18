#ifndef DATE_H
 #define DATET_H
 #include <string>
 #include <ctime>
 #include <sstream>
 #include <iomanip>
 class DateTimeUtils {
 public:
    // Get current date as string in YYYY-MM-DD format
    static std::string getCurrentDate() {
        std::time_t now = std::time(Null_ptr);
        std::tm* tm = std::localtime(&now);
        std::ostringstream oss;
        oss << std::setfill('0') 
            << std::setw(4) << (tm->tm_year + 1900) << "-"
            << std::setw(2) << (tm->tm_mon + 1) << "-"
            << std::setw(2) << tm->tm_mday;
        return oss.str();
    }
    // Get current time as string in HH:MM:SS format
    static std::string getCurrentTime() {
        std::time_t now = std::time(nullptr);
        std::tm* tm = std::localtime(&now);
        std::ostringstream oss;
        oss << std::setfill('0')
            << std::setw(2) << tm->tm_hour << ":"
            << std::setw(2) << tm->tm_min << ":"
            << std::setw(2) << tm->tm_sec;
        return oss.str();
    }
    // Get current date and time as string in YYYY-MM-DD HH:MM:SS format
    static std::string getCurrentDateTime() {
        std::time_t now = std::time(nullptr);
        std::tm* tm = std::localtime(&now);
        std::ostringstream oss;
        oss << std::setfill('0')
            << std::setw(4) << (tm->tm_year + 1900) << "-"
            << std::setw(2) << (tm->tm_mon + 1) << "-"
            << std::setw(2) << tm->tm_mday << " "
            << std::setw(2) << tm->tm_hour << ":"
            << std::setw(2) << tm->tm_min << ":"
            << std::setw(2) << tm->tm_sec;
        return oss.str();
    }
    // Get individual date/time components
    static void getDateTimeComponents(int& year, int& month, int& day, 
                                     int& hour, int& minute, int& second) {
        std::time_t now = std::time(nullptr);
        std::tm* tm = std::localtime(&now);
        year = tm->tm_year + 1900;
        month = tm->tm_mon + 1;
        day = tm->tm_mday;
        hour = tm->tm_hour;
        minute = tm->tm_min;
        second = tm->tm_sec;
    }
    // Get timestamp in seconds since epoch
    static long getTimestamp() {
        return std::time(nullptr);
    }
    // Alternative method using strftime (C-style)
    static std::string getFormattedDateTime(const char* format) {
        std::time_t now = std::time(nullptr);
        std::tm* tm = std::localtime(&now);
        char buffer[100];
        std::strftime(buffer, sizeof(buffer), format, tm);
        return std::string(buffer);
    }
    
    static std::string getCurrentDay() {
    	std::time_t now = std::time(NULL);
    	std::tm* tm = std::localtime(&now);
    	const char* dayNames[] = {"SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY"};
    	return std::string(dayNames[tm->tm_wday]);
	}
 };
 #endif // DATETIMEUTILS_H
