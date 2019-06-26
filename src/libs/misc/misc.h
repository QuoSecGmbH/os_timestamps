#ifndef MISC_H
#define MISC_H

#include "time.h"
#include "log.h"
#include <sys/stat.h>
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include "file_ts.h"

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

static const int GRANULARITY_NS = 1000;
static const int GRANULARITY_US = 1000000;
static const int GRANULARITY_MS = 1000000000;

extern int VERBOSE;

char* misc_concat(char* buf1, char* buf2);
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
