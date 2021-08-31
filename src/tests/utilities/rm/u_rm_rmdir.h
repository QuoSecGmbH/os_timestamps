#ifndef U_RMDIR_H
#define U_RMDIR_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"

int check_utilities_rm_rmdir_empty(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_rm_rmdir_notempty(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_rm_rmdir_notempty_parentdir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);


#endif
