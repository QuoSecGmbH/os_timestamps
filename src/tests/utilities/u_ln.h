#ifndef U_LN_H
#define U_LN_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"

int check_utilities_ln_new(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_ln_existing(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_ln_s_new(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_ln_s_existing(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#endif
