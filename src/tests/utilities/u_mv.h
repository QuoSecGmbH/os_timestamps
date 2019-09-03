#ifndef U_MV_H
#define U_MV_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"

int check_utilities_mv_new(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_mv_new_eq(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_mv_existing(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_mv_existing_eq(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#endif
