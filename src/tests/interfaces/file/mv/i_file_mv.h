#ifndef I_FILE_MV_H
#define I_FILE_MV_H

#include "interfaces.h"
// #include <unistd.h>
#include <fcntl.h>

int check_interfaces_file_mv_rename_file(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_mv_rename_file_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_mv_rename_file_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_mv_rename_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_mv_rename_dir_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_mv_rename_dir_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_mv_renameat_file(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_mv_renameat_file_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_mv_renameat_file_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_mv_renameat_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_mv_renameat_dir_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_mv_renameat_dir_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#endif
