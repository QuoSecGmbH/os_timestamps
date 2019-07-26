#ifndef I_FILE_W_H
#define I_FILE_W_H

#include "interfaces.h"
// #include <unistd.h>
#include <fcntl.h>

int check_interfaces_file_w_dprintf(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_w_ftruncate(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_w_write(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_w_write_zero(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#endif
