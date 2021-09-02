#ifndef I_FILE_C
#define I_FILE_C

#include "i_file.h"

int check_interfaces_file_fflush_write_imm(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, __func__, s_0s, ns_0ns, output_file, error_file, __func__);
    misc_nanosleep(ns_DELAY); 
    
    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    fwrite("Hallo", 5, 1, fd);
    fflush(fd);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY); 
    struct stat_macb* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    fclose(fd);
        
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}


int check_interfaces_file_fflush_write(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, __func__, s_0s, ns_0ns, output_file, error_file, __func__);
    misc_nanosleep(ns_DELAY); 
    
    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    fwrite("Hallo", 5, 1, fd);
    fflush(fd);
    
    struct stat_macb* file_stat = get_path_timestamps(path);
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    fclose(fd);
        
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_fflush_nowrite(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, __func__, s_0s, ns_0ns, output_file, error_file, __func__);
    misc_nanosleep(ns_DELAY); 
    
    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    fflush(fd);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY); 
    struct stat_macb* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    fclose(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_fseek_write_imm(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, __func__, s_0s, ns_0ns, output_file, error_file, __func__);
    misc_nanosleep(ns_DELAY); 
    
    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    fwrite("Hallo", 5, 1, fd);
    fseek(fd, 2, SEEK_SET);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
     misc_nanosleep(ns_DELAY); 
    struct stat_macb* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    fclose(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_fseek_write(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, __func__, s_0s, ns_0ns, output_file, error_file, __func__);
    misc_nanosleep(ns_DELAY); 
    
    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    fwrite("Hallo", 5, 1, fd);
    fseek(fd, 2, SEEK_SET);
    
    struct stat_macb* file_stat = get_path_timestamps(path);
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    fclose(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_fseek_nowrite(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, __func__, s_0s, ns_0ns, output_file, error_file, __func__);
    misc_nanosleep(ns_DELAY); 
    
    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    fseek(fd, 2, SEEK_SET);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY); 
    struct stat_macb* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    fclose(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_fsync_write_imm(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, __func__, s_0s, ns_0ns, output_file, error_file, __func__);
    misc_nanosleep(ns_DELAY); 
    
    int fd = open(path, O_WRONLY|O_RDONLY);
    if (fd == 0) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    write(fd, "Hallo", 5);
    fsync(fd);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY); 
    struct stat_macb* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    close(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_fsync_write(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, __func__, s_0s, ns_0ns, output_file, error_file, __func__);
    misc_nanosleep(ns_DELAY); 
    
    int fd = open(path, O_WRONLY|O_RDONLY);
    if (fd == 0) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    write(fd, "Hallo", 5);
    fsync(fd);
    
    struct stat_macb* file_stat = get_path_timestamps(path);
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    close(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_fsync_nowrite(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat_ensure_file_exists(dir_path, __func__, s_0s, ns_0ns, output_file, error_file, __func__);
    misc_nanosleep(ns_DELAY); 
    
    int fd = open(path, O_WRONLY|O_RDONLY);
    if (fd == 0) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    misc_nanosleep(ns_after_open);

    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    fsync(fd);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY); 
    struct stat_macb* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    close(fd);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}


#endif
