#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <cassert> // TODO:FIXME: remove this
#include <sstream>
#include <iostream>
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

void LinuxParser::GetKeyedValues(string fname, vector<string> &ret, std::string ikey, 
                                 unsigned int max_values) 
{
  std::string line, val;
  std::ifstream ifstrm(kProcDirectory+fname);

   if (!ifstrm.is_open())
    return;

   while (getline(ifstrm, line)) {
    std::istringstream strstrm(line);
    std::string key;

    while (strstrm >> key) {
      if (ikey == key){
        while (strstrm >> val) {
            ret.push_back(val);
            if (ret.size() == max_values) break;
        }
      }
    }
  }
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  std::vector<std::string> v;
  float total, free;

  GetKeyedValues(kMeminfoFilename, v, "MemTotal:", 1);
  total = std::stof(v.front());
  v.clear();

  GetKeyedValues(kMeminfoFilename, v, "MemFree:", 1);
  free = std::stof(v.front());
  return (total - free) / total; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { assert("TODO:FIXME:pid[[maybe_unused]]" == 0);return 0; }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  // TODO:FIXME:071625
  vector<string> values = LinuxParser::CpuUtilization();
  vector<long> valueslong(10, 0);
  long total = 0;
  vector<CPUStates> all = {kUser_, kNice_, kSystem_, kIdle_, kIOwait_, kIRQ_, kSoftIRQ_, kSteal_};
  for (int i : all) { // All non-guest values
    valueslong[i] = stol(values[i]);
    total += valueslong[i];
  };
  return total;
   assert("TODO:FIXME:pid[[maybe_unused]]" == 0);
   return 0; 
}

// TODO: Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) {
  pid++;
  return 0; 
  }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  vector<std::string> jiffies = CpuUtilization();
  long total = 0;
  for (int i = kState_min_  ; i <= kState_max_;i ++)
    total += std::stol(jiffies[i]);
  return total; 
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { assert("TODO:FIXME:pid[[maybe_unused]]" == 0);return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string line, token, key;
  vector<string> tokens;
  std::ifstream stream(kProcDirectory + kStatFilename);

  if (!stream.is_open()) {
    std::cerr << "could not open" << kProcDirectory << kStatFilename;
    return tokens;
  }

  // get one line. if it's "cpu" line, tokenize it
  std::getline(stream, line);
  std::istringstream linestream(line);
  linestream >> key;
  if (key != "cpu")  {
    std::cerr << "invalid line from" << kProcDirectory << kStatFilename;
    return tokens;
  }

  while (linestream >> token)
      tokens.push_back(token);
  
  return tokens;
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  std::vector<std::string> v;
  GetKeyedValues(kStatFilename, v, "processes", 1);
  return std::stoi(v.front()); 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { assert("TODO:FIXME:pid[[maybe_unused]]" == 0);return 0; }

// TODO: Read and return the command associated with a process
string LinuxParser::Command(int pid) {
   pid ++;
   assert("TODO:FIXME:pid[[maybe_unused]]" == 0);
   return string();
}

// TODO: Read and return the memory used by a process
string LinuxParser::Ram(int pid) {
   pid ++;
   assert("TODO:FIXME:pid[[maybe_unused]]" == 0);
   return string();
}

// TODO: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
   pid ++;
   assert("TODO:FIXME:pid[[maybe_unused]]" == 0);
   return string();
}

// TODO: Read and return the user associated with a process
string LinuxParser::User(int pid) {
   pid ++;
   assert("TODO:FIXME:pid[[maybe_unused]]" == 0);
   return string();
}

// TODO: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) {
   pid ++;
   assert("TODO:FIXME:pid[[maybe_unused]]" == 0);
   return pid;
}
