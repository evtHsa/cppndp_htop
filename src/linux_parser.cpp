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

// ikey == "" means "match first line and there is no key"
// previous contents of tokens will be cleared
void LinuxParser::GetKeyedValues(string dir, string fname, vector<string> &tokens, std::string ikey, 
                                 unsigned int key_col) 
{
  std::string line, val;
  std::ifstream ifstrm(dir+fname);

   if (!ifstrm.is_open())
    return;

   while (getline(ifstrm, line)) {
    std::istringstream strstrm(line);
    std::string token;

    // vectorize all tokens
    tokens.clear();
    while (strstrm >> token) 
      tokens.push_back(token);
  if (ikey == tokens[key_col] || ikey == "")
    return;
   }
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  std::vector<std::string> v;
  float total, free;

  GetKeyedValues(kProcDirectory, kMeminfoFilename, v, "MemTotal:");
  total = std::stof(v[1]);
  v.clear();

  GetKeyedValues(kProcDirectory, kMeminfoFilename, v, "MemFree:");
  free = std::stof(v[1]);
  return (total - free) / total; 
}

// Read and return the system uptime
long LinuxParser::UpTime() {
  std::vector<std::string> v;
  LinuxParser::GetKeyedValues(kProcDirectory, kUptimeFilename, v, ""); 
  return std::stol(v[1]); 
}

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
  GetKeyedValues(kProcDirectory, kStatFilename, v, "processes");
  return std::stoi(v[1]); 
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  std::vector<std::string> v;
  GetKeyedValues(kProcDirectory, kStatFilename, v, "procs_running");
  return std::stoi(v[1]); 
}

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

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  std::vector<std::string> v;
  std::string fname = std::to_string(pid) + kStatusFilename;
  GetKeyedValues(kProcDirectory, fname, v, "Uid:");
  return v[1];
}

// Read and return the user associated with a process
string LinuxParser::User(int pid) {
  string uid = Uid(pid);
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
