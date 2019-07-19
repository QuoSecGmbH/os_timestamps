#ifndef I_UIMENSAT_C
#define I_UIMENSAT_C

#include "i_futimens.h"

int check_interfaces_ts_utimensat_now_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.utimensat", s_0s, ns_100ms, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    struct timespec* ts_now1 = (struct timespec*) calloc(sizeof(struct timespec), 1);
    struct timespec* ts_now2 = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_now1->tv_nsec = UTIME_NOW;
    ts_now1->tv_sec = 0;
    ts_now2->tv_nsec = UTIME_NOW;
    ts_now2->tv_sec = 0;
    
    struct timespec times[2];
    times[0] = *ts_now1;
    times[1] = *ts_now2;
    
    int ret = utimensat(AT_FDCWD, path, times, 0);
    if (ret != 0) {
        log_warning(output_file, error_file, "%s - %s %d", __func__, "futimens failed with errno", errno);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_path_timestamps(path);
    
    int result = result_MAC_updated(UPDATE_MANDATORY, UPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    return result;
}

int check_interfaces_ts_utimensat_now_ns(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.utimensat", s_0s, ns_100ms, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    struct timespec* ts_now1 = (struct timespec*) calloc(sizeof(struct timespec), 1);
    struct timespec* ts_now2 = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_now1->tv_nsec = UTIME_NOW;
    ts_now1->tv_sec = 0;
    ts_now2->tv_nsec = UTIME_NOW;
    ts_now2->tv_sec = 0;
    
    struct timespec times[2];
    times[0] = *ts_now1;
    times[1] = *ts_now2;
    
    int ret = utimensat(AT_FDCWD, path, times, 0);
    if (ret != 0) {
        log_warning(output_file, error_file, "%s - %s %d", __func__, "futimens failed with errno", errno);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_path_timestamps(path);
    
    int result = result_MAC_granularity(GRANULARITY_MANDATORY, GRANULARITY_MANDATORY, GRANULARITY_NOCHECK, output_file, error_file, __func__, GRANULARITY_NS, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    return result;
}

int check_interfaces_ts_utimensat_now_ma_eq(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat(dir_path, "interfaces.utimensat");
    
    struct stat* file_stat = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat->st_mtim), &(file_stat->st_atim)) != 0){
        log_warning(output_file, error_file, "%s - MA not equal", __func__);
        result = 2;
    }
    
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, NULL, NULL, file_stat);
    return result;
}

int check_interfaces_ts_utimensat_now_mac_eq(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat(dir_path, "interfaces.utimensat");
    
    struct stat* file_stat = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat->st_mtim), &(file_stat->st_atim)) != 0 || misc_timespec_eq(&(file_stat->st_atim), &(file_stat->st_ctim)) != 0){
        log_warning(output_file, error_file, "%s - MAC not equal", __func__);
        result = 2;
    }
    
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, NULL, NULL, file_stat);
    return result;
}

int check_interfaces_ts_utimensat_set_future_a(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.utimensat", s_0s, ns_100ms, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    struct stat* file_stat_before = get_path_timestamps(path);
    
    struct timespec* ts_A = (struct timespec*) calloc(sizeof(struct timespec), 1);
    struct timespec* ts_M = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_A->tv_nsec = 151969641;
    ts_A->tv_sec = 2072274421; // Sat Sep  1 17:47:01 CEST 2035
    ts_M->tv_nsec = UTIME_OMIT;
    ts_M->tv_sec = 0;
    
    struct timespec times[2];
    times[0] = *ts_A;
    times[1] = *ts_M;
    
    int ret = utimensat(AT_FDCWD, path, times, 0);
    if (ret != 0) {
        log_warning(output_file, error_file, "%s - %s %d", __func__, "futimens failed with errno", errno);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat_after = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat_after->st_atim), ts_A) != 0){
        // Case: A was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "A not correctly set");
        result = 2;
    }
    
    int result_keep = result_MAC_kept(KEEP_MANDATORY, NOKEEP_MANDATORY, NOKEEP_MANDATORY, output_file, error_file, __func__, file_stat_before, file_stat_after);
    int result_update = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat_after);
    
    result = misc_max3(result, result_keep, result_update);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat_after);
    return result;
}

int check_interfaces_ts_utimensat_set_past_a(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.utimensat", s_0s, ns_100ms, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    struct stat* file_stat_before = get_path_timestamps(path);
    
    struct timespec* ts_A = (struct timespec*) calloc(sizeof(struct timespec), 1);
    struct timespec* ts_M = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_A->tv_nsec = 823515132;
    ts_A->tv_sec = 1187398743; // Sat Aug 18 02:59:03 CEST 2007
    ts_M->tv_nsec = UTIME_OMIT;
    ts_M->tv_sec = 0;
    
    struct timespec times[2];
    times[0] = *ts_A;
    times[1] = *ts_M;
    
    int ret = utimensat(AT_FDCWD, path, times, 0);
    if (ret != 0) {
        log_warning(output_file, error_file, "%s - %s %d", __func__, "futimens failed with errno", errno);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat_after = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat_after->st_atim), ts_A) != 0){
        // Case: A was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "A not correctly set");
        result = 2;
    }
    
    int result_keep = result_MAC_kept(KEEP_MANDATORY, NOKEEP_MANDATORY, NOKEEP_MANDATORY, output_file, error_file, __func__, file_stat_before, file_stat_after);
    int result_update = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat_after);
    
    result = misc_max3(result, result_keep, result_update);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat_after);
    return result;
}

int check_interfaces_ts_utimensat_set_future_m(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.utimensat", s_0s, ns_100ms, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    struct stat* file_stat_before = get_path_timestamps(path);
    
    struct timespec* ts_A = (struct timespec*) calloc(sizeof(struct timespec), 1);
    struct timespec* ts_M = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_A->tv_nsec = UTIME_OMIT;
    ts_A->tv_sec = 0;
    ts_M->tv_nsec = 151969641;
    ts_M->tv_sec = 2072274421; // Sat Sep  1 17:47:01 CEST 2035
    
    struct timespec times[2];
    times[0] = *ts_A;
    times[1] = *ts_M;
    
    int ret = utimensat(AT_FDCWD, path, times, 0);
    if (ret != 0) {
        log_warning(output_file, error_file, "%s - %s %d", __func__, "futimens failed with errno", errno);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat_after = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat_after->st_mtim), ts_M) != 0){
        // Case: M was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "M not correctly set");
        result = 2;
    }
    
    int result_keep = result_MAC_kept(NOKEEP_MANDATORY, KEEP_MANDATORY, NOKEEP_MANDATORY, output_file, error_file, __func__, file_stat_before, file_stat_after);
    int result_update = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat_after);
    
    result = misc_max3(result, result_keep, result_update);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat_after);
    return result;
}

int check_interfaces_ts_utimensat_set_past_m(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.utimensat", s_0s, ns_100ms, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    struct stat* file_stat_before = get_path_timestamps(path);
    
    struct timespec* ts_A = (struct timespec*) calloc(sizeof(struct timespec), 1);
    struct timespec* ts_M = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_A->tv_nsec = UTIME_OMIT;
    ts_A->tv_sec = 0; 
    ts_M->tv_nsec = 823515132;
    ts_M->tv_sec = 1187398743; // Sat Aug 18 02:59:03 CEST 2007
    
    struct timespec times[2];
    times[0] = *ts_A;
    times[1] = *ts_M;
    
    int ret = utimensat(AT_FDCWD, path, times, 0);
    if (ret != 0) {
        log_warning(output_file, error_file, "%s - %s %d", __func__, "futimens failed with errno", errno);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat_after = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat_after->st_mtim), ts_M) != 0){
        // Case: M was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "M not correctly set");
        result = 2;
    }
    
    int result_keep = result_MAC_kept(NOKEEP_MANDATORY, KEEP_MANDATORY, NOKEEP_MANDATORY, output_file, error_file, __func__, file_stat_before, file_stat_after);
    int result_update = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat_after);
    
    result = misc_max3(result, result_keep, result_update);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat_after);
    return result;
}


int check_interfaces_ts_utimensat_set_future_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.utimensat", s_0s, ns_100ms, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    struct stat* file_stat_before = get_path_timestamps(path);
    
    struct timespec* ts_A = (struct timespec*) calloc(sizeof(struct timespec), 1);
    struct timespec* ts_M = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_A->tv_nsec = 128539465;
    ts_A->tv_sec = 2109839871; // Sun Nov  9 11:37:51 CET 2036
    ts_M->tv_nsec = 786103930;
    ts_M->tv_sec = 2009843984; // Fri Sep  9 03:59:44 CEST 2033
    
    struct timespec times[2];
    times[0] = *ts_A;
    times[1] = *ts_M;
    
    int ret = utimensat(AT_FDCWD, path, times, 0);
    if (ret != 0) {
        log_warning(output_file, error_file, "%s - %s %d", __func__, "futimens failed with errno", errno);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat_after = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat_after->st_atim), ts_A) != 0){
        // Case: A was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "A not correctly set");
        result = 2;
    }
    
    if (misc_timespec_eq(&(file_stat_after->st_mtim), ts_M) != 0){
        // Case: M was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "M not correctly set");
        result = 2;
    }
    
    int result_update = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat_after);
    
    result = misc_max2(result, result_update);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat_after);
    return result;
}


int check_interfaces_ts_utimensat_set_past_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.utimensat", s_0s, ns_100ms, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    struct stat* file_stat_before = get_path_timestamps(path);
    
    struct timespec* ts_A = (struct timespec*) calloc(sizeof(struct timespec), 1);
    struct timespec* ts_M = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_A->tv_nsec = 454545656;
    ts_A->tv_sec = 732098712; // Sun Mar 14 09:45:12 CET 1993
    ts_M->tv_nsec = 781488087;
    ts_M->tv_sec = 1509823233; // Sat Nov  4 20:20:33 CET 2017
    
    struct timespec times[2];
    times[0] = *ts_A;
    times[1] = *ts_M;
    
    int ret = utimensat(AT_FDCWD, path, times, 0);
    if (ret != 0) {
        log_warning(output_file, error_file, "%s - %s %d", __func__, "futimens failed with errno", errno);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat_after = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat_after->st_atim), ts_A) != 0){
        // Case: A was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "A not correctly set");
        result = 2;
    }
    
    if (misc_timespec_eq(&(file_stat_after->st_mtim), ts_M) != 0){
        // Case: M was not set to correct value
        log_warning(output_file, error_file, "%s - %s", __func__, "M not correctly set");
        result = 2;
    }
    
    int result_update = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat_after);
    
    result = misc_max2(result, result_update);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat_after);
    return result;
}


int check_interfaces_ts_utimensat_set_omit(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.utimensat", s_0s, ns_100ms, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    struct stat* file_stat_before = get_path_timestamps(path);
    
    struct timespec* ts_A = (struct timespec*) calloc(sizeof(struct timespec), 1);
    struct timespec* ts_M = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_A->tv_nsec = UTIME_OMIT;
    ts_A->tv_sec = 0;
    ts_M->tv_nsec = UTIME_OMIT;
    ts_M->tv_sec = 0;
    
    struct timespec times[2];
    times[0] = *ts_A;
    times[1] = *ts_M;
    
    int ret = utimensat(AT_FDCWD, path, times, 0);
    if (ret != 0) {
        log_warning(output_file, error_file, "%s - %s %d", __func__, "futimens failed with errno", errno);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat_after = get_path_timestamps(path);
    
    int result = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat_after);
    
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat_after);
    return result;
}



#endif
