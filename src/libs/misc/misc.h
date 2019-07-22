#ifndef MISC_H
#define MISC_H

#include "time.h"
#include "log.h"
#include <sys/stat.h>
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include "file_ts.h"
#include <unistd.h>


static const long ns_0ns = 0;
static const long ns_1ns = 1;
static const long ns_10ns = 10;
static const long ns_100ns = 100;
static const long ns_1us = 1000;
static const long ns_10us = 10000;
static const long ns_100us = 100000;
static const long ns_1ms = 1000000;
static const long ns_10ms = 10000000; // 10ms: smaller i / 10**i makes a difference with nanosleep + file write + *stat*
static const long ns_100ms = 100000000;
static const long ns_1s = 1000000000;

static const time_t s_0s = 0;
static const time_t s_1s = 1;
static const time_t s_10s = 10;

static const int UPDATE_MANDATORY = 0;
static const int UPDATE_OPTIONAL = 1;
static const int NOUPDATE_MANDATORY = 2;
static const int NOUPDATE_OPTIONAL = 3;
static const int UPDATE_NOCHECK = 4;

static const int KEEP_MANDATORY = 0;
static const int KEEP_OPTIONAL = 1;
static const int NOKEEP_MANDATORY = 2;
static const int NOKEEP_OPTIONAL = 3;
static const int KEEP_NOCHECK = 4;

static const int GRANULARITY_MANDATORY = 0;
static const int GRANULARITY_OPTIONAL = 1;
static const int GRANULARITY_NOCHECK = 2;

// static const int GRANULARITY_NS = 1000;
// static const int GRANULARITY_US = 1000000;
// static const int GRANULARITY_MS = 1000000000;


// static const long GRANULARITY_LIST[] = {ns_10ns, ns_100ns, ns_1us, ns_10us, ns_100us, ns_1ms, ns_10ms, ns_100ms, ns_1s}; // from 10ns to 1s
static const long GRANULARITY_LIST[] = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000}; // from 10ns to 1s
static const int GRANULARITY_LIST_LEN = 9;

static const int GRANULARITY_NS = 0; // 10ns
static const int GRANULARITY_US = 3; // 10us
static const int GRANULARITY_MS = 6; // 10ms
static const int GRANULARITY_S = 9; // 10ms


extern int VERBOSE;

int misc_invert_check_result(int res);

void misc_nanosleep(int ns);
void misc_microsleep(int us);
void misc_millisleep(int ms);
void misc_sleep(int s);

char* misc_concat(char* buf1, char* buf2);
int misc_ensure_file_exists(char* buf);
char* misc_concat_ensure_file_exists(char* buf1, char* buf2, time_t sleep_s, long sleep_ns, FILE* output_file, FILE* error_file, const char* func_name);
int stat_succeeds(char *path);
void misc_cp_rwx_no_overwrite(char* path1, char* path2);

int misc_timespec_leq_leq(struct timespec* ts1, struct timespec* ts, struct timespec* ts2);
int misc_timespec_leq(struct timespec* ts1, struct timespec* ts2);
int misc_timespec_geq(struct timespec* ts1, struct timespec* ts2);
int misc_timespec_eq(struct timespec* ts1, struct timespec* ts2);
int result_MAC_updated(int M, int A, int C, FILE* output_file, FILE* error_file, const char* func_name, struct timespec* ts_before, struct timespec* ts_after, struct stat* file_stat);
int result_MAC_granularity(int M, int A, int C, FILE* output_file, FILE* error_file, const char* func_name, int divider, struct timespec* ts_before, struct timespec* ts_after, struct stat* file_stat);

int misc_min2(int a, int b);
int misc_min3(int a, int b, int c);
int misc_max2(int a, int b);
int misc_max3(int a, int b, int c);

#endif
