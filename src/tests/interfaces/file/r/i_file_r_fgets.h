#ifndef I_FILE_R_FGETS_H
#define I_FILE_R_FGETS_H

#include "interfaces.h"
// #include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int check_interfaces_file_r_fgets(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_r_fgets_ungetc(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_r_fgets_ungetc_both(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);


#endif
