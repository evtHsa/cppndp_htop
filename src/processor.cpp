#include "processor.h"
#include <cassert> // TODO:FIXME
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    long total = LinuxParser::Jiffies(); // TODO: is this int64 which i think /proc/stat uses?
    long active = LinuxParser::ActiveJiffies();
    float ret;
    ret = (float)active / total;
    return ret;
}