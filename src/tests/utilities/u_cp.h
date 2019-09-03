#ifndef CP_H
#define CP_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include "profile.h"

int check_utilities_cp_new(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_cp_new_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_cp_new_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_cp_new_dir_mc(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

int check_utilities_cp_existing(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_cp_existing_mc(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_utilities_cp_existing_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#endif
