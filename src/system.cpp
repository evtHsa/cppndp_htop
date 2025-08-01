#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <cassert> // TODO:FIXME
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
/*You need to complete the mentioned TODOs in order to satisfy the rubric criteria "The student will be able to extract and display basic data about the system."

You need to properly format the uptime. Refer to the comments mentioned in format. cpp for formatting the uptime.*/

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { assert("TODO:FIXME:pid[[maybe_unused]]" == 0);return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return string(LinuxParser::OperatingSystem()); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    float ret = LinuxParser::MemoryUtilization();
    return ret; 
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { return string(LinuxParser::OperatingSystem()); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { assert("TODO:FIXME:pid[[maybe_unused]]" == 0);return 0; }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() {
    return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { assert("TODO:FIXME:pid[[maybe_unused]]" == 0);return 0; }
