#ifndef I_FILE_R_FREAD_H
#define I_FILE_R_FREAD_H

#include "interfaces.h"
// #include <unistd.h>
#include <fcntl.h>

int check_interfaces_file_r_fread(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_r_fread_ungetc(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_r_fread_ungetc_both(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);


#endif
