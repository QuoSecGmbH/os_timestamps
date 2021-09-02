#ifndef I_FILE_W_FPUTWC_C
#define I_FILE_W_FPUTWC_C

#include "i_file_w_fputwc.h"

int check_interfaces_file_w_fputwc_fflush_imm(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, __func__ , s_0s, ns_0ns, output_file, error_file, __func__);

    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_DELAY);
        
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    fputwc(L"C", fd); // 0x3f = 63
    fflush(fd);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    fclose(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_w_fputwc_fflush(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, __func__ , s_0s, ns_0ns, output_file, error_file, __func__);

    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_DELAY);
        
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    fputwc(L"CC", fd); // 0x3f = 63
    fflush(fd);
    
    struct stat_macb* file_stat = get_path_timestamps(path);
    // Mark for update
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    fclose(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_w_fputwc_fclose(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, __func__ , s_0s, ns_0ns, output_file, error_file, __func__);

    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_DELAY);
        
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    fputwc(L"C", fd); // 0x3f = 63
    fclose(fd);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_w_fputwc_exit(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, __func__ , s_0s, ns_0ns, output_file, error_file, __func__);
    
    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    // Flushing to prevent output duplication on child abort (FreeBSD)
    fflush(csv_file);
    fflush(output_file);
    fflush(error_file);
    fflush(stdout);
    fflush(stderr);
    
    misc_nanosleep(ns_DELAY);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    pid_t child_pid = fork();
    if (child_pid == 0) {
        // Child code
        fputwc(L"C", fd); // 0x3f = 63
        _exit(0);
    }
    
    int wstatus;    
    if (waitpid(child_pid, &wstatus, 0) == -1) {
            log_error(output_file, error_file, "%s - waitpid failed with errno %d", __func__, errno);
    }
    else {
        if (WIFEXITED(wstatus)){
            if (WEXITSTATUS(wstatus) != 0){
                int exitstatus = WEXITSTATUS(wstatus);
                log_error(output_file, error_file, "%s - waitpid unexpected exit status: %d\n", __func__, exitstatus); 
            }
        }
        else {        
            log_error(output_file, error_file, "%s - childpid exited not normally", __func__);
        }
    }

    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_w_fputwc_abort(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, __func__ , s_0s, ns_0ns, output_file, error_file, __func__);
    
    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    // Flushing to prevent output duplication on child abort (FreeBSD)
    fflush(csv_file);
    fflush(output_file);
    fflush(error_file);
    fflush(stdout);
    fflush(stderr);
    
    misc_nanosleep(ns_DELAY);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    pid_t child_pid = fork();
    if (child_pid == 0) {
        // Child code
        fputwc(L"C", fd); // 0x3f = 63
        abort();
    }
    
    int wstatus;    
    if (waitpid(child_pid, &wstatus, 0) == -1) {
            log_error(output_file, error_file, "%s - waitpid failed with errno %d", __func__, errno);
    }
    else {
        if (WIFEXITED(wstatus)){
            if (WEXITSTATUS(wstatus) != 0){
                int exitstatus = WEXITSTATUS(wstatus);
                log_error(output_file, error_file, "%s - waitpid unexpected exit status: %d\n", __func__, exitstatus); 
            }
        }
    }

    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}





#endif
