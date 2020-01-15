#ifndef I_FILE_W_WPRINTF_C
#define I_FILE_W_WPRINTF_C

#include "i_file_w_wprintf.h"

int check_interfaces_file_w_wprintf_fflush(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    FILE* f = stdout;
    if (f == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    wprintf(L"%s\n", "fwprintf test");
    fflush(f);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat_macb* file_stat = get_file_timestamps(f);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

// int check_interfaces_file_w_wprintf_fclose(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
//     char* path = (char*) misc_concat_ensure_file_exists(dir_path, "interfaces.file.w.wprintf_fclose" , s_0s, ns_100ms, output_file, error_file, __func__);
//     
//     struct timespec* ts_before = current_time_ns_fslike_osspecific();
//     
//     FILE* f = stdout;
//     if (fd == NULL) {
//         log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
//         return 1;
//     }
//     
//     wprintf(L"%s\n", "fwprintf test");
//     fclose(f);
//     
//     struct timespec* ts_after = current_time_ns_fslike_osspecific();
//     struct stat_macb* file_stat = get_path_timestamps(path);
//       
//     int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
//     log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
//     
//     fopen(stdout);
//     
//     return result; 
// }

int check_interfaces_file_w_wprintf_exit(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    // Flushing to prevent output duplication on child abort (FreeBSD)
    fflush(csv_file);
    fflush(output_file);
    fflush(error_file);
    fflush(stdout);
    fflush(stderr);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    FILE* f = stdout;
    pid_t child_pid = fork();
    if (child_pid == 0) {
        // Child code
        if (f == NULL) {
            log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
            return 1;
        }
        
        wprintf(L"%s\n", "wprintf test");
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
    struct stat_macb* file_stat = get_file_timestamps(f);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_w_wprintf_abort(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){    
    // Flushing to prevent output duplication on child abort (FreeBSD)
    fflush(csv_file);
    fflush(output_file);
    fflush(error_file);
    fflush(stdout);
    fflush(stderr);
    
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    FILE* f = stdout;
    pid_t child_pid = fork();
    if (child_pid == 0) {
        // Child code
        if (f == NULL) {
            log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
            return 1;
        }
        
        wprintf(L"%s\n", "wprintf test");
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
    struct stat_macb* file_stat = get_file_timestamps(f);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}





#endif
