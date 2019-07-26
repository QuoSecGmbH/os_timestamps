#ifndef I_FILE_W_C
#define I_FILE_W_C

#include "i_file.h"

// int helper_interfaces_file_w_FILE(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path, char* str_syscall1, void* syscall1, char* str_syscall2, void* syscall2){
//     char* path_generic = (char*) misc_concat(dir_path, misc_concat("interfaces.file.w.", str_syscall1));    
//     char* path = (char*) misc_concat_ensure_file_exists((char*) misc_concat(path_generic, "_"), str_syscall2, s_0s, ns_100ms, output_file, error_file, __func__);
//     
//     struct timespec* ts_before = current_time_ns_fslike_osspecific();
//     
//     FILE* fd = fopen(path_mode, mode);
//     if (fd == NULL) {
//         log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
//         return 1;
//     }
//     
//     
//     
//     struct timespec* ts_after = current_time_ns_fslike_osspecific();
//     struct stat* file_stat = get_path_timestamps(path_mode);
//     struct stat* dir_stat = get_path_timestamps(dir_path);
//       
//     int result_file = result_MAC_updated(UPDATE_MANDATORY, UPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
//     int result_dir = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
//     log_info_ts_stat_on_error(output_file, error_file, __func__, result_file, ts_before, ts_after, file_stat);
//     log_info_ts_stat_on_error(output_file, error_file, __func__, result_dir, ts_before, ts_after, dir_stat);
//     
//     fclose(fd);
//     
//     int result = misc_max2(result_file, result_dir);
//     return result; 
// }

int check_interfaces_file_w_dprintf(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.file.w.fprintf_fflush" , s_0s, ns_100ms, output_file, error_file, __func__);
    
    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_after_open);  
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    dprintf(fd, "%s\n", "dprintf test");
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    fclose(fd);
    
    return result; 
}

int check_interfaces_file_w_ftruncate(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.file.w.ftruncate" , s_0s, ns_0ns, output_file, error_file, __func__);
    
    FILE* f = fopen(path, "wb");
    if (f == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    char buf[20] = "fwrite test";
    fwrite(buf, 1, 12, f);
    fclose(f);
    
    int fd = open(path, O_WRONLY|O_RDONLY);
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_after_open); 
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    ftruncate(fd, 3);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    close(fd);
    
    return result; 
}

int check_interfaces_file_w_write(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.file.w.ftruncate" , s_0s, ns_0ns, output_file, error_file, __func__);
    
    int fd = open(path, O_WRONLY|O_RDONLY);
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_after_open); 
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char buf[20] = "write test";
    write(fd, buf, 11);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    close(fd);
    
    return result; 
}

int check_interfaces_file_w_write_zero(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.file.w.ftruncate" , s_0s, ns_0ns, output_file, error_file, __func__);
    
    int fd = open(path, O_WRONLY|O_RDONLY);
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_after_open); 
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char buf[20] = "write test";
    write(fd, buf, 0);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    close(fd);
    
    return result; 
}


#endif
