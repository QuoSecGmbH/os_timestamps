#ifndef I_FILE_R_GETCHAR_C
#define I_FILE_R_GETCHAR_C

#include "i_file_r_getchar.h"

int check_interfaces_file_r_getchar(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    FILE* f = stdin;
    if (f == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    printf("Input one char: B\nInput:");
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    int gotten = getchar();
    getchar(); // discard 0x0a (newline)
    
    if (gotten == 0){
        log_warning(output_file, error_file, "%s - %s", __func__, "could not read data from file");
        return 1;
    }
    
    if (gotten != 0x42){
        log_warning(output_file, error_file, "%s - %s but %d", __func__, "read a wrong input (not B / 0x42)", gotten);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_file_timestamps(f);
      
    int result = result_MAC_updated(NOUPDATE_MANDATORY, UPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}


int check_interfaces_file_r_getchar_ungetc(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    FILE* f = stdin;
    if (f == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    ungetc(0x41, f);
    misc_nanosleep(ns_after_open); 
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    int gotten = getchar();
    
    if (gotten == 0){
        log_warning(output_file, error_file, "%s - %s", __func__, "could not read data from file");
        return 1;
    }
    
    if (gotten != 0x41){
        log_warning(output_file, error_file, "%s - %s", __func__, "read a different int than the one ungetc provided");
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_file_timestamps(f);
      
    int result = result_MAC_updated(NOUPDATE_MANDATORY, UPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_r_getchar_ungetc_both(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    FILE* f = stdin;
    if (f == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    ungetc(0x41, f);
    
    printf("Input one char: B\nInput:");
    
    misc_nanosleep(ns_after_open); 
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    int gotten1 = getchar();
    int gotten2 = getchar();
    getchar(); // discard 0x0a (newline)
    
    if (gotten1 == 0 || gotten2 == 0){
        log_warning(output_file, error_file, "%s - %s", __func__, "could not read data from file");
        return 1;
    }
    
    if (gotten1 != 0x41){
        log_warning(output_file, error_file, "%s - %s: %d", __func__, "read a different int than the one ungetc provided", gotten1);
        return 1;
    }
    
    if (gotten2 != 0x42){
        log_warning(output_file, error_file, "%s - %s but %d", __func__, "read a wrong input (not B / 0x42)", gotten2);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_file_timestamps(f);
      
    int result = result_MAC_updated(NOUPDATE_MANDATORY, UPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

#endif
