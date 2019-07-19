#ifndef RUN_TESTS_C
#define RUN_TESTS_C

#include "run_tests.h"

char* POSIX_c181 = "POSIX_c181";
char* MANDATORY = "MANDATORY";
char* NEEDNOT = "NEEDNOT";

int REPEAT_WORST = 0;
int REPEAT_BEST = 1;

int runtest(testenv_struct* env, char* ref, int repeat, int repeatOperator, time_t sleep_s, long sleep_ns, int (*func)(FILE*, FILE*, FILE*, char*), char* func_name, char* spec, char* spec_name, char* speclevel, char* desc){
    int result = -1;
    int newresult = 0;
    char* curr_ref;
    int i;
    
    struct timespec* ts_ns = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_ns->tv_sec = sleep_s;
    ts_ns->tv_nsec = sleep_ns; 
    
    for (i=0; i<repeat; i++){
        nanosleep(ts_ns, NULL);
        newresult = func(env->csv_file, env->output_file, env->error_file, env->dir_path);
        if (result == -1){
            result = newresult;
        }
        
        if (repeat >= 2 && VERBOSE){
            curr_ref = (char*) calloc(strlen(ref)+20, 1);
            sprintf(curr_ref, "%s.%i", ref, i+1);
            log_csv_add_result(env->csv_file, env->output_file, env->error_file, newresult, desc, spec, spec_name, speclevel, curr_ref, func_name);
        }
        
        if (repeatOperator == REPEAT_BEST){
            if (newresult < result){
                result = newresult;
            }
        }
        else{
            if (newresult > result){
                result = newresult;
            }
        }
    }
    log_csv_add_result(env->csv_file, env->output_file, env->error_file, result, desc, spec, spec_name, speclevel, ref, func_name);
    
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
    
    // pre-creating some of the test files
    misc_concat_ensure_file_exists(dir_path, "interfaces.futimens", s_0s, ns_0ns, output_file, error_file, __func__);
    misc_concat_ensure_file_exists(dir_path, "interfaces.utimensat", s_0s, ns_0ns, output_file, error_file, __func__);
    misc_concat_ensure_file_exists(dir_path, "interfaces.utimes", s_0s, ns_0ns, output_file, error_file, __func__);
    misc_concat_ensure_file_exists(dir_path, "interfaces.utime", 2*s_1s, ns_0ns, output_file, error_file, __func__);
    
    testenv_struct* test_env = testenv_alloc(csv_file, output_file, error_file, dir_path);
    
    log_csv_add_line(csv_file, 6, "Passed?", "Description", "Specified?", "Spec", "Level", "Ref", "Function");
    group_check_general_clock(test_env);
    group_check_general_new_file(test_env);
    group_check_general_update(test_env);
    
    group_check_interfaces_exec(test_env);
    group_check_interfaces_attr(test_env);
    group_check_interfaces_ts_futimens(test_env);
    group_check_interfaces_ts_utimensat(test_env);
    group_check_interfaces_ts_utimes(test_env);
    group_check_interfaces_ts_utime(test_env);

    log_close_csv(csv_file);
}

void group_check_general_clock(testenv_struct* env){
    runtest(env, "GENERAL.CLOCK.RES", 1, REPEAT_WORST, s_0s, ns_10ms, check_general_clock_res, "check_general_clock_res", "Yes", POSIX_c181, MANDATORY, "Clock resolution shall be at max 0.02s (CLOCK_REALTIME)");
    runtest(env, "GENERAL.CLOCK.INCREMENTS", 1, REPEAT_WORST, s_0s, ns_10ms, check_general_clock_increments, "check_general_clock_increments", "No", "", MANDATORY, "Clock is incremental (increasing)");
}

void group_check_general_new_file(testenv_struct* env){
    runtest(env, "GENERAL.NEW_FILE_REALTIME", 1, REPEAT_WORST, s_0s, ns_10ms, check_general_new_file_realtime, "check_general_new_file_realtime", "No", "", MANDATORY, "New file shall have MAC updated (CLOCK_REALTIME)");
    runtest(env, "GENERAL.NEW_FILE", 1, REPEAT_WORST, s_0s, ns_10ms, check_general_new_file, "check_general_new_file", "Yes", POSIX_c181, MANDATORY, "New file shall have MAC updated");
    runtest(env, "GENERAL.NEW_FILE.MAC_eq", 1, REPEAT_WORST, s_0s, ns_10ms, check_general_new_file_mac_eq, "check_general_new_file_mac_eq", "No", "", MANDATORY, "New file shall have MAC set to same value");
}

void group_check_general_update(testenv_struct* env){ 
    runtest(env, "GENERAL.UPDATE.WRITE_CLOSE", 2, REPEAT_WORST, s_0s, ns_10ms, check_general_update_write_close, "check_general_update_write_close", "Yes", POSIX_c181, MANDATORY, "fwrite+fclose shall update MC");
    runtest(env, "GENERAL.UPDATE.READ_CLOSE", 2, REPEAT_WORST, s_0s, ns_10ms, check_general_update_read_close, "check_general_update_read_close", "Yes", POSIX_c181, MANDATORY, "fread+fclose shall update A");
    runtest(env, "GENERAL.UPDATE.WRITE_STAT", 2, REPEAT_WORST, s_0s, ns_10ms, check_general_update_write_stat, "check_general_update_write_stat", "Yes", POSIX_c181, MANDATORY, "fwrite+fstat shall update MC");
    runtest(env, "GENERAL.UPDATE.READ_STAT", 2, REPEAT_WORST, s_0s, ns_10ms, check_general_update_read_stat, "check_general_update_read_stat", "Yes", POSIX_c181, MANDATORY, "fread+fstat shall update A");
}

void group_check_interfaces_exec(testenv_struct* env){
    runtest(env, "INTERFACES.EXEC.EXECVP", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_exec_execvp, "check_interfaces_exec_execvp", "Yes", POSIX_c181, MANDATORY, "exec shall update A");
    runtest(env, "INTERFACES.EXEC.EXECVP_LOCAL", 2, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_exec_execvp_local, "check_interfaces_exec_execvp_local", "Yes", POSIX_c181, MANDATORY, "exec shall update A (local)");
}

void group_check_interfaces_attr(testenv_struct* env){
    runtest(env, "INTERFACES.ATTR.CHMOD", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_attr_chmod, "check_interfaces_attr_chmod", "Yes", POSIX_c181, MANDATORY, "chmod shall update C");
    runtest(env, "INTERFACES.ATTR.CHOWN_GRP", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_attr_chown_grp, "check_interfaces_attr_chown_grp", "Yes", POSIX_c181, MANDATORY, "chown(-1, getgid()) shall update C");
    runtest(env, "INTERFACES.ATTR.CHOWN_USR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_attr_chown_usr, "check_interfaces_attr_chown_usr", "Yes", POSIX_c181, MANDATORY, "chown(getuid(), -1) shall update C");
    runtest(env, "INTERFACES.ATTR.CHOWN_GRP_USR", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_attr_chown_grp_usr, "check_interfaces_attr_chown_grp_usr", "Yes", POSIX_c181, MANDATORY, "chown(getuid(), getgid()) shall update C");
    runtest(env, "INTERFACES.ATTR.CHOWN_NOCHANGE", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_attr_chown_nochange, "check_interfaces_attr_chown_nochange", "Yes", POSIX_c181, NEEDNOT, "chown(-1, -1) need not update MAC");
}

void group_check_interfaces_ts_futimens(testenv_struct* env){
    runtest(env, "INTERFACES.TS.FUTIMENS_NOW_MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_now_ma, "check_interfaces_ts_futimens_now_ma", "Yes", POSIX_c181, MANDATORY, "Setting MA to now with futimens shall set MA and update C");
    runtest(env, "INTERFACES.TS.FUTIMENS_NOW_NS", 10, REPEAT_BEST, s_0s, ns_10ms, check_interfaces_ts_futimens_now_ns, "check_interfaces_ts_futimens_now_ns", "Yes", POSIX_c181, MANDATORY, "Setting MA to now with futimens shall give MA granularity to the nanoseconds");
    runtest(env, "INTERFACES.TS.FUTIMENS_NOW_MA_EQ", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_now_ma_eq, "check_interfaces_ts_futimens_now_ma_eq", "No", "", MANDATORY, "Setting MA to now with futimens shall set MA to same value");
    runtest(env, "INTERFACES.TS.FUTIMENS_NOW_MAC_EQ", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_now_mac_eq, "check_interfaces_ts_futimens_now_mac_eq", "No", "", MANDATORY, "Setting MA to now with futimens shall set MAC to same value");
    runtest(env, "INTERFACES.TS.FUTIMENS.SET.FUTURE.A", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_set_future_a, "check_interfaces_ts_futimens_set_future_a", "Yes", POSIX_c181, MANDATORY, "Setting A to a future value shall set A, keep M and update C");
    runtest(env, "INTERFACES.TS.FUTIMENS.SET.PAST.A", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_set_past_a, "check_interfaces_ts_futimens_set_past_a", "Yes", POSIX_c181, MANDATORY, "Setting A to a past value shall set A, keep M and update C");
    runtest(env, "INTERFACES.TS.FUTIMENS.SET.FUTURE.M", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_set_future_m, "check_interfaces_ts_futimens_set_future_m", "Yes", POSIX_c181, MANDATORY, "Setting M to a future value shall set M, keep A and update C");
    runtest(env, "INTERFACES.TS.FUTIMENS.SET.PAST.M", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_set_past_m, "check_interfaces_ts_futimens_set_past_m", "Yes", POSIX_c181, MANDATORY, "Setting M to a past value shall set M, keep A and update C");
    runtest(env, "INTERFACES.TS.FUTIMENS.SET.FUTURE.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_set_future_ma, "check_interfaces_ts_futimens_set_future_ma", "Yes", POSIX_c181, MANDATORY, "Setting M and A to future values shall set MA and update C");
    runtest(env, "INTERFACES.TS.FUTIMENS.SET.PAST.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_set_past_ma, "check_interfaces_ts_futimens_set_past_ma", "Yes", POSIX_c181, MANDATORY, "Setting M and A to past values shall set MA and update C");
    runtest(env, "INTERFACES.TS.FUTIMENS.SET.OMIT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_futimens_set_omit, "check_interfaces_ts_futimens_set_omit", "Yes", POSIX_c181, NEEDNOT, "With UTIME_OMIT, C need not to be updated");
}

void group_check_interfaces_ts_utimensat(testenv_struct* env){
    runtest(env, "INTERFACES.TS.UTIMENSAT_NOW_MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_now_ma, "check_interfaces_ts_utimensat_now_ma", "Yes", POSIX_c181, MANDATORY, "Setting MA to now with utimensat shall set MA and update C");
    runtest(env, "INTERFACES.TS.UTIMENSAT_NOW_NS", 10, REPEAT_BEST, s_0s, ns_10ms, check_interfaces_ts_utimensat_now_ns, "check_interfaces_ts_utimensat_now_ns", "Yes", POSIX_c181, MANDATORY, "Setting MA to now with utimensat shall give MA granularity to the nanoseconds");
    runtest(env, "INTERFACES.TS.UTIMENSAT_NOW_MA_EQ", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_now_ma_eq, "check_interfaces_ts_utimensat_now_ma_eq", "No", "", MANDATORY, "Setting MA to now with utimensat shall set MA to same value");
    runtest(env, "INTERFACES.TS.UTIMENSAT_NOW_MAC_EQ", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_now_mac_eq, "check_interfaces_ts_utimensat_now_mac_eq", "No", "", MANDATORY, "Setting MA to now with utimensat shall set MAC to same value");
    runtest(env, "INTERFACES.TS.UTIMENSAT.SET.FUTURE.A", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_set_future_a, "check_interfaces_ts_utimensat_set_future_a", "Yes", POSIX_c181, MANDATORY, "Setting A to a future value shall set A, keep M and update C");
    runtest(env, "INTERFACES.TS.UTIMENSAT.SET.PAST.A", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_set_past_a, "check_interfaces_ts_utimensat_set_past_a", "Yes", POSIX_c181, MANDATORY, "Setting A to a past value shall set A, keep M and update C");
    runtest(env, "INTERFACES.TS.UTIMENSAT.SET.FUTURE.M", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_set_future_m, "check_interfaces_ts_utimensat_set_future_m", "Yes", POSIX_c181, MANDATORY, "Setting M to a future value shall set M, keep A and update C");
    runtest(env, "INTERFACES.TS.UTIMENSAT.SET.PAST.M", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_set_past_m, "check_interfaces_ts_utimensat_set_past_m", "Yes", POSIX_c181, MANDATORY, "Setting M to a past value shall set M, keep A and update C");
    runtest(env, "INTERFACES.TS.UTIMENSAT.SET.FUTURE.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_set_future_ma, "check_interfaces_ts_utimensat_set_future_ma", "Yes", POSIX_c181, MANDATORY, "Setting M and A to future values shall set MA and update C");
    runtest(env, "INTERFACES.TS.UTIMENSAT.SET.PAST.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_set_past_ma, "check_interfaces_ts_utimensat_set_past_ma", "Yes", POSIX_c181, MANDATORY, "Setting M and A to past values shall set MA and update C");
    runtest(env, "INTERFACES.TS.UTIMENSAT.SET.OMIT", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimensat_set_omit, "check_interfaces_ts_utimensat_set_omit", "Yes", POSIX_c181, NEEDNOT, "With UTIME_OMIT, C need not to be updated");
}

void group_check_interfaces_ts_utimes(testenv_struct* env){
    runtest(env, "INTERFACES.TS.UTIMES_NOW_MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimes_now_ma, "check_interfaces_ts_utimes_now_ma", "Yes", POSIX_c181, MANDATORY, "Setting MA to now with utimes shall set MA and update C");
    runtest(env, "INTERFACES.TS.UTIMES_NOW_US", 10, REPEAT_BEST, s_0s, ns_10ms, check_interfaces_ts_utimes_now_us, "check_interfaces_ts_utimes_now_us", "Yes", POSIX_c181, MANDATORY, "Setting MA to now with utimes shall give MA granularity to the microsecond");

    runtest(env, "INTERFACES.TS.UTIMES.SET.FUTURE.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimes_set_future_ma, "check_interfaces_ts_utimes_set_future_ma", "Yes", POSIX_c181, MANDATORY, "Setting M and A to future values shall set MA and update C");
    runtest(env, "INTERFACES.TS.UTIMES.SET.PAST.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utimes_set_past_ma, "check_interfaces_ts_utimes_set_past_ma", "Yes", POSIX_c181, MANDATORY, "Setting M and A to past values shall set MA and update C");
}

void group_check_interfaces_ts_utime(testenv_struct* env){
    runtest(env, "INTERFACES.TS.UTIME_NOW_MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utime_now_ma, "check_interfaces_ts_utime_now_ma", "Yes", POSIX_c181, MANDATORY, "Setting MA to now with utime shall set MA and update C");
    runtest(env, "INTERFACES.TS.UTIME_NOW_S", 10, REPEAT_BEST, s_0s, ns_10ms, check_interfaces_ts_utime_now_s, "check_interfaces_ts_utime_now_us", "Yes", POSIX_c181, MANDATORY, "Setting MA to now with utime shall give MA granularity to the second");

    runtest(env, "INTERFACES.TS.UTIME.SET.FUTURE.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utime_set_future_ma, "check_interfaces_ts_utime_set_future_ma", "Yes", POSIX_c181, MANDATORY, "Setting M and A to future values shall set MA and update C");
//     runtest(env, "INTERFACES.TS.UTIME.SET.PAST.MA", 1, REPEAT_WORST, s_0s, ns_10ms, check_interfaces_ts_utime_set_past_ma, "check_interfaces_ts_utime_set_past_ma", "Yes", POSIX_c181, MANDATORY, "Setting M and A to past values shall set MA and update C");
}
#endif

    
    
