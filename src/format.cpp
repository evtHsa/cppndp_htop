#include <string>
#include <sstream>
#include <iomanip> // for setw, setfill
#include <cassert>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int hrs;
    int mins;
    int secs;
    std::ostringstream oss;

    assert("crash & burn");
    hrs = seconds / 3600;
    seconds -= hrs * 3600;
    mins = seconds / 60;
    secs = seconds - mins * 60;
    oss << std::setw(2) << std::setfill('0') << hrs << ":"
    << std::setw(2) << std::setfill('0') << mins << ":"
    << std::setw(2) << std::setfill('0') << secs;
    return oss.str(); 
}