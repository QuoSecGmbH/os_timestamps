#ifndef I_FILE_R_GETS_C
#define I_FILE_R_GETS_C

#include "i_file_r_gets.h"

#ifndef __OpenBSD__
int check_interfaces_file_r_gets(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    FILE* f = stdin;
    if (f == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    printf("Input one char: B - WARNING inputing more than 20 char will cause memory corruption (gets)\nInput:");
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char* buf = (char*) calloc(21, sizeof(char));
    char* s = (char*) (intptr_t) gets(buf);
    
    if (s == NULL){
        log_warning(output_file, error_file, "%s - %s", __func__, "could not read data from file");
        return 1;
    }
    
    if (buf[0] != 0x42){
        log_warning(output_file, error_file, "%s - %s but %d", __func__, "read a wrong input (not B / 0x42)", buf[0]);
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


int check_interfaces_file_r_gets_ungetc(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    FILE* f = stdin;
    if (f == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    ungetc(0x0a, f);
    ungetc(0x41, f);
    misc_nanosleep(ns_after_open); 
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char* buf = (char*) calloc(21, sizeof(char));
    char* s = (char*) (intptr_t) gets(buf);
    
    if (s == NULL){
        log_warning(output_file, error_file, "%s - %s", __func__, "could not read data from file");
        return 1;
    }
    
    if (buf[0] != 0x41){
        log_warning(output_file, error_file, "%s - %s", __func__, "read a different int than the one ungetc provided");
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_file_timestamps(f);
      
    int result = result_MAC_updated(NOUPDATE_MANDATORY, UPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(buf);
    
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_r_gets_ungetc_both(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    FILE* f = stdin;
    if (f == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    ungetc(0x0a, f);
    ungetc(0x41, f);
    
    printf("Input one char: B - WARNING inputing more than 20 char will cause memory corruption (gets)\nInput:");
    
    misc_nanosleep(ns_after_open); 
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char* buf1 = (char*) calloc(21, sizeof(char));
    char* buf2 = (char*) calloc(21, sizeof(char));
    char* s1 = (char*) (intptr_t) gets(buf1);
    char* s2 = (char*) (intptr_t) gets(buf2);
    
    if (s1 == NULL || s2 == NULL){
        log_warning(output_file, error_file, "%s - %s", __func__, "could not read data from file");
        return 1;
    }
    
    if (buf1[0] != 0x41){
        log_warning(output_file, error_file, "%s - %s: %d", __func__, "read a different int than the one ungetc provided", buf1[0]);
        return 1;
    }
    
    if (buf2[0] != 0x42){
        log_warning(output_file, error_file, "%s - %s but %d", __func__, "read a wrong input (not B / 0x42)", buf2[0]);
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_file_timestamps(f);
      
    int result = result_MAC_updated(NOUPDATE_MANDATORY, UPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(buf1);
    free(buf2);
    
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}
#endif

#endif
