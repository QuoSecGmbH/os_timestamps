#ifndef I_FILE_R_GETLINE_C
#define I_FILE_R_GETLINE_C

#include "i_file_r_getline.h"

int check_interfaces_file_r_getline(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists_filled(dir_path, "interfaces.file.r.getline", 10, s_0s, ns_100ms, output_file, error_file, __func__);
    
    FILE* fd = fopen(path, "rb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_after_open); 
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char *line = NULL;
    size_t len = 0;
    int n_read = getline(&line, &len, fd);
    
    if (n_read <= 2){
        log_warning(output_file, error_file, "%s - %s", __func__, "could not read data from file");
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat_macb* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(NOUPDATE_MANDATORY, UPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    fclose(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}


int check_interfaces_file_r_getline_ungetc(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists_filled(dir_path, "interfaces.file.r.getline.ungetc", 10, s_0s, ns_100ms, output_file, error_file, __func__);
    
    FILE* fd = fopen(path, "rb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    ungetc(0x0a, fd);
    ungetc(0x41, fd);
    misc_nanosleep(ns_after_open); 
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char *line = NULL;
    size_t len = 0;
    int n_read = getline(&line, &len, fd);
    
    if (n_read < 1){
        log_warning(output_file, error_file, "%s - %s", __func__, "could not read data from file");
        return 1;
    }
    
    if (line[0] != 0x41){
        log_warning(output_file, error_file, "%s - %s", __func__, "read a different int than the one ungetc provided");
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat_macb* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(NOUPDATE_MANDATORY, UPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    fclose(fd);
    
    free(line);
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_r_getline_ungetc_both(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists_filled(dir_path, "interfaces.file.r.getline.ungetc.both", 10, s_0s, ns_100ms, output_file, error_file, __func__);
    
    FILE* fd = fopen(path, "rb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    ungetc(0x0a, fd);
    ungetc(0x41, fd);
    misc_nanosleep(ns_after_open); 
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char *line1 = NULL;
    size_t len1 = 0;
    int n_read1 = getline(&line1, &len1, fd);
    
    char *line2 = NULL;
    size_t len2 = 0;
    int n_read2 = getline(&line2, &len2, fd);
    
    if (n_read1 < 1 || n_read2 < 1){
        log_warning(output_file, error_file, "%s - %s", __func__, "could not read data from file");
        return 1;
    }
    
    if (line1[0] != 0x41){
        log_warning(output_file, error_file, "%s - %s", __func__, "read a different int than the one ungetc provided");
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat_macb* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(NOUPDATE_MANDATORY, UPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    fclose(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

#endif
