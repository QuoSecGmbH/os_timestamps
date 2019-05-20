#ifndef CURRENT_TIME_H
#define CURRENT_TIME_H

// #pragma once 

// #include <sys/time.h>
#include <time.h>
// int clock_gettime(clockid_t clock_id, struct timespec *tp);

// #include <linux/time.h>
// #include <bits/types/clockid_t.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <sys/types.h>

#include "log.h"
#include "misc.h"

// int main();
void print_current_time_s();
void print_current_time_custom(int type);
void print_current_time_ns();
time_t* current_time_s();
int check_general_clock_res(FILE* csv_file, FILE* outpuy_file, FILE* error_file);
int check_general_clock_increments(FILE* csv_file, FILE* output_file, FILE* error_file);
struct timespec* current_time_custom(int type);
struct timespec* current_time_ns();
struct timespec* current_time_ns_coarse();

#ifdef __linux__
    struct timespec* current_time_ns_linux_coarse();
    #pragma message("__linux__: current_time_ns_fslike_osspecific will resolve to current_time_ns_linux_coarse")
#elif __FreeBSD__
    struct timespec* current_time_ns_freebsd_coarse();
    #pragma message("__FreeBSD__: current_time_ns_fslike_osspecific will resolve to current_time_ns_freebsd_coarse")
#elif __OpenBSD__
    struct timespec* current_time_ns_openbsd_coarse();
    #pragma message("__OpenBSD__: current_time_ns_fslike_osspecific will resolve to current_time_ns_openbsd_coarse")
#else
    #pragma message("OS not detected: current_time_ns_fslike_osspecific will resolve to current_time_ns")
#endif
struct timespec*  current_time_ns_fslike_osspecific();

#endif
