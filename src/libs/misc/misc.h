#ifndef MISC_H
#define MISC_H

#include "time.h"
#include "log.h"
#include <sys/stat.h>
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

static const int UPDATE_MANDATORY = 0;
static const int UPDATE_OPTIONAL = 1;
static const int NOUPDATE_MANDATORY = 2;
static const int NOUPDATE_OPTIONAL = 3;

char* misc_concat(char* buf1, char* buf2);

int misc_timespec_leq_leq(struct timespec* ts1, struct timespec* ts, struct timespec* ts2);
int misc_timespec_leq(struct timespec* ts1, struct timespec* ts2);
int misc_timespec_geq(struct timespec* ts1, struct timespec* ts2);
int misc_timespec_eq(struct timespec* ts1, struct timespec* ts2);
int result_MAC_updated(int M, int A, int C, FILE* output_file, FILE* error_file, const char* func_name, struct timespec* ts_before, struct timespec* ts_after, struct stat* file_stat);

#endif
