#ifndef I_FILE_H
#define I_FILE_H

#include "interfaces.h"
// #include <unistd.h>
#include <fcntl.h>

int check_interfaces_file_fflush_write_imm(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fflush_write(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fflush_nowrite(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fseek_write_imm(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fseek_write(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fseek_nowrite(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fsync_write_imm(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fsync_write(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fsync_nowrite(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);


#endif
