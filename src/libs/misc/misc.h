#ifndef MISC_H
#define MISC_H

#include "time.h"
#include "stdlib.h"
#include <string.h>

char* misc_concat(char* buf1, char* buf2);

int misc_timespec_leq_leq(struct timespec* ts1, struct timespec* ts, struct timespec* ts2);
int misc_timespec_leq(struct timespec* ts1, struct timespec* ts2);
int misc_timespec_geq(struct timespec* ts1, struct timespec* ts2);
int misc_timespec_eq(struct timespec* ts1, struct timespec* ts2);

#endif
