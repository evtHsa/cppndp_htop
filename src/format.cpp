#include <string>
#include <sstream>
#include <iomanip> // for setw, setfill
#include "format.h"

using std::string;

// Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int days, hrs, mins, secs;
    std::ostringstream oss;

    string ret;
    days = seconds / (3600 * 24);
    seconds -= days * 3600 * 24;
    hrs = seconds / 3600;
    seconds -= hrs * 3600;
    mins = seconds / 60;
    secs = seconds - mins * 60;
    oss << std::setw(3) << days << " days, "
      << std::setw(2) << std::setfill('0') << hrs << ":"
    << std::setw(2) << std::setfill('0') << mins << ":"
    << std::setw(2) << std::setfill('0') << secs;
    ret = oss.str();
    return ret; 
}