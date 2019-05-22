#ifndef RUN_TESTS_H
#define RUN_TESTS_H

#include "current_time.h"
#include "log.h"
#include "general.h"
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

void group_check_general_clock(testenv_struct* test_env);
void group_check_general_update(testenv_struct* test_env);
void group_check_general_new_file(testenv_struct* test_env);


#endif
