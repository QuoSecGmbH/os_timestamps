#ifndef I_FILE_NEW_H
#define I_FILE_NEW_H

#include "interfaces.h"
// #include <unistd.h>
#include <fcntl.h>

int check_interfaces_file_new_mkdtemp_new(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_new_mkdtemp_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_new_mkdtemp_mac_1s(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_new_mkdir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_new_mkdir_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_new_mkdir_mac_1s(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_new_mkdirat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_new_mkdirat_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_new_mkdirat_mac_1s(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_new_mkfifo(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_new_mkfifo_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_new_mkfifo_mac_1s(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#ifndef __APPLE__
int check_interfaces_file_new_mkfifoat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_new_mkfifoat_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_new_mkfifoat_mac_1s(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
#endif

int check_interfaces_file_new_mkpipe(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
// check_interfaces_file_r_pread(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
// check_interfaces_file_r_pread_zero(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#endif
