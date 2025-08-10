#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <cassert> // TODO:FIXME

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid){
      pid_ = pid;
}

// TODO: Return this process's ID
int Process::Pid() {
      return pid_; 
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
      long pid_uptime = LinuxParser::UpTime(pid_);

// TODO: Return the command that generated this process
string Process::Command() { assert("TODO:FIXME:pid[[maybe_unused]]" == 0);return string(); }

// Return this process's memory utilization
string Process::Ram() {
      std::vector<std::string> v;
      std::string fname = std::to_string(pid_) + LinuxParser::kStatusFilename;
      LinuxParser::GetKeyedValues(LinuxParser::kProcDirectory, fname, v, "VmRSS:");
      return string(v[1]); 
}

// Return the user (name) that generated this process
string Process::User() {
      return LinuxParser::User(pid_);
}

// Return the age of this process (in seconds)
long int Process::UpTime() {
       return LinuxParser::UpTime(pid_);
}

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const 
{
   return a.pid_ < this->pid_;
}