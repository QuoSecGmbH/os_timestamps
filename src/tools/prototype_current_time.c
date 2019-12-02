#ifndef PROTOTYPE_CURRENT_TIME_C
#define PROTOTYPE_CURRENT_TIME_C

#include "prototype_current_time.h"


int main (int argc, char **argv){
  if (argc >= 3){
#ifndef __linux__
#ifndef __FreeBSD__
    current_time_setup_local_timemarker(stdout, stderr);
    current_time_setup_local_timemarkerdir(stdout, stderr);
#endif
#endif
    print_current_time_ns_fslike_osspecific();
  }
  else if (argc >= 2){
    int type = atoi(argv[1]);
    print_current_time_custom(type);
  }
  else {
    print_current_time_ns();
  }
  
}

/*
On Linux:
    - https://www.kernel.org/doc/html/latest/core-api/timekeeping.html
    - https://github.com/torvalds/linux/blob/master/include/uapi/linux/time.h#L44
#define CLOCK_REALTIME              0
#define CLOCK_MONOTONIC             1
#define CLOCK_PROCESS_CPUTIME_ID    2
#define CLOCK_THREAD_CPUTIME_ID	    3
#define CLOCK_MONOTONIC_RAW         4
#define CLOCK_REALTIME_COARSE       5
#define CLOCK_MONOTONIC_COARSE      6
#define CLOCK_BOOTTIME              7
#define CLOCK_REALTIME_ALARM        8
#define CLOCK_BOOTTIME_ALARM        9
*/


#endif
