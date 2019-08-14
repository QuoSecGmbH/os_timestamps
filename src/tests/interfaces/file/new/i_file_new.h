#ifndef I_FILE_NEW_H
#define I_FILE_NEW_H

#include "interfaces.h"
// #include <unistd.h>
#include <fcntl.h>

int check_interfaces_file_new_mkdtemp_new(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_new_mkdtemp_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
// check_interfaces_file_r_pread(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
// check_interfaces_file_r_pread_zero(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#endif
