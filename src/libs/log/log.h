#ifndef LOG_H
#define LOG_H

#include "time.h"
#include "stdio.h"
#include "misc.h"
#include <sys/stat.h>
#include <stdarg.h> 
#include <string.h>

FILE* log_open_csv(char* path);
void log_close_csv(FILE* csv_file);
void log_csv_add_line(FILE* csv_file, int buf_count, ...);
void log_csv_add_result(FILE* csv_file, FILE* output_file, FILE* error_file, int result, char* desc, char* specified, char* spec, char* ref, char* func);
void log_result(FILE* output_file, FILE* error_file, const char* format, ...);
void log_info(FILE* output_file, FILE* error_file, const char* format, ...);
void log_debug(FILE* output_file, FILE* error_file, const char* format, ...);
void log_warning(FILE* output_file, FILE* error_file, const char* format, ...);
void log_error(FILE* output_file, FILE* error_file, const char* format, ...);
void log_info_ts_stat_on_error(FILE* output_file, FILE* error_file, const char* func_name, int result, struct timespec* ts_before, struct timespec* ts_after, struct stat* file_stat);

#endif
