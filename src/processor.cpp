#include "processor.h"
#include "linux_parser.h"

// Return the aggregate CPU utilization
float Processor::Utilization() { 
    long total = LinuxParser::Jiffies();
    long active = LinuxParser::ActiveJiffies();
    float ret;
    ret = (float)active / total;
    return ret;
}