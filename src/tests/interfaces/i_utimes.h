#ifndef I_UTIMES_H
#define I_UTIMES_H

#include "interfaces.h"
// #include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

int check_interfaces_ts_utimes_now_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_ts_utimes_now_us(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

int check_interfaces_ts_utimes_set_future_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_ts_utimes_set_past_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#endif
