/*
  logger.h
  Header file which contains the logger class and a helper function
*/
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <time.h>

// Helper functions which allow to read /proc/meminfo file for necessary info
#include "readproc.h"

#ifndef LOGGER
#define LOGGER

using namespace std;

// Helper function which is used to get current timestamp
const string currentDateTime(){
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);

  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

  return buf;
}

class Logger{
  public:
    float logger();
    float logMemoryUsage();
    float availMem();

};

float Logger::logger(){
	
	return this->logMemoryUsage();
}


float Logger::logMemoryUsage(){
  /* Write to the file current amount of memory used and memory available,
     along with a timestamp 
  */

  float scalingFactor = 1000;
  int totalMemory = GetMemTotal();
  int availableMemory = GetMemAvail();
  int memoryUsed = totalMemory - availableMemory;

  return (memoryUsed/scalingFactor)/1024;
}

float Logger::availMem(){
	return GetMemTotal()/1000.0/1024.0;
}

#endif
