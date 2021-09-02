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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "log.h"
#include "misc.h"
// #include "current_time_message.h"

extern char* path_timemarker;
extern char* path_timemarkerdir;

void current_time_setup_local_timemarker(FILE* output_file, FILE* error_file);
void current_time_setup_local_timemarkerdir(FILE* output_file, FILE* error_file);

// int main();
void print_current_time_s();
void print_current_time_ns_fslike_osspecific();
void print_current_time_custom(int type);
void print_current_time_ns();
time_t* current_time_s();
int check_general_clock_res(FILE* csv_file, FILE* outpuy_file, FILE* error_file, char* dir_path);
int check_general_clock_realtime_increments(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_general_clock_ns_fslike_osspecific_increments(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
struct timespec* current_time_custom(int type);
struct timespec* current_time_ns();
struct timespec* current_time_ns_coarse();


#ifdef __linux__
struct timespec* current_time_ns_linux_coarse();
#endif

#ifdef __FreeBSD__
struct timespec* current_time_ns_freebsd_coarse();
#endif

#ifdef __OpenBSD__
struct timespec* current_time_ns_openbsd_coarse();
#endif


struct timespec* current_time_ns_fslike_generic();
struct timespec* current_time_ns_fslike_generic_futimens();
struct timespec*  current_time_ns_fslike_osspecific();

#endif
