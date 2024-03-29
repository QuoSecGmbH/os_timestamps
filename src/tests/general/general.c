#ifndef GENERAL_C
#define GENERAL_C

#include "general.h"

int check_general_new_file_realtime(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat(dir_path, "general.new_file_realtime");
    
    struct timespec* ts_before = current_time_ns();
    
    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    fclose(fd);
    
    struct timespec* ts_after = current_time_ns();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    int result = result_MAC_updated(UPDATE_MANDATORY, UPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_general_new_file(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat(dir_path, "general.new_file");
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    fclose(fd);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    int result = result_MAC_updated(UPDATE_MANDATORY, UPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}


int check_general_new_file_mac_eq(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat(dir_path, "general.new_file_mac_eq");

    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    fclose(fd);
    
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat->st_mtim), &(file_stat->st_atim)) != 0 || misc_timespec_eq(&(file_stat->st_atim), &(file_stat->st_ctim)) != 0){
        log_warning(output_file, error_file, "check_general_new_file_mac_eq - MAC not equal");
        result = 2;
    }
    
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, NULL, NULL, file_stat);
    
    free(path);
    free(file_stat);
    
    return result;
}


int check_general_update_write_close(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists(dir_path, __func__, 0, ns_after_open, output_file, error_file, __func__);
    
    // Preparation
    FILE* fd = fopen(path, "ab");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    get_file_timestamps(fd); // stat
    misc_nanosleep(ns_DELAY); // Delay
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    // Actions
    fwrite("Hallo", 5, 1, fd);
    fclose(fd);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(path);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_general_update_read_close(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists(dir_path, __func__, 0, ns_after_open, output_file, error_file, __func__);
    
    
    FILE* fd = fopen(path, "rb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    get_file_timestamps(fd);
    misc_nanosleep(ns_DELAY);
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char buf[6];
    fread(buf, 5, 1, fd);
    fclose(fd);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, UPDATE_MANDATORY, NOUPDATE_OPTIONAL, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_general_update_write_fstat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists(dir_path, __func__, 0, ns_after_open, output_file, error_file, __func__);

    FILE* fd = fopen(path, "ab");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }    
    
    get_file_timestamps(fd);
    misc_nanosleep(ns_DELAY);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    fwrite("Hallo", 5, 1, fd);
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    fstat(fileno(fd), attr);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    free(attr);
    fclose(fd);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_general_update_write(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists(dir_path, __func__, 0, ns_after_open, output_file, error_file, __func__);
    
    FILE* fd = fopen(path, "ab");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    get_file_timestamps(fd);
    misc_nanosleep(ns_DELAY);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    fwrite("Hallo", 5, 1, fd);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    fclose(fd);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_general_update_write_stat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists(dir_path, __func__, 0, ns_after_open, output_file, error_file, __func__);
    
    FILE* fd = fopen(path, "ab");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    get_file_timestamps(fd);
    misc_nanosleep(ns_DELAY);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    fwrite("Hallo", 5, 1, fd);
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    stat(path, attr);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    free(attr);
    fclose(fd);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_general_update_read_fstat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists_filled(dir_path, __func__, 10, 0, ns_after_open, output_file, error_file, __func__);
    
    FILE* fd = fopen(path, "rb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    get_file_timestamps(fd);
    misc_nanosleep(ns_DELAY);
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char buf[6];
    fread(buf, 5, 1, fd);
    
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    fstat(fileno(fd), attr);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    free(attr);
    fclose(fd);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, UPDATE_MANDATORY, NOUPDATE_OPTIONAL, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_general_update_read_stat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists_filled(dir_path, __func__, 10, 0, ns_after_open, output_file, error_file, __func__);

    FILE* fd = fopen(path, "rb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    get_file_timestamps(fd);
    misc_nanosleep(ns_DELAY);
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char buf[6];
    fread(buf, 5, 1, fd);
    
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    stat(path, attr);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    free(attr);
    fclose(fd);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, UPDATE_MANDATORY, NOUPDATE_OPTIONAL, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_general_update_read(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists_filled(dir_path, __func__, 10, 0, ns_after_open, output_file, error_file, __func__);
    
    
    FILE* fd = fopen(path, "rb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    get_file_timestamps(fd);
    misc_nanosleep(ns_DELAY);
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char buf[6];
    fread(buf, 5, 1, fd);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY);
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    fclose(fd);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_MANDATORY, NOUPDATE_OPTIONAL, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_general_update_mark_read(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists_filled(dir_path, __func__, 10, 0, ns_after_open, output_file, error_file, __func__);
    
    FILE* fd = fopen(path, "rb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    get_file_timestamps(fd);
    misc_nanosleep(ns_DELAY);
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char buf[6];
    fread(buf, 5, 1, fd);
    
    struct stat_macb* file_stat = get_path_timestamps(path);
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    fclose(fd);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, UPDATE_MANDATORY, NOUPDATE_OPTIONAL, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_general_update_fopen_r(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists_filled(dir_path, __func__, 10, 0, ns_after_open, output_file, error_file, __func__);
    
    misc_nanosleep(ns_DELAY);
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    FILE* fd = fopen(path, "rb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    struct stat_macb* file_stat = get_path_timestamps(path);
    misc_nanosleep(ns_DELAY);
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    fclose(fd);
    
    int result = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_general_update_fopen_r_fstat_fclose(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists_filled(dir_path, __func__, 10, 0, ns_after_open, output_file, error_file, __func__);
    
    misc_nanosleep(ns_DELAY);
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    FILE* fd = fopen(path, "rb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    fstat(path, fd);
    fclose(fd);
    
    struct stat_macb* file_stat = get_path_timestamps(path);
    misc_nanosleep(ns_DELAY);
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    free(attr);
    
    int result = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}



#endif
