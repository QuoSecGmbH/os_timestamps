#ifndef I_DIR_C
#define I_DIR_C

#include "i_dir.h"

int check_interfaces_dir_readdir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_dir_exists(dir_path, __func__, s_0s, ns_0ns, output_file, error_file, __func__);
    misc_concat_ensure_file_exists(path, "file", s_0s, ns_0ns, output_file, error_file, __func__);

    DIR *dp = opendir(path);
    if (dp == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening directory");
        return 1;
    }
    misc_nanosleep(ns_DELAY);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    readdir(dp);
        
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    closedir(dp);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, UPDATE_MANDATORY, NOUPDATE_OPTIONAL, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);

    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_dir_readdir_files(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_dir_exists(dir_path, __func__, s_0s, ns_0ns, output_file, error_file, __func__);
    char* file_path = misc_concat_ensure_file_exists(path, "file", s_0s, ns_0ns, output_file, error_file, __func__);

    DIR *dp = opendir(path);
    if (dp == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening directory");
        return 1;
    }
    struct dirent *de;   
    int first = 0;
    misc_nanosleep(ns_DELAY);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();

    while (de != NULL || first == 0){
        de = readdir(dp);
        first = 1;
    }
        
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(file_path);
    
    closedir(dp);
    
    int result = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);

    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_dir_readdir_r(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_dir_exists(dir_path, __func__, s_0s, ns_0ns, output_file, error_file, __func__);
    misc_concat_ensure_file_exists(path, "file", s_0s, ns_0ns, output_file, error_file, __func__);

    DIR *dp = opendir(path);
    if (dp == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening directory");
        return 1;
    }
    struct dirent* de1 = (struct dirent*) calloc(sizeof(struct dirent), 1);
    struct dirent** de2 = (struct dirent**) calloc(sizeof(struct dirent*), 1);
    misc_nanosleep(ns_DELAY);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    readdir_r(dp, de1, de2);
        
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    closedir(dp);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, UPDATE_MANDATORY, NOUPDATE_OPTIONAL, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);

    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_dir_readdir_r_files(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_dir_exists(dir_path, __func__, s_0s, ns_0ns, output_file, error_file, __func__);
    char* file_path = misc_concat_ensure_file_exists(path, "file", s_0s, ns_0ns, output_file, error_file, __func__);

    DIR *dp = opendir(path);
    if (dp == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening directory");
        return 1;
    }
    struct dirent *de1 = (struct dirent*) calloc(sizeof(struct dirent), 1);
    struct dirent **de2 = (struct dirent**) calloc(sizeof(struct dirent*), 1);
    int ret = 0;
    int first = 0;
    misc_nanosleep(ns_DELAY);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();

    while (ret == 0 && (*de2 != NULL || first == 0)){
        ret = readdir_r(dp, de1, de2);
        first = 1;
    }
        
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(file_path);
    
    closedir(dp);
    
    int result = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);

    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}


#endif
