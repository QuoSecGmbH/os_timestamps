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

On OpenBSD:
    - https://man.openbsd.org/clock_settime
    - https://github.com/openbsd/src/blob/master/sys/sys/_time.h#L35
#define CLOCK_REALTIME              0
#define CLOCK_PROCESS_CPUTIME_ID    2
#define CLOCK_MONOTONIC             3
#define CLOCK_THREAD_CPUTIME_ID     4
#define CLOCK_UPTIME                5
#define CLOCK_BOOTTIME              6

On FreeBSD:
    - https://www.freebsd.org/cgi/man.cgi?query=clock_gettime
    - https://github.com/freebsd/freebsd/blob/96ac98747a90910e1178abccc617e9f04692dcec/sys/sys/time.h#L463
#define	CLOCK_REALTIME              0
#define	CLOCK_VIRTUAL               1
#define	CLOCK_PROF                  2
#define	CLOCK_MONOTONIC             4
#define	CLOCK_UPTIME                5	FreeBSD-specific. 
#define	CLOCK_UPTIME_PRECISE        7	FreeBSD-specific. 
#define	CLOCK_UPTIME_FAST           8	FreeBSD-specific. 
#define	CLOCK_REALTIME_PRECISE      9	FreeBSD-specific. 
#define	CLOCK_REALTIME_FAST         10	FreeBSD-specific. 
#define	CLOCK_MONOTONIC_PRECISE     11	FreeBSD-specific. 
#define	CLOCK_MONOTONIC_FAST        12	FreeBSD-specific. 
#define	CLOCK_SECOND                13	FreeBSD-specific. 
#define	CLOCK_THREAD_CPUTIME_ID     14
#define	CLOCK_PROCESS_CPUTIME_ID    15
*/


#endif
