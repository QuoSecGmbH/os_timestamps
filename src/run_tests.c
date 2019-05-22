#ifndef RUN_TESTS_C
#define RUN_TESTS_C

#include "run_tests.h"

char* POSIX_c181 = "POSIX_c181";
long ns_10ms = 10000000; // 10ms: smaller i / 10**i makes a difference with nanosleep + file write + *stat*

int runtest(testenv_struct* env, char* ref, int repeat, long sleep_ns, int (*func)(FILE*, FILE*, FILE*, char*), char* func_name, char* spec, char* spec_name, char* desc){
    int result = 0;
    int newresult = 0;
    char* curr_ref;
    int i;
    
    struct timespec* ts_ns = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_ns->tv_sec = 0;
    ts_ns->tv_nsec = sleep_ns; 
    
    for (i=0; i<repeat; i++){
        if (repeat >= 2){
            curr_ref = (char*) calloc(strlen(ref)+20, 1);
            sprintf(curr_ref, "%s.%i", ref, i+1);
        }
        else {
            curr_ref = ref;
        }

        nanosleep(ts_ns, NULL);
        newresult = func(env->csv_file, env->output_file, env->error_file, env->dir_path);
        log_csv_add_result(env->csv_file, env->output_file, env->error_file, newresult, desc, spec, spec_name, curr_ref, func_name);
        
        if (newresult > result){
            result = newresult;
        }
    }
    
    return result;
}

testenv_struct* testenv_alloc(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  testenv_struct* env = (testenv_struct*) calloc(sizeof(testenv_struct), 1);
  env->csv_file = csv_file;
  env->output_file = output_file;
  env->error_file = error_file;
  env->dir_path = dir_path;
  return env;
}

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
    
    
    testenv_struct* test_env = testenv_alloc(csv_file, output_file, error_file, dir_path);
    
    log_csv_add_line(csv_file, 6, "Passed?", "Description", "Specified?", "Spec", "Ref", "Function");
    group_check_general_clock(test_env);
    group_check_general_new_file(test_env);
    group_check_general_update(test_env);

    log_close_csv(csv_file);
}

void group_check_general_clock(testenv_struct* env){
    runtest(env, "GENERAL.CLOCK.RES", 1, ns_10ms, check_general_clock_res, "check_general_clock_res", "Yes", POSIX_c181, "Clock resolution shall be at max 0.02s (CLOCK_REALTIME)");
    runtest(env, "GENERAL.CLOCK.INCREMENTS", 1, ns_10ms, check_general_clock_increments, "check_general_clock_increments", "No", "", "Clock is incremental (increasing)");
}

void group_check_general_new_file(testenv_struct* env){
    runtest(env, "GENERAL.NEW_FILE_REALTIME", 1, ns_10ms, check_general_new_file_realtime, "check_general_new_file_realtime", "No", "", "New file shall have MAC updated (CLOCK_REALTIME)");
    runtest(env, "GENERAL.NEW_FILE", 1, ns_10ms, check_general_new_file, "check_general_new_file", "Yes", POSIX_c181, "New file shall have MAC updated");
    runtest(env, "GENERAL.NEW_FILE.MAC_eq", 1, ns_10ms, check_general_new_file_mac_eq, "check_general_new_file_mac_eq", "No", "", "New file shall have MAC set to same value");
}

void group_check_general_update(testenv_struct* env){ 
    runtest(env, "GENERAL.UPDATE.WRITE_CLOSE", 2, ns_10ms, check_general_update_write_close, "check_general_update_write_close", "Yes", POSIX_c181, "fwrite+fclose shall update MC");
    runtest(env, "GENERAL.UPDATE.READ_CLOSE", 2, ns_10ms, check_general_update_read_close, "check_general_update_read_close", "Yes", POSIX_c181, "fread+fclose shall update A");
    runtest(env, "GENERAL.UPDATE.WRITE_STAT", 2, ns_10ms, check_general_update_write_stat, "check_general_update_write_stat", "Yes", POSIX_c181, "fwrite+fstat shall update MC");
    runtest(env, "GENERAL.UPDATE.READ_STAT", 2, ns_10ms, check_general_update_read_stat, "check_general_update_read_stat", "Yes", POSIX_c181, "fread+fstat shall update A");
    runtest(env, "GENERAL.UPDATE.CHMOD", 2, ns_10ms, check_general_update_chmod, "check_general_update_chmod", "Yes", POSIX_c181, "chmod shall update C");
}

#endif
