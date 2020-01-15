#ifndef I_FILE_MV_C
#define I_FILE_MV_C

#include "i_file_mv.h"

int check_interfaces_file_mv_rename_file(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.mv.rename.file/");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    char* path = misc_concat_ensure_file_exists(path_dir, "orig", s_0s, ns_100ms, output_file, error_file, __func__);
    char* path_new = misc_concat(path_dir, "renamed");
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    rename(path, path_new);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* file_stat = get_path_timestamps(path_new);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(path_new);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_interfaces_file_mv_rename_file_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.mv.rename.file.ma/");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    char* path = misc_concat_ensure_file_exists(path_dir, "orig", s_0s, ns_100ms, output_file, error_file, __func__);
    char* path_new = misc_concat(path_dir, "renamed");
    
    struct stat_macb* file_stat_before = get_path_timestamps(path);
    
    rename(path, path_new);
    
    struct stat_macb* file_stat_after = get_path_timestamps(path_new);

    int result = 0;
    if (misc_timespec_eq(&(file_stat_before->st_mtim), &(file_stat_after->st_mtim)) != 0 || misc_timespec_eq(&(file_stat_before->st_atim), &(file_stat_after->st_atim)) != 0) {
        log_warning(output_file, error_file, "%s - MC not kept", __func__);
        result = 2;
    }

    log_info_ts_stat_on_error_message(output_file, error_file, __func__, result, NULL, NULL, file_stat_before, "before");
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, result, NULL, NULL, file_stat_after, "after");
    
    free(path);
    free(path_new);
    free(file_stat_before);
    free(file_stat_after);
    
    return result;
}

int check_interfaces_file_mv_rename_file_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.mv.rename.file.dir/");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    char* path = misc_concat_ensure_file_exists(path_dir, "orig", s_0s, ns_100ms, output_file, error_file, __func__);
    char* path_new = misc_concat(path_dir, "renamed");
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    rename(path, path_new);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* dir_stat = get_path_timestamps(path_dir);
    
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, dir_stat);
    
    free(path);
    free(path_new);
    free(ts_before);
    free(ts_after);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_mv_rename_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.mv.rename.dir/");
    mkdir(path_dir, 0700);
    
    char* path = misc_concat(path_dir, "orig");
    char* path_new = misc_concat(path_dir, "renamed");
    mkdir(path, 0700);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    rename(path, path_new);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* file_stat = get_path_timestamps(path_new);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(path_new);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_interfaces_file_mv_rename_dir_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.mv.rename.dir.ma/");
    mkdir(path_dir, 0700);
    
    char* path = misc_concat(path_dir, "orig");
    char* path_new = misc_concat(path_dir, "renamed");
    mkdir(path, 0700);
    misc_nanosleep(ns_after_open);
    
    struct stat_macb* file_stat_before = get_path_timestamps(path);
    
    rename(path, path_new);
    
    struct stat_macb* file_stat_after = get_path_timestamps(path_new);
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat_before->st_mtim), &(file_stat_after->st_mtim)) != 0 || misc_timespec_eq(&(file_stat_before->st_atim), &(file_stat_after->st_atim)) != 0) {
        log_warning(output_file, error_file, "%s - MA not kept", __func__);
        result = 2;
    }
    
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, result, NULL, NULL, file_stat_before, "before");
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, result, NULL, NULL, file_stat_after, "after");
    
    free(path);
    free(path_new);
    free(file_stat_before);
    free(file_stat_after);
    
    return result;
}


int check_interfaces_file_mv_rename_dir_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.mv.rename.dir.dir/");
    mkdir(path_dir, 0700);
    
    char* path = misc_concat(path_dir, "orig");
    char* path_new = misc_concat(path_dir, "renamed");
    mkdir(path, 0700);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    rename(path, path_new);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* dir_stat = get_path_timestamps(path_dir);
    
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, dir_stat);
    
    free(path);
    free(path_new);
    free(ts_before);
    free(ts_after);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_mv_renameat_file(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.mv.renameat.file/");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    char* path = misc_concat_ensure_file_exists(path_dir, "orig", s_0s, ns_100ms, output_file, error_file, __func__);
    char* path_new = misc_concat(path_dir, "renamed");
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    renameat((int) AT_FDCWD, path, (int) AT_FDCWD, path_new);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* file_stat = get_path_timestamps(path_new);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(path_new);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_interfaces_file_mv_renameat_file_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.mv.renameat.file.ma/");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    char* path = misc_concat_ensure_file_exists(path_dir, "orig", s_0s, ns_100ms, output_file, error_file, __func__);
    char* path_new = misc_concat(path_dir, "renamed");
    
    struct stat_macb* file_stat_before = get_path_timestamps(path);
    
    renameat((int) AT_FDCWD, path, (int) AT_FDCWD, path_new);
    
    struct stat_macb* file_stat_after = get_path_timestamps(path_new);
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat_before->st_mtim), &(file_stat_after->st_mtim)) != 0 || misc_timespec_eq(&(file_stat_before->st_atim), &(file_stat_after->st_atim)) != 0) {
        log_warning(output_file, error_file, "%s - MC not kept", __func__);
        result = 2;
    }
    
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, result, NULL, NULL, file_stat_before, "before");
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, result, NULL, NULL, file_stat_after, "after");
    
    free(path);
    free(path_new);
    free(file_stat_before);
    free(file_stat_after);
    
    return result;
}

int check_interfaces_file_mv_renameat_file_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.mv.renameat.file.dir/");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    char* path = misc_concat_ensure_file_exists(path_dir, "orig", s_0s, ns_100ms, output_file, error_file, __func__);
    char* path_new = misc_concat(path_dir, "renamed");
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    renameat((int) AT_FDCWD, path, (int) AT_FDCWD, path_new);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* dir_stat = get_path_timestamps(path_dir);
    
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, dir_stat);
    
    free(path);
    free(path_new);
    free(ts_before);
    free(ts_after);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_mv_renameat_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.mv.renameat.dir/");
    mkdir(path_dir, 0700);
    
    char* path = misc_concat(path_dir, "orig");
    char* path_new = misc_concat(path_dir, "renamed");
    mkdir(path, 0700);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    renameat((int) AT_FDCWD, path, (int) AT_FDCWD, path_new);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* file_stat = get_path_timestamps(path_new);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(path_new);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_interfaces_file_mv_renameat_dir_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.mv.renameat.dir.ma/");
    mkdir(path_dir, 0700);
    
    char* path = misc_concat(path_dir, "orig");
    char* path_new = misc_concat(path_dir, "renamed");
    mkdir(path, 0700);
    misc_nanosleep(ns_after_open);
    
    struct stat_macb* file_stat_before = get_path_timestamps(path);
    
    renameat((int) AT_FDCWD, path, (int) AT_FDCWD, path_new);
    
    struct stat_macb* file_stat_after = get_path_timestamps(path_new);
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat_before->st_mtim), &(file_stat_after->st_mtim)) != 0 || misc_timespec_eq(&(file_stat_before->st_atim), &(file_stat_after->st_atim)) != 0) {
        log_warning(output_file, error_file, "%s - MC not kept", __func__);
        result = 2;
    }
    
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, result, NULL, NULL, file_stat_before, "before");
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, result, NULL, NULL, file_stat_after, "after");
    
    free(path);
    free(path_new);
    free(file_stat_before);
    free(file_stat_after);
    
    return result;
}

int check_interfaces_file_mv_renameat_dir_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.mv.renameat.dir.dir/");
    mkdir(path_dir, 0700);
    
    char* path = misc_concat(path_dir, "orig");
    char* path_new = misc_concat(path_dir, "renamed");
    mkdir(path, 0700);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    renameat((int) AT_FDCWD, path,(int)  AT_FDCWD, path_new);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* dir_stat = get_path_timestamps(path_dir);
    
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, dir_stat);
    
    free(path);
    free(path_new);
    free(ts_before);
    free(ts_after);
    free(dir_stat);
    
    return result;
}


#endif
