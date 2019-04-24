#ifndef RUN_TESTS_H
#define RUN_TESTS_H

#include "current_time.h"
#include "log.h"
#include "general.h"
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

void group_check_general_clock(FILE* csv_file, FILE* output_file, FILE* err_file);
void group_check_general_update(FILE* csv_file, FILE* output_file, FILE* err_file, char* dir_path);

#endif
