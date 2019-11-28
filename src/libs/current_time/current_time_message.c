#ifndef CURRENT_TIME_MESSAGE_H
#define CURRENT_TIME_MESSAGE_H

#ifdef __linux__
    struct timespec* current_time_ns_linux_coarse();
    #pragma message("__linux__: current_time_ns_fslike_osspecific will resolve to current_time_ns_linux_coarse")
#elif __FreeBSD__
    struct timespec* current_time_ns_freebsd_coarse();
    #pragma message("__FreeBSD__: current_time_ns_fslike_osspecific will resolve to current_time_ns_freebsd_coarse")
#elif __OpenBSD__
    #include "file_ts.h"
    struct timespec* current_time_ns_openbsd_coarse();
    #pragma message("__OpenBSD__: current_time_ns_fslike_osspecific will resolve to current_time_ns_openbsd_coarse")
#else
    #pragma message("OS not detected: current_time_ns_fslike_osspecific will resolve to current_time_ns")
#endif
    
#endif
