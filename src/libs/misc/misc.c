#ifndef MISC_C
#define MISC_C

#include "misc.h"

char* misc_concat(char* buf1, char* buf2){
    int len1 = strlen(buf1);
    int len2 = strlen(buf2);
    
    char* buf = calloc(sizeof(char), len1+len2+1);
    strcpy(buf, buf1);
    strcat(buf, buf2);
    
    return buf;
}

int misc_timespec_leq_leq(struct timespec* ts1, struct timespec* ts, struct timespec* ts2){
    if (misc_timespec_leq(ts1, ts) == 0 && misc_timespec_leq(ts, ts2) == 0){
        return 0;
    }
    return 1;
}

int misc_timespec_leq(struct timespec* ts1, struct timespec* ts2){
    if (ts1->tv_sec < ts2->tv_sec){
        return 0;
    }
    else if (ts1->tv_sec == ts2->tv_sec && ts1->tv_nsec <= ts2->tv_nsec){
        return 0;
    }
    return 1;
}

int misc_timespec_geq(struct timespec* ts1, struct timespec* ts2){
    if (ts1->tv_sec > ts2->tv_sec){
        return 0;
    }
    else if (ts1->tv_sec == ts2->tv_sec && ts1->tv_nsec >= ts2->tv_nsec){
        return 0;
    }
    return 1;
}

int misc_timespec_eq(struct timespec* ts1, struct timespec* ts2){
    if (ts1->tv_sec == ts2->tv_sec && ts1->tv_nsec == ts2->tv_nsec){
        return 0;
    }
    return 1;
}

#endif
