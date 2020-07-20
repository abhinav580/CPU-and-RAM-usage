# CPU-and-RAM-usage

## Windows
In Windows there is a library named "windows.h" for C++ which contains a class <b>MEMORYSTATUSEX</b>. This class contains all the information about CPU(Idle time, CPU Load, etc) as well as about Memory(RAM being used, available RAM, etc). So I have used this Library to implement the stuffs in the Qt Application.


## Linux
In Linux we have a straight forward technique to get the required data. I have used two files: <br> 
<b>1. /proc/meminfo</b> To get the data regarding RAM(i.e., Total memory, Available Memory, etc)
<br>
<b>2. /proc/stat</b> To get the data regarding CPU usage.

