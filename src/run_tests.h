#ifndef RUN_TESTS_H
#define RUN_TESTS_H

#include "current_time.h"
#include "log.h"
#include "general.h"
#include "interfaces.h"
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

typedef struct testenv_struct{
    FILE* csv_file;
    FILE* output_file;
    FILE* error_file;
    char* dir_path;
} testenv_struct;
testenv_struct* testenv_alloc(FILE* csv_file, FILE* output_file, FILE* err_file, char* dir_path);
int runtest(testenv_struct* env, char* ref, int repeat, time_t sleep_s, long sleep_ns, int (*func)(FILE*, FILE*, FILE*, char*), char* func_name, char* spec, char* spec_name, char* speclevel, char* desc);

void group_check_general_clock(testenv_struct* test_env);
void group_check_general_update(testenv_struct* test_env);
void group_check_general_new_file(testenv_struct* test_env);
void group_check_interfaces_exec(testenv_struct* env);


#endif
