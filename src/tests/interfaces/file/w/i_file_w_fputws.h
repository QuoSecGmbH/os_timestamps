#ifndef I_FILE_W_FPUTWS_H
#define I_FILE_W_FPUTWS_H

#include "interfaces.h"
// #include <unistd.h>
#include <fcntl.h>

int check_interfaces_file_w_fputws_fflush(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_w_fputws_fclose(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_w_fputws_exit(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_w_fputws_abort(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);


#endif
