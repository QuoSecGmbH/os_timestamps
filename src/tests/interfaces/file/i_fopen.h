#ifndef I_FOPEN_H
#define I_FOPEN_H

#include "interfaces.h"
// #include <unistd.h>
#include <fcntl.h>


int helper_interfaces_file_fopen_new_writemode(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path, char* mode);
int check_interfaces_file_fopen_new_W(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_new_WB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_new_A(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_new_AB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_new_WP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_new_WBP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_new_WPB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_new_AP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_new_ABP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_new_APB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

int helper_interfaces_file_fopen_existing_writemode(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path, char* mode);
int check_interfaces_file_fopen_existing_W(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_existing_WB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_existing_WP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_existing_WBP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_existing_WPB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

int helper_interfaces_file_fopen_fwrite_existing_writemode(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path, char* mode);
int check_interfaces_file_fopen_fwrite_existing_W(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fwrite_existing_WB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fwrite_existing_WP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fwrite_existing_WBP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fwrite_existing_WPB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fwrite_existing_RP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fwrite_existing_RBP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fwrite_existing_RPB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

int helper_interfaces_file_fopen_fwrite_existing_dir_writemode(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path, char* mode);
int check_interfaces_file_fopen_fwrite_existing_dir_W(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fwrite_existing_dir_WB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fwrite_existing_dir_WP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fwrite_existing_dir_WBP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fwrite_existing_dir_WPB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fwrite_existing_dir_RP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fwrite_existing_dir_RBP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fwrite_existing_dir_RPB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

int helper_interfaces_file_fopen_existing_readmode(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path, char* mode);
int check_interfaces_file_fopen_existing_R(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_existing_RB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_existing_RP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_existing_RBP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_existing_RPB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

int helper_interfaces_file_fopen_fread_existing_readmode(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path, char* mode);
int check_interfaces_file_fopen_fread_existing_R(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fread_existing_RB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fread_existing_RP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fread_existing_RBP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fread_existing_RPB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

int helper_interfaces_file_fopen_fread_existing_writemode(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path, char* mode);
int check_interfaces_file_fopen_fread_existing_WP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fread_existing_WBP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_file_fopen_fread_existing_WPB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#endif
