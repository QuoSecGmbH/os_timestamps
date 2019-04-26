#ifndef LOG_C
#define LOG_C

#include "log.h"

FILE* log_open_csv(char* path){
    FILE* csv_file = fopen(path, "w");
    return csv_file;
}

void log_close_csv(FILE* csv_file){
    fclose(csv_file);
}

void log_csv_add_line(FILE* csv_file, int buf_count, ...){
    va_list buf_list; 
    va_start(buf_list, buf_count); 

    int i;
    char* buf;
    for (i = 1; i <= buf_count; i++){
        buf = va_arg(buf_list, char *);
        fwrite(buf, strlen(buf), 1, csv_file);
        
        if (i < buf_count){
            fwrite(", ", 2, 1, csv_file);
        }
    }
    fwrite("\n", 1, 1, csv_file);
  
    va_end(buf_list); 
}

void log_csv_add_result(FILE* csv_file, FILE* output_file, FILE* error_file, int result, char* desc, char* specified, char* spec, char* ref, char* func){
    char* res_str; 
    if (result == 0){
        res_str = "Yes";
    }
    else if (result == 1){
        res_str = "No (ERR)";   
    }
    else {
        res_str = "No";
    }
    
    log_csv_add_line(csv_file, 6, res_str, desc, specified, spec, ref, func);
    log_result(output_file, error_file, "%s - %s - %s - %s", res_str, desc, ref, func);
}

void log_result(FILE* output_file, FILE* error_file, const char* format, ...){
    va_list argptr;
    va_start(argptr, format);
    fprintf(output_file, "RESULT: ");
    vfprintf(output_file, format, argptr);
    fprintf(output_file, "\n");
    va_end(argptr);
}

void log_info(FILE* output_file, FILE* error_file, const char* format, ...){
    va_list argptr;
    va_start(argptr, format);
    fprintf(output_file, "INFO: ");
    vfprintf(output_file, format, argptr);
    fprintf(output_file, "\n");
    va_end(argptr);
}

void log_debug(FILE* output_file, FILE* error_file, const char* format, ...){
    if (0) {
        va_list argptr;
        va_start(argptr, format);
        fprintf(output_file, "DEBUG: ");
        vfprintf(output_file, format, argptr);
        fprintf(output_file, "\n");
        va_end(argptr);
    }
}

void log_warning(FILE* output_file, FILE* error_file, const char* format, ...){
    va_list argptr;
    va_start(argptr, format);
    fprintf(output_file, "WARNING: ");
    vfprintf(output_file, format, argptr);
    fprintf(output_file, "\n");
    va_end(argptr);
}

void log_error(FILE* output_file, FILE* error_file, const char* format, ...){
    va_list argptr;
    va_start(argptr, format);
    fprintf(error_file, "ERROR: ");
    vfprintf(error_file, format, argptr);
    fprintf(error_file, "\n");
    va_end(argptr);
}
                  
#endif
