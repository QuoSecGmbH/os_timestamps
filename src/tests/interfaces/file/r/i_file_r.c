#ifndef I_FILE_R_C
#define I_FILE_R_C

#include "i_file_r.h"

int check_interfaces_file_r_read(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists_filled(dir_path, "interfaces.file.r.read", 10, s_0s, ns_100ms, output_file, error_file, __func__);
    
    int fd = open(path, O_RDONLY);
    if (fd == 0) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char* buf = (char*) calloc(3, sizeof(char));
    read(fd, buf, 2);
        
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, UPDATE_MANDATORY, NOUPDATE_OPTIONAL, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(buf);
    close(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_r_read_zero(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists_filled(dir_path, "interfaces.file.r.read", 10, s_0s, ns_100ms, output_file, error_file, __func__);
    
    int fd = open(path, O_RDONLY);
    if (fd == 0) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char* buf = (char*) calloc(3, sizeof(char));
    read(fd, buf, 0);
        
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(buf);
    close(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_r_pread(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists_filled(dir_path, "interfaces.file.r.read", 10, s_0s, ns_100ms, output_file, error_file, __func__);
    
    int fd = open(path, O_RDONLY);
    if (fd == 0) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char* buf = (char*) calloc(3, sizeof(char));
    pread(fd, buf, 2, 1);
        
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, UPDATE_MANDATORY, NOUPDATE_OPTIONAL, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(buf);
    close(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_r_pread_zero(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists_filled(dir_path, "interfaces.file.r.read", 10, s_0s, ns_100ms, output_file, error_file, __func__);
    
    int fd = open(path, O_RDONLY);
    if (fd == 0) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char* buf = (char*) calloc(3, sizeof(char));
    pread(fd, buf, 0, 1);
        
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(buf);
    close(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

#endif
