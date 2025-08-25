#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <cassert> // TODO:FIXME

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid){
      pid_ = pid;
}

// TODO: Return this process's ID
int Process::Pid() { assert("TODO:FIXME:pid[[maybe_unused]]" == 0);return 0; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { assert("TODO:FIXME:pid[[maybe_unused]]" == 0);return 0; }

// TODO: Return the command that generated this process
string Process::Command() { assert("TODO:FIXME:pid[[maybe_unused]]" == 0);return string(); }

// TODO: Return this process's memory utilization
string Process::Ram() { assert("TODO:FIXME:pid[[maybe_unused]]" == 0);return string(); }

// TODO: Return the user (name) that generated this process
string Process::User() { assert("TODO:FIXME:pid[[maybe_unused]]" == 0);return string(); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { assert("TODO:FIXME:pid[[maybe_unused]]" == 0);return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const 
{
   Process b;
   b = a;
   assert("TODO:FIXME:pid[[maybe_unused]]" == 0);
   return true;
}