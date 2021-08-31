#ifndef I_FILE_RM_H
#define I_FILE_RM_H

#include "interfaces.h"
// #include <unistd.h>
#include <fcntl.h>

int check_interfaces_file_rm_unlink_last_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_rm_unlink_notlast_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_rm_unlink_notlast(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_rm_unlinkat_last_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_rm_unlinkat_notlast_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_rm_unlinkat_notlast(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

int check_interfaces_file_rm_remove_dir_empty_parentdir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_rm_remove_dir_notempty_parentdir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_rm_remove_dir_notempty(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_rm_remove_file_last_parentdir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_rm_remove_file_notlast_parentdir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_rm_remove_file_notlast(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

int check_interfaces_file_rm_rmdir_empty_parentdir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_rm_rmdir_notempty_parentdir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_rm_rmdir_notempty(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#endif
