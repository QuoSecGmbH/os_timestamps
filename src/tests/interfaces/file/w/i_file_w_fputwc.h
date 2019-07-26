#ifndef I_FILE_W_FPUTWC_H
#define I_FILE_W_FPUTWC_H

#include "interfaces.h"
// #include <unistd.h>
#include <fcntl.h>

int check_interfaces_file_w_fputwc_fflush(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_w_fputwc_fclose(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_w_fputwc_exit(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_w_fputwc_abort(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);


#endif
