#ifndef I_FILE_NEW_C
#define I_FILE_NEW_C

#include "i_file_r.h"

int check_interfaces_file_new_mkdtemp_new(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char* template = misc_concat(dir_path, (char*) "interfaces.files.new.mkdtemp.new.XXXXXX");
    char* path_dir = mkdtemp(template);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_path_timestamps(path_dir);
    
    int result = result_MAC_updated(UPDATE_MANDATORY, UPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(template);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_interfaces_file_new_mkdtemp_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* template = misc_concat(dir_path, (char*) "interfaces.files.new.mkdtemp.new.XXXXXX");
    char* path_dir = mkdtemp(template);
    
    struct stat* file_stat = get_path_timestamps(path_dir);
    int result = 0;
    if (misc_timespec_eq(&(file_stat->st_mtim), &(file_stat->st_atim)) != 0 || misc_timespec_eq(&(file_stat->st_atim), &(file_stat->st_ctim)) != 0){
        log_warning(output_file, error_file, "check_interfaces_file_new_mkdtemp_mac - MAC not equal");
        result = 2;
    }
    
    free(template);
    free(file_stat);
    
    return result;
}

#endif
