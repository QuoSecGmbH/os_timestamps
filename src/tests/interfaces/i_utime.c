#ifndef I_UTIME_C
#define I_UTIME_C

#include "i_utime.h"

int check_interfaces_ts_utime_now_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.utime", 2 * s_1s, ns_0ns, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    // Is there a better way to set time to now with utimes ?
    struct timespec* ts_current_time = current_time_ns_fslike_osspecific();
    struct timespec* ts_current_time_s = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_current_time_s->tv_nsec = 0;
    ts_current_time_s->tv_sec = ts_current_time->tv_sec;
    
    struct utimbuf* ut_now = (struct utimbuf*) calloc(sizeof(struct utimbuf), 1);
    ut_now->actime = ts_current_time->tv_sec;
    ut_now->modtime = ts_current_time->tv_sec;
    
    int ret = utime(path, ut_now);
    if (ret != 0) {
        log_warning(output_file, error_file, "%s - %s %d", __func__, "utime failed with errno", errno);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat->st_atim), ts_current_time_s) != 0){
        // Case: A was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "A not correctly set");
        result = 2;
    }
    
    if (misc_timespec_eq(&(file_stat->st_mtim), ts_current_time_s) != 0){
        // Case: M was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "M not correctly set");
        result = 2;
    }
    
    int result_update = result_MAC_updated(UPDATE_NOCHECK, UPDATE_NOCHECK, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    result = misc_max2(result, result_update);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    return result;
}

int check_interfaces_ts_utime_now_s(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.utime", 2 * s_1s, ns_0ns, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    // Is there a better way to set time to now with utimes ?
    struct timespec* ts_current_time = current_time_ns_fslike_osspecific();
    struct timespec* ts_current_time_s = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_current_time_s->tv_nsec = 0;
    ts_current_time_s->tv_sec = ts_current_time->tv_sec;
    
    struct utimbuf* ut_now = (struct utimbuf*) calloc(sizeof(struct utimbuf), 1);
    ut_now->actime = ts_current_time->tv_sec;
    ut_now->modtime = ts_current_time->tv_sec;
    
    int ret = utime(path, ut_now);
    if (ret != 0) {
        log_warning(output_file, error_file, "%s - %s %d", __func__, "utime failed with errno", errno);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_path_timestamps(path);
    
//     int resultM = result_MAC_granularity(GRANULARITY_MANDATORY, GRANULARITY_NOCHECK, GRANULARITY_NOCHECK, output_file, error_file, __func__, GRANULARITY_US, ts_before, ts_after, file_stat);
//     int resultA = result_MAC_granularity(GRANULARITY_NOCHECK, GRANULARITY_MANDATORY, GRANULARITY_NOCHECK, output_file, error_file, __func__, GRANULARITY_US, ts_before, ts_after, file_stat);
//     int result = misc_min2(resultM, resultA);
    int result = result_MAC_granularity(GRANULARITY_MANDATORY, GRANULARITY_MANDATORY, GRANULARITY_NOCHECK, output_file, error_file, __func__, GRANULARITY_S, ts_before, ts_after, file_stat);
    
//     if (result == 2){
//         // Case: granularity for both is not microsecond, we then consider granularity is s as expected
//         result = 0;
//     }
//     else {
//         log_warning(output_file, error_file, "%s - %s %d", __func__, "granularity is not second");
//         result = 2;
//     }
    
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    return result;
}

int check_interfaces_ts_utime_set_future_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.utime", 2 * s_1s, ns_0ns, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    struct stat* file_stat_before = get_path_timestamps(path);

    struct utimbuf* ut_future = (struct utimbuf*) calloc(sizeof(struct utimbuf), 1);
    ut_future->actime = 2109839871; // Sun Nov  9 11:37:51 CET 2036
    ut_future->modtime = 2009843984; // Fri Sep  9 03:59:44 CEST 2033
    
    struct timespec* ts_A_s = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_A_s->tv_nsec = 0;
    ts_A_s->tv_sec = ut_future->actime;
    
    struct timespec* ts_M_s = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_M_s->tv_nsec = 0;
    ts_M_s->tv_sec = ut_future->modtime;
    
    int ret = utime(path, ut_future);
    if (ret != 0) {
        log_warning(output_file, error_file, "%s - %s %d", __func__, "utime failed with errno", errno);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat_after = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat_after->st_atim), ts_A_s) != 0){
        // Case: A was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "A not correctly set");
        result = 2;
    }
    
    if (misc_timespec_eq(&(file_stat_after->st_mtim), ts_M_s) != 0){
        // Case: M was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "M not correctly set");
        result = 2;
    }
    
    int result_update = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat_after);
    
    result = misc_max2(result, result_update);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat_after);
    return result;
}

int check_interfaces_ts_utime_set_past_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.utime", 2 * s_1s, ns_0ns, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    struct stat* file_stat_before = get_path_timestamps(path);

    struct utimbuf* ut_past = (struct utimbuf*) calloc(sizeof(struct utimbuf), 1);
    ut_past->actime = 732098712; // Sun Mar 14 09:45:12 CET 1993
    ut_past->modtime = 1509823233; // Sat Nov  4 20:20:33 CET 2017
    
    struct timespec* ts_A_s = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_A_s->tv_nsec = 0;
    ts_A_s->tv_sec = ut_past->actime;
    
    struct timespec* ts_M_s = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_M_s->tv_nsec = 0;
    ts_M_s->tv_sec = ut_past->modtime;
    
    int ret = utime(path, ut_past);
    if (ret != 0) {
        log_warning(output_file, error_file, "%s - %s %d", __func__, "utime failed with errno", errno);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat_after = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat_after->st_atim), ts_A_s) != 0){
        // Case: A was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "A not correctly set");
        result = 2;
    }
    
    if (misc_timespec_eq(&(file_stat_after->st_mtim), ts_M_s) != 0){
        // Case: M was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "M not correctly set");
        result = 2;
    }
    
    int result_update = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat_after);
    
    result = misc_max2(result, result_update);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat_after);
    return result;
}



#endif
