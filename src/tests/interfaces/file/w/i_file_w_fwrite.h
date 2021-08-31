#ifndef I_FILE_W_FWRITE_H
#define I_FILE_W_FWRITE_H

#include "interfaces.h"
// #include <unistd.h>
#include <fcntl.h>

int check_interfaces_file_w_fwrite_fflush_imm(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_w_fwrite_fflush(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_w_fwrite_fclose(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_w_fwrite_exit(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_w_fwrite_abort(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);


#endif
