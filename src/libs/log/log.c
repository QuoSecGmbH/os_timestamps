#ifndef LOG_C
#define LOG_C

#include "log.h"

FILE* log_open_csv(char* path){
    FILE* csv_file = fopen(path, "wb");
    return csv_file;
}

FILE* log_open_csv_append(char* path){
    FILE* csv_file = fopen(path, "ab");
    return csv_file;
}

void log_close_csv(FILE* csv_file){
    fclose(csv_file);
}

void log_csv_add_line(FILE* csv_file, int buf_count, ...){
    va_list buf_list; 
    va_start(buf_list, buf_count); 

//     fwrite("BEGLINE\n", 8, 1, csv_file);
    int i;
    char* buf;
    for (i = 1; i <= buf_count; i++){
        buf = va_arg(buf_list, char *);
        fwrite("\"", 1, 1, csv_file);
        fwrite(buf, strlen(buf), 1, csv_file);
        fwrite("\"", 1, 1, csv_file);
        
        if (i < buf_count){
            fwrite(", ", 2, 1, csv_file);
        }
    }
    fwrite("\n", 1, 1, csv_file);
//     fwrite("ENDLINE\n", 8, 1, csv_file);
  
    va_end(buf_list); 
}

void log_csv_add_result(FILE* csv_file, FILE* output_file, FILE* error_file, int result, char* desc, char* specified, char* spec, char* speclevel, char* ref, char* func){
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
    
    log_csv_add_line(csv_file, 6, res_str, desc, specified, spec, speclevel, ref, func);
    log_result(output_file, error_file, "%s - %s(%s.%s) - %s - %s - %s", res_str, specified, spec, speclevel, desc, ref, func);
}

void log_result(FILE* output_file, FILE* error_file, const char* format, ...){
    va_list argptr;
    va_start(argptr, format);
    fprintf(output_file, "RESULT: ");
    vfprintf(output_file, format, argptr);
    fprintf(output_file, "\n");
        
    va_start(argptr, format);
    fprintf(stdout, "RESULT: ");
    vfprintf(stdout, format, argptr);
    fprintf(stdout, "\n");
    va_end(argptr);
}

void log_info(FILE* output_file, FILE* error_file, const char* format, ...){
    va_list argptr;
    va_start(argptr, format);
    fprintf(output_file, "INFO: ");
    vfprintf(output_file, format, argptr);
    fprintf(output_file, "\n");
    
    va_start(argptr, format);
    fprintf(stdout, "INFO: ");
    vfprintf(stdout, format, argptr);
    fprintf(stdout, "\n");
    va_end(argptr);
}

void log_debug(FILE* output_file, FILE* error_file, const char* format, ...){
    if (0) {
        va_list argptr;
        va_start(argptr, format);
        fprintf(output_file, "DEBUG: ");
        vfprintf(output_file, format, argptr);
        fprintf(output_file, "\n");
        
            
        va_start(argptr, format);
        fprintf(stdout, "DEBUG: ");
        vfprintf(stdout, format, argptr);
        fprintf(stdout, "\n");
        va_end(argptr);
    }
}

void log_warning(FILE* output_file, FILE* error_file, const char* format, ...){
    va_list argptr;
    va_start(argptr, format);
    fprintf(output_file, "WARNING: ");
    vfprintf(output_file, format, argptr);
    fprintf(output_file, "\n");
        
    va_start(argptr, format);
    fprintf(stdout, "WARNING: ");
    vfprintf(stdout, format, argptr);
    fprintf(stdout, "\n");
    va_end(argptr);
}

void log_error(FILE* output_file, FILE* error_file, const char* format, ...){
    va_list argptr;
    va_start(argptr, format);
    fprintf(error_file, "ERROR: ");
    vfprintf(error_file, format, argptr);
    fprintf(error_file, "\n");
        
    va_start(argptr, format);
    fprintf(stderr, "ERROR: ");
    vfprintf(stderr, format, argptr);
    fprintf(stderr, "\n");
    va_end(argptr);
}

void log_info_ts_profile_on_error_generic(FILE* output_file, FILE* error_file, const char* func_name, int result, struct profile_info_struct* pi, char* message, int print_profile){
    if (result != 0 || VERBOSE >= 1){
        if (print_profile) misc_print_profile(output_file, error_file, pi);
        
        if (strlen(message) == 0){
            log_info(output_file, error_file, "%s:", func_name, message);
        }
        else {
            log_info(output_file, error_file, "%s - %s:", func_name, message);
        }
        if (pi->ts_before != NULL && pi->ts_after != NULL && pi->ts_after_delay != NULL){
            log_info(output_file, error_file, "Before: %lds %ldns ; After: %lds %ldns ; After delay: %lds %ldns",
                     pi->ts_before->tv_sec, pi->ts_before->tv_nsec,
                     pi->ts_after->tv_sec, pi->ts_after->tv_nsec,
                     pi->ts_after_delay->tv_sec, pi->ts_after_delay->tv_nsec);
        }
        int i;
        for (i = 0; i < pi->watch_num; i++){
            char* path = pi->watch_array[i];
            struct stat_macb* file_stat_before = pi->multi_stat_before[i];
            struct stat_macb* file_stat_after = pi->multi_stat_after[i];
            struct stat_macb* file_stat_after_delay = pi->multi_stat_after_delay[i];
            int error_printed = 0;
            if (file_stat_before != NULL){
                log_info(output_file, error_file, "stat before command for %s", path);
                log_info(output_file, error_file, "M: %lds %ldns", file_stat_before->st_mtim.tv_sec, file_stat_before->st_mtim.tv_nsec);
                log_info(output_file, error_file, "A: %lds %ldns", file_stat_before->st_atim.tv_sec, file_stat_before->st_atim.tv_nsec);
                log_info(output_file, error_file, "C: %lds %ldns", file_stat_before->st_ctim.tv_sec, file_stat_before->st_ctim.tv_nsec);
                log_info(output_file, error_file, "B: %lds %ldns", file_stat_before->st_btim.tv_sec, file_stat_before->st_btim.tv_nsec);
            }
            else if (error_printed == 0) {
                log_info(output_file, error_file, "stat before command for %s is NULL", path);
                error_printed = 1;
                
            }
            if (file_stat_after != NULL){
                log_info(output_file, error_file, "stat after command for %s", path);
                log_info(output_file, error_file, "M: %lds %ldns", file_stat_after->st_mtim.tv_sec, file_stat_after->st_mtim.tv_nsec);
                log_info(output_file, error_file, "A: %lds %ldns", file_stat_after->st_atim.tv_sec, file_stat_after->st_atim.tv_nsec);
                log_info(output_file, error_file, "C: %lds %ldns", file_stat_after->st_ctim.tv_sec, file_stat_after->st_ctim.tv_nsec);
                log_info(output_file, error_file, "B: %lds %ldns", file_stat_after->st_btim.tv_sec, file_stat_after->st_btim.tv_nsec);
            }
            else if (error_printed == 0)  {
                log_info(output_file, error_file, "stat after command for %s is NULL", path);
                error_printed = 1;
            }
            if (file_stat_after_delay != NULL){
                log_info(output_file, error_file, "stat after delay for %s", path);
                log_info(output_file, error_file, "M: %lds %ldns", file_stat_after_delay->st_mtim.tv_sec, file_stat_after_delay->st_mtim.tv_nsec);
                log_info(output_file, error_file, "A: %lds %ldns", file_stat_after_delay->st_atim.tv_sec, file_stat_after_delay->st_atim.tv_nsec);
                log_info(output_file, error_file, "C: %lds %ldns", file_stat_after_delay->st_ctim.tv_sec, file_stat_after_delay->st_ctim.tv_nsec);
                log_info(output_file, error_file, "B: %lds %ldns", file_stat_after_delay->st_btim.tv_sec, file_stat_after_delay->st_btim.tv_nsec);
            }
            else if (error_printed == 0) {
                log_info(output_file, error_file, "stat after delay for %s is NULL", path);
                error_printed = 1;
            }
        }
    }
}

void log_info_ts_profile_on_error_message(FILE* output_file, FILE* error_file, const char* func_name, int result, struct profile_info_struct* pi, char* message){
    log_info_ts_profile_on_error_generic(output_file, error_file, func_name, result, pi, message, 1);
}

void log_info_ts_profile_on_error_message_short(FILE* output_file, FILE* error_file, const char* func_name, int result, struct profile_info_struct* pi, char* message){
    log_info_ts_profile_on_error_generic(output_file, error_file, func_name, result, pi, message, 0);
}

void log_info_ts_stat_on_error_message(FILE* output_file, FILE* error_file, const char* func_name, int result, struct timespec* ts_before, struct timespec* ts_after, struct stat_macb* file_stat, char* message){
    if (result != 0 || VERBOSE >= 1){
        if (strlen(message) == 0){
            log_info(output_file, error_file, "%s:", func_name, message);
        }
        else {
            log_info(output_file, error_file, "%s - %s:", func_name, message);
        }
        if (ts_before != NULL && ts_after != NULL){
            log_info(output_file, error_file, "Before: %lds %ldns ; After: %lds %ldns", ts_before->tv_sec, ts_before->tv_nsec, ts_after->tv_sec, ts_after->tv_nsec);
        }
        if (file_stat != NULL){
            log_info(output_file, error_file, "M: %lds %ldns", file_stat->st_mtim.tv_sec, file_stat->st_mtim.tv_nsec);
            log_info(output_file, error_file, "A: %lds %ldns", file_stat->st_atim.tv_sec, file_stat->st_atim.tv_nsec);
            log_info(output_file, error_file, "C: %lds %ldns", file_stat->st_ctim.tv_sec, file_stat->st_ctim.tv_nsec);
            log_info(output_file, error_file, "B: %lds %ldns", file_stat->st_btim.tv_sec, file_stat->st_btim.tv_nsec);
        }
    }
}

void log_info_ts_stat_on_error(FILE* output_file, FILE* error_file, const char* func_name, int result, struct timespec* ts_before, struct timespec* ts_after, struct stat_macb* file_stat){
    log_info_ts_stat_on_error_message(output_file, error_file, func_name, result, ts_before, ts_after, file_stat, "");
}
                  
#endif
