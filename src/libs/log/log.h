#ifndef LOG_H
#define LOG_H

#include "stdio.h"
#include <stdarg.h> 
#include <string.h>

FILE* log_open_csv(char* path);
void log_close_csv(FILE* csv_file);
void log_csv_add_line(FILE* csv_file, int buf_count, ...);
void log_csv_add_result(FILE* csv_file, FILE* output_file, FILE* error_file, int result, char* desc, char* specified, char* spec, char* ref, char* func);
void log_result(FILE* output_file, FILE* error_file, const char* format, ...);
void log_info(FILE* output_file, FILE* error_file, const char* format, ...);
void log_warning(FILE* output_file, FILE* error_file, const char* format, ...);
void log_error(FILE* output_file, FILE* error_file, const char* format, ...);

#endif
