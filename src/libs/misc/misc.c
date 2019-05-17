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

int result_MAC_updated(int M, int A, int C, FILE* output_file, FILE* error_file, const char* func_name, struct timespec* ts_before, struct timespec* ts_after, struct stat* file_stat) {
    int result = 0;
    
    if (M==UPDATE_MANDATORY || M==UPDATE_OPTIONAL){
        if (misc_timespec_leq_leq(ts_before, &(file_stat->st_mtim), ts_after) != 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "M not updated");
            if (M==UPDATE_MANDATORY){
                result = 2;
            }
        }
    }
    else if (M==NOUPDATE_MANDATORY || M==NOUPDATE_OPTIONAL){
        if (misc_timespec_leq_leq(ts_before, &(file_stat->st_mtim), ts_after) == 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "M updated");
            if (M==NOUPDATE_MANDATORY){
                result = 2;
            }
        }
    }
    
    if (A==UPDATE_MANDATORY || A==UPDATE_OPTIONAL){
        if (misc_timespec_leq_leq(ts_before, &(file_stat->st_atim), ts_after) != 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "A not updated");
            if (A==UPDATE_MANDATORY){
                result = 2;
            }
        }
    }
    else if (A==NOUPDATE_MANDATORY || A==NOUPDATE_OPTIONAL){
        if (misc_timespec_leq_leq(ts_before, &(file_stat->st_atim), ts_after) == 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "A updated");
            if (A==NOUPDATE_MANDATORY){
                result = 2;
            }
        }
    }
    
    if (C==UPDATE_MANDATORY || C==UPDATE_OPTIONAL){
        if (misc_timespec_leq_leq(ts_before, &(file_stat->st_ctim), ts_after) != 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "C not updated");
            if (C==UPDATE_MANDATORY){
                result = 2;
            }
        }
    }
    else if (C==NOUPDATE_MANDATORY || C==NOUPDATE_OPTIONAL){
        if (misc_timespec_leq_leq(ts_before, &(file_stat->st_ctim), ts_after) == 0){
            log_warning(output_file, error_file, "%s - %s", func_name, "C updated");
            if (C==NOUPDATE_MANDATORY){
                result = 2;
            }
        }
    }
    
    return result;
}

#endif
