#ifndef U_RM_H
#define U_RM_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"

int check_utilities_rm_rm_dir_empty(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_rm_rm_r_dir_empty(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_rm_rm_r_dir_notempty(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_rm_rm_file_last(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_rm_rm_file_notlast(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_rm_rm_file_notlast_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);


#endif
