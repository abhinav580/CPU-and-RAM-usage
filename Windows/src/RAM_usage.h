#include "windows.h"

float RAM_used(){
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	return (memInfo.ullTotalPhys - memInfo.ullAvailPhys)*100.00/memInfo.ullTotalPhys;
}

float TotalRAM()
{
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	return memInfo.ullTotalPhys;
}


float FreeRAM()
{
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	return memInfo.ullAvailPhys;
}