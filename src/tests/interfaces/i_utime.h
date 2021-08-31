#ifndef I_UTIME_H
#define I_UTIME_H

#include "interfaces.h"
// #include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <utime.h>

int check_interfaces_ts_utime_now_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_ts_utime_now_s(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

int check_interfaces_ts_utime_set_future_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);
int check_interfaces_ts_utime_set_past_ma(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path);

#endif
