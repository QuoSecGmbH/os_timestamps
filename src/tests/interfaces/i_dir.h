#ifndef I_DIR_H
#define I_DIR_H

#include "interfaces.h"
// #include <unistd.h>
#include <fcntl.h>

int check_interfaces_dir_readdir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_dir_readdir_files(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_dir_readdir_r(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_dir_readdir_r_files(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#endif
