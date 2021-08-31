#ifndef I_FILE_LN_H
#define I_FILE_LN_H

#include "interfaces.h"
// #include <unistd.h>
#include <fcntl.h>

int check_interfaces_file_ln_link(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_ln_linkat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_ln_symlink(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_ln_symlinkat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_ln_readlink(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_ln_readlinkat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#endif
