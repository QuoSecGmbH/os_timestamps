#ifndef RUN_TESTS_C
#define RUN_TESTS_C

#include "run_tests.h"

char* POSIX_c181 = "POSIX_c181";


int main (int argc, char **argv){
    if (argc >= 2){
        VERBOSE=1;
    }
  
    FILE* csv_file = log_open_csv("results.csv");
    FILE* output_file = stdout;
    FILE* error_file = stderr;
  
    int i;
    char* dir_base_path = "tmp_tests";
    char* dir_path = NULL;
    for (i = 0; i <= 100; i++){
        char* buf = (char*) calloc(sizeof(char), strlen(dir_base_path)+6);
        sprintf(buf, "%s_%03d/", dir_base_path, i);
        struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
        if (stat(buf, attr) == -1) {
            mkdir(buf, 0700);
            dir_path = buf;
            break;
        }
    }
    
    if (dir_path == NULL){
        log_error(output_file, error_file, "%s", "Impossible to find suitable directory for tests, exiting.");
        return 1;
    }
    log_info(output_file, error_file, "Directory for tests is: %s", dir_path);
    
    struct timespec* ts_ns = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_ns->tv_sec = 0;
    ts_ns->tv_nsec = 10000000; // 10ms:smaller i / 10**i makes a difference with nanosleep + file write + *stat*
    
    log_csv_add_line(csv_file, 6, "Passed?", "Description", "Specified?", "Spec", "Ref", "Function");
    group_check_general_clock(csv_file, output_file, error_file);
    group_check_general_new_file(csv_file, output_file, error_file, dir_path);
    nanosleep(ts_ns, NULL);
    group_check_general_update(csv_file, output_file, error_file, dir_path);

    log_close_csv(csv_file);
}

void group_check_general_clock(FILE* csv_file, FILE* output_file, FILE* error_file){
    int result;
    
    result = check_general_clock_res(csv_file, output_file, error_file);
    log_csv_add_result(csv_file, output_file, error_file, result, "Clock resolution shall be at max 0.02s (CLOCK_REALTIME)", "Yes", POSIX_c181, "GENERAL.CLOCK.RES", "check_general_clock_res");
    result = check_general_clock_increments(csv_file, output_file, error_file);
    log_csv_add_result(csv_file, output_file, error_file, result, "Clock is incremental (increasing)", "No", "", "GENERAL.CLOCK.INCREMENTS", "check_general_clock_increments");
}

void group_check_general_new_file(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    int result;
    
    result = check_general_new_file_realtime(csv_file, output_file, error_file, dir_path);
    log_csv_add_result(csv_file, output_file, error_file, result, "New file shall have MAC updated (CLOCK_REALTIME)", "No", "", "GENERAL.NEW_FILE_REALTIME", "check_general_new_file_realtime");
    result = check_general_new_file(csv_file, output_file, error_file, dir_path);
    log_csv_add_result(csv_file, output_file, error_file, result, "New file shall have MAC updated", "Yes", POSIX_c181, "GENERAL.NEW_FILE", "check_general_new_file");
    result = check_general_new_file_mac_eq(csv_file, output_file, error_file, dir_path);
    log_csv_add_result(csv_file, output_file, error_file, result, "New file shall have MAC set to same value", "No", "", "GENERAL.NEW_FILE.MAC_eq", "check_general_new_file_mac_eq");
}


void group_check_general_update(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    int result;
    struct timespec* ts_ns = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_ns->tv_sec = 0;
    ts_ns->tv_nsec = 10000000; // 10ms: smaller i / 10**i makes a difference with nanosleep + file write + *stat*
    
    result = check_general_update_write_close(csv_file, output_file, error_file, dir_path);
    log_csv_add_result(csv_file, output_file, error_file, result, "(1) fwrite+fclose shall update MC", "Yes", POSIX_c181, "GENERAL.UPDATE.WRITE_CLOSE", "check_general_update_write_close");
    nanosleep(ts_ns, NULL);
    result = check_general_update_write_close(csv_file, output_file, error_file, dir_path);
    log_csv_add_result(csv_file, output_file, error_file, result, "(2) fwrite+fclose shall update MC", "Yes", POSIX_c181, "GENERAL.UPDATE.WRITE_CLOSE", "check_general_update_write_close");
    
    nanosleep(ts_ns, NULL);
    result = check_general_update_read_close(csv_file, output_file, error_file, dir_path);
    log_csv_add_result(csv_file, output_file, error_file, result, "(1) fread+fclose shall update A", "Yes", POSIX_c181, "GENERAL.UPDATE.READ_CLOSE", "check_general_update_read_close");
    nanosleep(ts_ns, NULL);
    result = check_general_update_read_close(csv_file, output_file, error_file, dir_path);
    log_csv_add_result(csv_file, output_file, error_file, result, "(2) fread+fclose shall update A", "Yes", POSIX_c181, "GENERAL.UPDATE.READ_CLOSE", "check_general_update_read_close");
    nanosleep(ts_ns, NULL);
    
    result = check_general_update_write_stat(csv_file, output_file, error_file, dir_path);
    log_csv_add_result(csv_file, output_file, error_file, result, "fwrite+fstat shall update MC", "Yes", POSIX_c181, "GENERAL.UPDATE.WRITE_STAT", "check_general_update_write_stat");
    nanosleep(ts_ns, NULL);
    result = check_general_update_read_stat(csv_file, output_file, error_file, dir_path);
    log_csv_add_result(csv_file, output_file, error_file, result, "fread+fstat shall update A", "Yes", POSIX_c181, "GENERAL.UPDATE.READ_STAT", "check_general_update_read_stat");
    nanosleep(ts_ns, NULL);
    
    result = check_general_update_chmod(csv_file, output_file, error_file, dir_path);
    log_csv_add_result(csv_file, output_file, error_file, result, "chmod shall update C", "Yes", POSIX_c181, "GENERAL.UPDATE.CHMOD", "check_general_update_chmod");
}

#endif
