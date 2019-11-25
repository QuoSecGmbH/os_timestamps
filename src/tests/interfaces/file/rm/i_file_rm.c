#ifndef I_FILE_RM_C
#define I_FILE_RM_C

#include "i_file_rm.h"

int check_interfaces_file_rm_unlink_last_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.rm.unlink.last.dir/");
    mkdir(path_dir, 0700);
    
    char* path = (char*) misc_concat_ensure_file_exists(path_dir, "file", s_0s, ns_0ns, output_file, error_file, __func__);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    unlink(path);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* dir_stat = get_path_timestamps(path_dir);
    
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, dir_stat);
    
    free(path);
    free(path_dir);
    free(ts_before);
    free(ts_after);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_rm_unlink_notlast_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.rm.unlink.notlast.dir/");
    mkdir(path_dir, 0700);
    
    char* path = (char*) misc_concat_ensure_file_exists(path_dir, "file", s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_link = (char*) misc_concat(path_dir, "file_link");
    link(path, path_link);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    unlink(path_link);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* dir_stat = get_path_timestamps(path_dir);
    
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, dir_stat);
    
    free(path);
    free(path_link);
    free(path_dir);
    free(ts_before);
    free(ts_after);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_rm_unlink_notlast(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.rm.unlink.notlast/");
    mkdir(path_dir, 0700);
    
    char* path = (char*) misc_concat_ensure_file_exists(path_dir, "file", s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_link = (char*) misc_concat(path_dir, "file_link");
    link(path, path_link);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    unlink(path_link);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(path_link);
    free(path_dir);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_interfaces_file_rm_unlinkat_last_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.rm.unlinkat.last.dir/");
    mkdir(path_dir, 0700);
    
    char* path = (char*) misc_concat_ensure_file_exists(path_dir, "file", s_0s, ns_0ns, output_file, error_file, __func__);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    unlinkat((int) AT_FDCWD, path, 0);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* dir_stat = get_path_timestamps(path_dir);
    
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, dir_stat);
    
    free(path);
    free(path_dir);
    free(ts_before);
    free(ts_after);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_rm_unlinkat_notlast_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.rm.unlinkat.notlast.dir/");
    mkdir(path_dir, 0700);
    
    char* path = (char*) misc_concat_ensure_file_exists(path_dir, "file", s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_link = (char*) misc_concat(path_dir, "file_link");
    link(path, path_link);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    unlinkat((int) AT_FDCWD, path_link, 0);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* dir_stat = get_path_timestamps(path_dir);
    
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, dir_stat);
    
    free(path);
    free(path_link);
    free(path_dir);
    free(ts_before);
    free(ts_after);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_rm_unlinkat_notlast(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.rm.unlinkat.notlast/");
    mkdir(path_dir, 0700);
    
    char* path = (char*) misc_concat_ensure_file_exists(path_dir, "file", s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_link = (char*) misc_concat(path_dir, "file_link");
    link(path, path_link);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    unlinkat((int) AT_FDCWD, path_link, 0);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(path_link);
    free(path_dir);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_interfaces_file_rm_remove_dir_empty_parentdir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.rm.remove.dir.empty.parentdir/");
    mkdir(path_dir, 0700);
    
    char* path = (char*) misc_concat(path_dir, "dir/");
    mkdir(path, 0700);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    remove(path);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* dir_stat = get_path_timestamps(path_dir);
    
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, dir_stat);
    
    free(path);
    free(path_dir);
    free(ts_before);
    free(ts_after);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_rm_remove_dir_notempty_parentdir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.rm.remove.dir.notempty.parentdir/");
    mkdir(path_dir, 0700);
    
    char* path = (char*) misc_concat(path_dir, "dir/");
    mkdir(path, 0700);
    char* path_file = (char*) misc_concat_ensure_file_exists(path, "file", s_0s, ns_0ns, output_file, error_file, __func__);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    remove(path);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* dir_stat = get_path_timestamps(path_dir);
    
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, dir_stat);
    
    free(path);
    free(path_dir);
    free(path_file);
    free(ts_before);
    free(ts_after);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_rm_remove_dir_notempty(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.rm.remove.dir.notempty/");
    mkdir(path_dir, 0700);
    
    char* path = (char*) misc_concat_ensure_file_exists(path_dir, "file", s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_link = (char*) misc_concat(path_dir, "file_link");
    link(path, path_link);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    remove(path_link);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(path_link);
    free(path_dir);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_interfaces_file_rm_remove_file_last_parentdir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.rm.remove.file.last.parentdir/");
    mkdir(path_dir, 0700);
    
    char* path = (char*) misc_concat_ensure_file_exists(path_dir, "file", s_0s, ns_0ns, output_file, error_file, __func__);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    remove(path);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* dir_stat = get_path_timestamps(path_dir);
    
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, dir_stat);
    
    free(path);
    free(path_dir);
    free(ts_before);
    free(ts_after);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_rm_remove_file_notlast_parentdir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.rm.remove.file.notlast.parentdir/");
    mkdir(path_dir, 0700);
    
    char* path = (char*) misc_concat_ensure_file_exists(path_dir, "file", s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_link = (char*) misc_concat(path_dir, "file_link");
    link(path, path_link);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    remove(path);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* dir_stat = get_path_timestamps(path_dir);
    
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, dir_stat);
    
    free(path);
    free(path_dir);
    free(path_link);
    free(ts_before);
    free(ts_after);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_rm_remove_file_notlast(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.rm.remove.file.notlast/");
    mkdir(path_dir, 0700);
    
    char* path = (char*) misc_concat_ensure_file_exists(path_dir, "file", s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_link = (char*) misc_concat(path_dir, "file_link");
    link(path, path_link);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    unlink(path_link);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(path_link);
    free(path_dir);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_interfaces_file_rm_rmdir_empty_parentdir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.rm.rmdir.empty.parentdir/");
    mkdir(path_dir, 0700);
    
    char* path = (char*) misc_concat(path_dir, "dir/");
    mkdir(path, 0700);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    rmdir(path);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* dir_stat = get_path_timestamps(path_dir);
    
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, dir_stat);
    
    free(path);
    free(path_dir);
    free(ts_before);
    free(ts_after);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_rm_rmdir_notempty_parentdir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.rm.rmdir.notempty.parentdir/");
    mkdir(path_dir, 0700);
    
    char* path = (char*) misc_concat(path_dir, "dir/");
    mkdir(path, 0700);
    char* path_file = (char*) misc_concat_ensure_file_exists(path, "file", s_0s, ns_0ns, output_file, error_file, __func__);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    rmdir(path);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* dir_stat = get_path_timestamps(path_dir);
    
    int result = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_OPTIONAL, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, dir_stat);
    
    free(path);
    free(path_dir);
    free(path_file);
    free(ts_before);
    free(ts_after);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_rm_rmdir_notempty(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.file.rm.rmdir.notempty/");
    mkdir(path_dir, 0700);
    
    char* path = (char*) misc_concat_ensure_file_exists(path_dir, "file", s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_link = (char*) misc_concat(path_dir, "file_link");
    link(path, path_link);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    rmdir(path_link);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(path_link);
    free(path_dir);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}


#endif
