#ifndef I_UIMENSAT_H
#define I_UIMENSAT_H

#include "interfaces.h"
// #include <unistd.h>
#include <fcntl.h>

int check_interfaces_ts_utimensat_now_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_ts_utimensat_now_ns(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_ts_utimensat_now_ma_eq(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_ts_utimensat_now_mac_eq(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

int check_interfaces_ts_utimensat_set_future_a(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_ts_utimensat_set_past_a(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_ts_utimensat_set_future_m(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_ts_utimensat_set_past_m(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_ts_utimensat_set_future_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_ts_utimensat_set_past_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_ts_utimensat_set_omit(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#endif
