#ifndef I_FILE_R_GETS_H
#define I_FILE_R_GETS_H

#include "interfaces.h"
// #include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int check_interfaces_file_r_gets(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_r_gets_ungetc(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_r_gets_ungetc_both(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);


#endif
