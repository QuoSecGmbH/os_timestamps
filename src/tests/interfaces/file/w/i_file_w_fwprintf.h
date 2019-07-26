#ifndef I_FILE_W_FWPRINTF_H
#define I_FILE_W_FWPRINTF_H

#include "interfaces.h"
// #include <unistd.h>
#include <fcntl.h>

int check_interfaces_file_w_fwprintf_fflush(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_w_fwprintf_fclose(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_w_fwprintf_exit(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_w_fwprintf_abort(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);


#endif
