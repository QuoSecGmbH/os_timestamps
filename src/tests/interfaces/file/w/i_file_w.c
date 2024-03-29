#ifndef I_FILE_W_C
#define I_FILE_W_C

#include "i_file_w.h"

int check_interfaces_file_w_dprintf(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, __func__ , s_0s, ns_0ns, output_file, error_file, __func__);
    
//     FILE* fd = fopen(path, "wb");
    int fd = open(path, O_WRONLY);
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    misc_nanosleep(ns_DELAY);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    dprintf(fd, "%s\n", "dprintf test");
    
    struct stat_macb* file_stat = get_path_timestamps(path);
    // Mark for update
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    close(fd);
//     fclose(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_w_ftruncate(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, __func__ , s_0s, ns_0ns, output_file, error_file, __func__);
    
    FILE* f = fopen(path, "wb");
    if (f == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    char buf[20] = "fwrite test";
    fwrite(buf, 1, 12, f);
    fclose(f);
    
    int fd = open(path, O_WRONLY|O_RDONLY);
    if (fd == 0) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_DELAY);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    ftruncate(fd, 3);
    
    struct stat_macb* file_stat = get_path_timestamps(path);
    // Mark for update
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    close(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_w_write_imm(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, __func__ , s_0s, ns_0ns, output_file, error_file, __func__);
    
    int fd = open(path, O_WRONLY|O_RDONLY);
    if (fd == 0) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_DELAY);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char buf[20] = "write test";
    write(fd, buf, 11);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    close(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_w_write(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, __func__ , s_0s, ns_0ns, output_file, error_file, __func__);
    
    int fd = open(path, O_WRONLY|O_RDONLY);
    if (fd == 0) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_DELAY);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char buf[20] = "write test";
    write(fd, buf, 11);
    
    struct stat_macb* file_stat = get_path_timestamps(path);
    // Mark for update
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    close(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_w_write_zero(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, __func__ , s_0s, ns_0ns, output_file, error_file, __func__);
    
    int fd = open(path, O_WRONLY|O_RDONLY);
    if (fd == 0) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_DELAY);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char buf[20] = "write test";
    write(fd, buf, 0);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    close(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}


#endif
