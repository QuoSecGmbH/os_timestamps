#ifndef I_FILE_R_WSCANF_C
#define I_FILE_R_WSCANF_C

#include "i_file_r_wscanf.h"

int check_interfaces_file_r_wscanf(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    FILE* f = stdin;
    if (f == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    printf("Input one char: B\nInput:");
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    wchar_t* buf = (wchar_t*) calloc(3, sizeof(wchar_t));
    int n_read = wscanf(L"%02ls", buf);
    
    if (n_read == 0){
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
    
    free(buf);
    
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}


int check_interfaces_file_r_wscanf_ungetc(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    FILE* f = stdin;
    if (f == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    ungetwc(L'\n', f);
    ungetwc(L'A', f);
    misc_nanosleep(ns_after_open); 
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    wchar_t* buf = (wchar_t*) calloc(3, sizeof(wchar_t));
    int n_read = wscanf("%02ls", buf);
    
    if (n_read == 0){
        log_warning(output_file, error_file, "%s - %s", __func__, "could not read data from file");
        return 1;
    }
    
    if (buf[0] != L'A'){
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

int check_interfaces_file_r_wscanf_ungetc_both(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    FILE* f = stdin;
    if (f == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    ungetwc(L'\n', f);
    ungetwc(L'A', f);
    
    printf("Input one char: B - WARNING inputing more than 20 char will cause memory corruption (wscanf)\nInput:");
    
    misc_nanosleep(ns_after_open); 
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    wchar_t* buf1 = (wchar_t*) calloc(3, sizeof(wchar_t));
    int n_read1 = wscanf("%02ls", buf1);
    
    wchar_t* buf2 = (wchar_t*) calloc(3, sizeof(wchar_t));
    int n_read2 = wscanf("%02ls", buf2);
    
    if (n_read1 == 0 || n_read2 == 0){
        log_warning(output_file, error_file, "%s - %s", __func__, "could not read data from file");
        return 1;
    }
    
    if (buf1[0] != L'A'){
        log_warning(output_file, error_file, "%s - %s: %d", __func__, "read a different int than the one ungetc provided", buf1[0]);
        return 1;
    }
    
    if (buf2[0] != L'B'){
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
