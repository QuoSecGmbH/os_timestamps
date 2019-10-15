#ifndef I_FILE_LN_C
#define I_FILE_LN_C

#include "i_file_ln.h"

int check_interfaces_file_ln_link(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists_filled(dir_path, "interfaces.file.ln.link.orig", 5, s_0s, ns_after_open, output_file, error_file, __func__);
        
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char* path_link = misc_concat(dir_path, (char*) "interfaces.file.ln.link.link");
    
    int r = link(path, path_link);
    
    if (r != 0){
        log_warning(output_file, error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }

    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat* file_stat = get_path_timestamps(path_link);
    struct stat* dir_stat = get_path_timestamps(dir_path);
    
    int result_link = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    int result_dir = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, result_link, ts_before, ts_after, file_stat, "link");
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, result_dir, ts_before, ts_after, dir_stat, "dir");
    
    int result = misc_max2(result_link, result_dir);
    
    free(path);
    free(path_link);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_ln_linkat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists_filled(dir_path, "interfaces.file.ln.linkat.orig", 3, s_0s, ns_after_open, output_file, error_file, __func__);
    char* path_link = (char*) misc_concat(dir_path, "interfaces.file.ln.linkat.dir/interfaces.file.ln.linkat.link");
    
    int olddir_fd = open(dir_path, S_IRUSR);
    if (olddir_fd == 0){
        log_warning(output_file, error_file, "%s - %s: %d", __func__, "error opening olddir", errno);
        return 1;  
    }
    
    char* newdir_path = misc_concat(dir_path, "interfaces.file.ln.linkat.dir");
    int r1 = mkdirat(AT_FDCWD, newdir_path, S_IRWXU | S_IRWXG);
    if (r1 != 0){
        log_warning(output_file, error_file, "%s - %s %s: %d", __func__, "error creating dir", newdir_path, errno);
        return 1;
    }
    
    int newdir_fd = open(newdir_path, S_IRUSR);
    if (newdir_fd == 0){
        log_warning(output_file, error_file, "%s - %s: %d", __func__, "error opening newdir at %s", errno, newdir_path);
        return 1;  
    }
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();

    int r2 = linkat(olddir_fd, "interfaces.file.ln.linkat.orig", newdir_fd, "interfaces.file.ln.linkat.link", 0);
    if (r2 != 0){
        log_warning(output_file, error_file, "%s - %s: %d", __func__, "error creating link", errno);
        return 1;
    }

    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat* file_stat = get_path_timestamps(path_link);
    struct stat* dir_stat = get_path_timestamps(newdir_path);
    
    int result_link = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    int result_dir = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, result_link, ts_before, ts_after, file_stat, "link");
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, result_dir, ts_before, ts_after, dir_stat, "dir");
    
    int result = misc_max2(result_link, result_dir);
    
    free(path);
    free(path_link);
    free(newdir_path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_ln_symlink(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists_filled(dir_path, "interfaces.file.ln.symlink.orig", 5, s_0s, ns_after_open, output_file, error_file, __func__);
    char* path_link = misc_concat(dir_path, (char*) "interfaces.file.ln.symlink.link");

    struct timespec* ts_before = current_time_ns_fslike_osspecific();

    int r = symlink("interfaces.file.ln.symlink.orig", path_link);
    if (r != 0){
        log_warning(output_file, error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }

    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat* file_stat = get_path_timestamps_lstat(path_link);
    struct stat* dir_stat = get_path_timestamps(dir_path);
    
    int result_link = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    int result_dir = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, result_link, ts_before, ts_after, file_stat, "link");
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, result_dir, ts_before, ts_after, dir_stat, "dir");
    
    int result = misc_max2(result_link, result_dir);
    
    free(path);
    free(path_link);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_ln_symlinkat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists_filled(dir_path, "interfaces.file.ln.symlinkat.orig", 3, s_0s, ns_after_open, output_file, error_file, __func__);
    char* path_link = (char*) misc_concat(dir_path, "interfaces.file.ln.symlinkat.dir/interfaces.file.ln.symlinkat.link");
    
    int olddir_fd = open(dir_path, S_IRUSR);
    if (olddir_fd == 0){
        log_warning(output_file, error_file, "%s - %s: %d", __func__, "error opening olddir", errno);
        return 1;  
    }
    
    char* newdir_path = misc_concat(dir_path, "interfaces.file.ln.symlinkat.dir");
    int r1 = mkdirat(AT_FDCWD, newdir_path, S_IRWXU | S_IRWXG);
    if (r1 != 0){
        log_warning(output_file, error_file, "%s - %s %s: %d", __func__, "error creating dir", newdir_path, errno);
        return 1;
    }
    
    int newdir_fd = open(newdir_path, S_IRUSR);
    if (newdir_fd == 0){
        log_warning(output_file, error_file, "%s - %s: %d", __func__, "error opening newdir at %s", errno, newdir_path);
        return 1;  
    }
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();

    int r2 = symlinkat("../interfaces.file.ln.symlinkat.orig", newdir_fd, "interfaces.file.ln.symlinkat.link");
    if (r2 != 0){
        log_warning(output_file, error_file, "%s - %s: %d", __func__, "error creating link", errno);
        return 1;
    }

    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat* file_stat = get_path_timestamps_lstat(path_link);
    struct stat* dir_stat = get_path_timestamps(newdir_path);
    
    int result_link = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    int result_dir = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, result_link, ts_before, ts_after, file_stat, "link");
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, result_dir, ts_before, ts_after, dir_stat, "dir");
    
    int result = misc_max2(result_link, result_dir);
    
    free(path);
    free(path_link);
    free(newdir_path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_ln_readlink(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists_filled(dir_path, "interfaces.file.ln.readlink.orig", 5, s_0s, ns_after_open, output_file, error_file, __func__);
    char* relpath_link = "interfaces.file.ln.readlink.link";
    char* path_link = misc_concat(dir_path, relpath_link);

    int r = symlink("interfaces.file.ln.readlink.orig", path_link);
    if (r != 0){
        log_warning(output_file, error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    enum { BUFFERSIZE = 1024 };
    char buf_link[BUFFERSIZE];
    ssize_t len = readlink(path_link, buf_link, sizeof(buf_link)-1);

    if (len != -1) {
        buf_link[len] = '\0';
        log_info(output_file, error_file, "%s - %s %s", __func__, "readlink read", buf_link);
    }  
    else {
        log_warning(output_file, error_file, "%s - %s: %d", __func__, "error reading symlink", errno);
    }

    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat* file_stat = get_path_timestamps_lstat(path_link);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, UPDATE_MANDATORY, NOUPDATE_OPTIONAL, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, result, ts_before, ts_after, file_stat, "link");
    
    free(path);
    free(path_link);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_interfaces_file_ln_readlinkat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists_filled(dir_path, "interfaces.file.ln.readlinkat.orig", 3, s_0s, ns_after_open, output_file, error_file, __func__);
    char* path_link = (char*) misc_concat(dir_path, "interfaces.file.ln.readlinkat.dir/interfaces.file.ln.readlinkat.link");
    
    int olddir_fd = open(dir_path, S_IRUSR);
    if (olddir_fd == 0){
        log_warning(output_file, error_file, "%s - %s: %d", __func__, "error opening olddir", errno);
        return 1;  
    }
    
    char* newdir_path = misc_concat(dir_path, "interfaces.file.ln.readlinkat.dir");
    int r1 = mkdirat(AT_FDCWD, newdir_path, S_IRWXU | S_IRWXG);
    if (r1 != 0){
        log_warning(output_file, error_file, "%s - %s %s: %d", __func__, "error creating dir", newdir_path, errno);
        return 1;
    }
    
    int newdir_fd = open(newdir_path, S_IRUSR);
    if (newdir_fd == 0){
        log_warning(output_file, error_file, "%s - %s: %d", __func__, "error opening newdir at %s", errno, newdir_path);
        return 1;  
    }
    
    int r2 = symlinkat("../interfaces.file.ln.readlinkat.orig", newdir_fd, "interfaces.file.ln.readlinkat.link");
    if (r2 != 0){
        log_warning(output_file, error_file, "%s - %s: %d", __func__, "error creating link", errno);
        return 1;
    }
    misc_nanosleep(ns_after_open);

    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    enum { BUFFERSIZE = 1024 };
    char buf_link[BUFFERSIZE];
    ssize_t len = readlinkat(newdir_fd, "interfaces.file.ln.readlinkat.link", buf_link, sizeof(buf_link)-1);

    if (len != -1) {
        buf_link[len] = '\0';
        log_info(output_file, error_file, "%s - %s %s", __func__, "readlink read", buf_link);
    }  
    else {
        log_warning(output_file, error_file, "%s - %s: %d", __func__, "error reading symlink", errno);
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat* file_stat = get_path_timestamps_lstat(path_link);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, UPDATE_MANDATORY, NOUPDATE_OPTIONAL, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, result, ts_before, ts_after, file_stat, "link");
    
    free(path);
    free(path_link);
    free(newdir_path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

#endif
