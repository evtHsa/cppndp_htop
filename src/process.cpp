#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;
#include <iostream> // FIXME: get rid of this when not using cout for debug
Process::Process(int pid){
      pid_ = pid;
}

// Return this process's ID
int Process::Pid() {
      return pid_; 
}

// Return this process's CPU utilization
float Process::CpuUtilization() {
      std::vector<std::string> v;
      std::string fname = std::to_string(pid_) + LinuxParser::kStatFilename;
      unsigned long u_time, s_time, cu_time, cs_time, total_time;
      float ret;
      long pid_uptime = LinuxParser::UpTime(pid_);

      LinuxParser::GetKeyedValues(LinuxParser::kProcDirectory, fname, v, ""); // empty key because 1 line file
      // for proc/pid/stat field definitions: https://manpages.ubuntu.com/manpages/noble/man5/proc_pid_stat.5.html
      u_time = std::stol(v[13]);  // user time for this process
      s_time = std::stol(v[14]);  // system time for this process
      cu_time = std::stol(v[15]); // user time for children of this process
      cs_time = std::stol(v[16]); // system time for children of this process
      total_time = u_time + s_time + cu_time + cs_time;
      total_time /= sysconf(_SC_CLK_TCK); // convert to seconds to match units of LinuxParser::UpTime()

      if (total_time == 0) return 0.0f;

      // calc per https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat
      ret = ((float)total_time) / pid_uptime;
      return ret; 
}

// Return the command that generated this process
string Process::Command() {
      std::vector<std::string> v;
      std::string fname = std::to_string(pid_) + LinuxParser::kCmdlineFilename;
      LinuxParser::GetKeyedValues(LinuxParser::kProcDirectory, fname, v, "");
      return string(v[0]);
}

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