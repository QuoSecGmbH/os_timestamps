#ifndef U_LS_H
#define U_LS_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"

int check_utilities_ls(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_ls_files(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#endif
