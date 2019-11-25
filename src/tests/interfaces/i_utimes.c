#ifndef I_UTIMES_C
#define I_UTIMES_C

#include "i_utimes.h"

int check_interfaces_ts_utimes_now_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.utimes", s_1s, ns_0ns, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    // Is there a better way to set time to now with utimes ?
    struct timespec* ts_current_time = current_time_ns_fslike_osspecific();
    struct timespec* ts_current_time_us = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_current_time_us->tv_nsec = (ts_current_time->tv_nsec / 1000) * 1000;
    ts_current_time_us->tv_sec = ts_current_time->tv_sec;
    
    struct timeval* tv_now1 = (struct timeval*) calloc(sizeof(struct timeval), 1);
    struct timeval* tv_now2 = (struct timeval*) calloc(sizeof(struct timeval), 1);
    tv_now1->tv_usec = ts_current_time->tv_nsec / 1000;
    tv_now1->tv_sec = ts_current_time->tv_sec;
    tv_now2->tv_usec = ts_current_time->tv_nsec / 1000;
    tv_now2->tv_sec = ts_current_time->tv_sec;
    
    struct timeval times[2];
    times[0] = *tv_now1;
    times[1] = *tv_now2;
    
    int ret = utimes(path, times);
    if (ret != 0) {
        log_warning(output_file, error_file, "%s - %s %d", __func__, "utimes failed with errno", errno);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat->st_atim), ts_current_time_us) != 0){
        // Case: A was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "A not correctly set");
        result = 2;
    }
    
    if (misc_timespec_eq(&(file_stat->st_mtim), ts_current_time_us) != 0){
        // Case: M was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "M not correctly set");
        result = 2;
    }
    
    int result_update = result_MAC_updated(UPDATE_NOCHECK, UPDATE_NOCHECK, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    result = misc_max2(result, result_update);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_current_time);
    free(ts_current_time_us);
    free(tv_now1);
    free(tv_now2);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_interfaces_ts_utimes_now_us(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.utimes", s_1s, ns_0ns, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    // Is there a better way to set time to now with utimes ?
    struct timespec* ts_current_time = current_time_ns_fslike_osspecific();
    
    struct timeval* tv_now1 = (struct timeval*) calloc(sizeof(struct timeval), 1);
    struct timeval* tv_now2 = (struct timeval*) calloc(sizeof(struct timeval), 1);
    tv_now1->tv_usec = ts_current_time->tv_nsec / 1000;
    tv_now1->tv_sec = ts_current_time->tv_sec;
    tv_now2->tv_usec = ts_current_time->tv_nsec / 1000;
    tv_now2->tv_sec = ts_current_time->tv_sec;
    
    struct timeval times[2];
    times[0] = *tv_now1;
    times[1] = *tv_now2;
    
    int ret = utimes(path, times);
    if (ret != 0) {
        log_warning(output_file, error_file, "%s - %s %d", __func__, "utimes failed with errno", errno);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    int result = result_MAC_granularity(GRANULARITY_MANDATORY, GRANULARITY_MANDATORY, GRANULARITY_NOCHECK, output_file, error_file, __func__, GRANULARITY_US, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_current_time);
    free(tv_now1);
    free(tv_now2);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_interfaces_ts_utimes_set_future_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.utimes", s_1s, ns_0ns, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    struct timeval* tv_A = (struct timeval*) calloc(sizeof(struct timeval), 1);
    struct timeval* tv_M = (struct timeval*) calloc(sizeof(struct timeval), 1);
    tv_A->tv_usec = 128539;
    tv_A->tv_sec = 2109839871; // Sun Nov  9 11:37:51 CET 2036
    tv_M->tv_usec = 786103;
    tv_M->tv_sec = 2009843984; // Fri Sep  9 03:59:44 CEST 2033
    
    struct timespec* ts_A_us = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_A_us->tv_nsec = tv_A->tv_usec * 1000;
    ts_A_us->tv_sec = tv_A->tv_sec;
    
    struct timespec* ts_M_us = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_M_us->tv_nsec = tv_M->tv_usec * 1000;
    ts_M_us->tv_sec = tv_M->tv_sec;
    
    struct timeval times[2];
    times[0] = *tv_A;
    times[1] = *tv_M;
    
    int ret = utimes(path, times);
    if (ret != 0) {
        log_warning(output_file, error_file, "%s - %s %d", __func__, "utimes failed with errno", errno);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat_macb* file_stat_after = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat_after->st_atim), ts_A_us) != 0){
        // Case: A was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "A not correctly set");
        result = 2;
    }
    
    if (misc_timespec_eq(&(file_stat_after->st_mtim), ts_M_us) != 0){
        // Case: M was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "M not correctly set");
        result = 2;
    }
    
    int result_update = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat_after);
    
    result = misc_max2(result, result_update);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat_after);
    
    free(path);
    free(tv_A);
    free(tv_M);
    free(ts_A_us);
    free(ts_M_us);
    free(ts_before);
    free(ts_after);
    free(file_stat_after);
    
    return result;
}


int check_interfaces_ts_utimes_set_past_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.utimes", s_1s, ns_0ns, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    struct timeval* tv_A = (struct timeval*) calloc(sizeof(struct timeval), 1);
    struct timeval* tv_M = (struct timeval*) calloc(sizeof(struct timeval), 1);
    tv_A->tv_usec = 454545;
    tv_A->tv_sec = 732098712; // Sun Mar 14 09:45:12 CET 1993
    tv_M->tv_usec = 781488;
    tv_M->tv_sec = 1509823233; // Sat Nov  4 20:20:33 CET 2017
    
    struct timespec* ts_A_us = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_A_us->tv_nsec = tv_A->tv_usec * 1000;
    ts_A_us->tv_sec = tv_A->tv_sec;
    
    struct timespec* ts_M_us = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_M_us->tv_nsec = tv_M->tv_usec * 1000;
    ts_M_us->tv_sec = tv_M->tv_sec;
    
    struct timeval times[2];
    times[0] = *tv_A;
    times[1] = *tv_M;
    
    int ret = utimes(path, times);
    if (ret != 0) {
        log_warning(output_file, error_file, "%s - %s %d", __func__, "utimes failed with errno", errno);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat_macb* file_stat_after = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat_after->st_atim), ts_A_us) != 0){
        // Case: A was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "A not correctly set");
        result = 2;
    }
    
    if (misc_timespec_eq(&(file_stat_after->st_mtim), ts_M_us) != 0){
        // Case: M was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "M not correctly set");
        result = 2;
    }
    
    int result_update = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat_after);
    
    result = misc_max2(result, result_update);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat_after);
    
    free(path);
    free(tv_A);
    free(tv_M);
    free(ts_A_us);
    free(ts_M_us);
    free(ts_before);
    free(ts_after);
    free(file_stat_after);
    
    return result;
}



#endif
