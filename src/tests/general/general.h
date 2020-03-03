#ifndef GENERAL_H
#define GENERAL_H

#include "log.h"
#include "current_time.h"
#include "file_ts.h"
#include "misc.h"
#include <stdint.h>

int check_general_new_file_realtime(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_general_new_file(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_general_new_file_mac_eq(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_general_update_write_close(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_general_update_read_close(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_general_update_write_stat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_general_update_write_before_stat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_general_update_write_fstat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_general_update_read_stat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_general_update_read_before_stat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_general_update_read_fstat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_general_update_fopen_stat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_general_update_fopen_fstat_fclose(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
#endif
