/*
  readproc.h
  Reads /proc/meminfo for information about system memory
*/

#ifndef READPROC
#define READPROC

int GetMemTotal(){
/* This function is used in order to read the meminfo file
   in order to obtain the total amount of memory in the system.
   Returns -1 if there was an error.
*/
    FILE *meminfo = fopen("/proc/meminfo", "r");
    if(meminfo == NULL){
      return -1;
    }

    char line[256];
    while(fgets(line, sizeof(line), meminfo)){
        int memTotal;
        if(sscanf(line, "MemTotal: %d kB", &memTotal) == 1){
            fclose(meminfo);
            return memTotal;
        }
    }

    // Getting here means we were not able to find what we were looking for
    fclose(meminfo);
    return -1;
}

int GetMemAvail(){
/* Same function as above but it parses the meminfo file
   in order to obtain the current amount of physical memory available
*/
    FILE *meminfo = fopen("/proc/meminfo", "r");
    if(meminfo == NULL){
      return -1;
    }

    char line[256];
    while(fgets(line, sizeof(line), meminfo)){
        int memAvail;
        if(sscanf(line, "MemAvailable: %d kB", &memAvail) == 1){
            fclose(meminfo);
            return memAvail;
        }
    }

    fclose(meminfo);
    return -1;
}

#endif
