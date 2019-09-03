#ifndef RUN_TESTS_H
#define RUN_TESTS_H

#include "current_time.h"
#include "log.h"
#include "general.h"
#include "interfaces.h"
#include "utilities.h"
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "profile.h"
#include "misc.h"

testenv_struct* testenv_alloc(FILE* csv_file, FILE* output_file, FILE* err_file, char* dir_path);
int runtest(testenv_struct* env, char* ref, int repeat, int repeatOperator, time_t sleep_s, long sleep_ns, int (*func)(FILE*, FILE*, FILE*, char*), char* func_name, char* spec, char* spec_name, char* speclevel, char* desc);

void group_check_general_clock(testenv_struct* test_env);
void group_check_general_update(testenv_struct* test_env);
void group_check_general_new_file(testenv_struct* test_env);
void group_check_interfaces_exec(testenv_struct* env);
void group_check_interfaces_attr(testenv_struct* env);
void group_check_interfaces_ts_futimens(testenv_struct* env);
void group_check_interfaces_ts_utimensat(testenv_struct* env);
void group_check_interfaces_ts_utimes(testenv_struct* env);
void group_check_interfaces_ts_utime(testenv_struct* env);
void group_check_interfaces_file(testenv_struct* env);
void group_check_interfaces_file_fopen(testenv_struct* env);
void group_check_interfaces_file_w(testenv_struct* env);
void group_check_interfaces_file_r(testenv_struct* env);
void group_check_interfaces_dir(testenv_struct* env);
void group_check_interfaces_file_new(testenv_struct* env);
void group_check_interfaces_file_ln(testenv_struct* env);
void group_check_interfaces_file_mv(testenv_struct* env);
void group_check_interfaces_file_rm(testenv_struct* env);

void group_check_utilities_attr(testenv_struct* env);
void group_check_utilities_cp(testenv_struct* env);
void group_check_utilities_new(testenv_struct* env);
void group_check_utilities_mv(testenv_struct* env);
void group_check_utilities_rm(testenv_struct* env);
void group_check_utilities_ln(testenv_struct* env);
void group_check_utilities_ls(testenv_struct* env);
void group_check_utilities_vi(testenv_struct* env);
void group_check_utilities_ed(testenv_struct* env);
void group_check_utilities_ex(testenv_struct* env);


#endif
