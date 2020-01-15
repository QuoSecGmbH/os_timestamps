#ifndef I_FILE_NEW_C
#define I_FILE_NEW_C

#include "i_file_new.h"

int check_interfaces_file_new_mkdtemp_new(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){ 
    char* template = misc_concat(dir_path, (char*) "interfaces.files.new.mkdtemp.new.XXXXXX");
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char* path_dir = mkdtemp(template);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat_macb* file_stat = get_path_timestamps(path_dir);
    
    int result = result_MAC_updated(UPDATE_MANDATORY, UPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(template);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_interfaces_file_new_mkdtemp_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* template = misc_concat(dir_path, (char*) "interfaces.files.new.mkdtemp.mac.new.XXXXXX");
    
    char* path_dir = mkdtemp(template);
    
    struct stat_macb* file_stat = get_path_timestamps(path_dir);
    int result = 0;
    if (misc_timespec_eq(&(file_stat->st_mtim), &(file_stat->st_atim)) != 0 || misc_timespec_eq(&(file_stat->st_atim), &(file_stat->st_ctim)) != 0){
        log_warning(output_file, error_file, "%s - MAC not equal", __func__);
        result = 2;
    }
    
    free(template);
    free(file_stat);
    
    return result;
}

int check_interfaces_file_new_mkdtemp_mac_1s(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* template = misc_concat(dir_path, (char*) "interfaces.files.new.mkdtemp.mac_1s.new.XXXXXX");
    
    char* path_dir = mkdtemp(template);
    misc_sleep(1);
    
    struct stat_macb* file_stat = get_path_timestamps(path_dir);
    int result = 0;
    if (misc_timespec_eq(&(file_stat->st_mtim), &(file_stat->st_atim)) != 0 || misc_timespec_eq(&(file_stat->st_atim), &(file_stat->st_ctim)) != 0){
        log_warning(output_file, error_file, "%s - MAC not equal", __func__);
        result = 2;
    }
    
    free(template);
    free(file_stat);
    
    return result;
}

int check_interfaces_file_new_mkdir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.files.new.mkdir/");
    char* path_new_dir = misc_concat(path_dir, (char*) "mkdir/");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    mkdir(path_new_dir, 0700);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* dir_stat = get_path_timestamps(path_new_dir);
    struct stat_macb* parent_dir_stat = get_path_timestamps(path_dir);
    
    int dir_result = result_MAC_updated(UPDATE_MANDATORY, UPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    int parent_dir_result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, parent_dir_stat);
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, dir_result, ts_before, ts_after, dir_stat, "dir");
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, parent_dir_result, ts_before, ts_after, parent_dir_stat, "parent dir");
    
    int result = misc_max2(dir_result, parent_dir_result);
    
    free(path_dir);
    free(path_new_dir);
    free(ts_before);
    free(ts_after);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_new_mkdir_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.files.new.mkdir.mac/");
    char* path_new_dir = misc_concat(path_dir, (char*) "mkdir/");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    mkdir(path_new_dir, 0700);
    
    struct stat_macb* dir_stat = get_path_timestamps(path_new_dir);

    int result = 0;
    if (misc_timespec_eq(&(dir_stat->st_mtim), &(dir_stat->st_atim)) != 0 || misc_timespec_eq(&(dir_stat->st_atim), &(dir_stat->st_ctim)) != 0){
        log_warning(output_file, error_file, "%s - MAC not equal", __func__);
        result = 2;
    }
    
    free(path_dir);
    free(path_new_dir);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_new_mkdir_mac_1s(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.files.new.mkdir.mac_1s/");
    char* path_new_dir = misc_concat(path_dir, (char*) "mkdir/");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    mkdir(path_new_dir, 0700);
    misc_sleep(1);
    
    struct stat_macb* dir_stat = get_path_timestamps(path_new_dir);
    
    int result = 0;
    if (misc_timespec_eq(&(dir_stat->st_mtim), &(dir_stat->st_atim)) != 0 || misc_timespec_eq(&(dir_stat->st_atim), &(dir_stat->st_ctim)) != 0){
        log_warning(output_file, error_file, "%s - MAC not equal", __func__);
        result = 2;
    }
    
    free(path_dir);
    free(path_new_dir);
    free(dir_stat);
    
    return result;
}


int check_interfaces_file_new_mkdirat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.files.new.mkdirat/");
    char* path_new_dir = misc_concat(path_dir, (char*) "mkdirat/");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    mkdirat(AT_FDCWD, path_new_dir, S_IRWXU | S_IRWXG);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* dir_stat = get_path_timestamps(path_new_dir);
    struct stat_macb* parent_dir_stat = get_path_timestamps(path_dir);
    
    int dir_result = result_MAC_updated(UPDATE_MANDATORY, UPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    int parent_dir_result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, parent_dir_stat);
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, dir_result, ts_before, ts_after, dir_stat, "dir");
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, parent_dir_result, ts_before, ts_after, parent_dir_stat, "parent dir");
    
    int result = misc_max2(dir_result, parent_dir_result);
    
    free(path_dir);
    free(path_new_dir);
    free(ts_before);
    free(ts_after);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_new_mkdirat_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.files.new.mkdirat.mac/");
    char* path_new_dir = misc_concat(path_dir, (char*) "mkdirat/");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    mkdirat(AT_FDCWD, path_new_dir, S_IRWXU | S_IRWXG);
    
    struct stat_macb* dir_stat = get_path_timestamps(path_new_dir);

    int result = 0;
    if (misc_timespec_eq(&(dir_stat->st_mtim), &(dir_stat->st_atim)) != 0 || misc_timespec_eq(&(dir_stat->st_atim), &(dir_stat->st_ctim)) != 0){
        log_warning(output_file, error_file, "%s - MAC not equal", __func__);
        result = 2;
    }
    
    free(path_dir);
    free(path_new_dir);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_new_mkdirat_mac_1s(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.files.new.mkdirat.mac_1s/");
    char* path_new_dir = misc_concat(path_dir, (char*) "mkdirat/");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    mkdirat(AT_FDCWD, path_new_dir, S_IRWXU | S_IRWXG);
    misc_sleep(1);
    
    struct stat_macb* dir_stat = get_path_timestamps(path_new_dir);
    
    int result = 0;
    if (misc_timespec_eq(&(dir_stat->st_mtim), &(dir_stat->st_atim)) != 0 || misc_timespec_eq(&(dir_stat->st_atim), &(dir_stat->st_ctim)) != 0){
        log_warning(output_file, error_file, "%s - MAC not equal", __func__);
        result = 2;
    }
    
    free(path_dir);
    free(path_new_dir);
    free(dir_stat);
    
    return result;
}

int check_interfaces_file_new_mkfifo(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.files.new.mkfifo/");
    char* path_fifo = misc_concat(path_dir, (char*) "mkfifo");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    mkfifo(path_fifo, 0700);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* fifo_stat = get_path_timestamps(path_fifo);
    struct stat_macb* parent_dir_stat = get_path_timestamps(path_dir);
    
    int fifo_result = result_MAC_updated(UPDATE_MANDATORY, UPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, fifo_stat);
    int parent_dir_result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, parent_dir_stat);
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, fifo_result, ts_before, ts_after, fifo_stat, "dir");
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, parent_dir_result, ts_before, ts_after, parent_dir_stat, "parent dir");
    
    int result = misc_max2(fifo_result, parent_dir_result);
    
    free(path_dir);
    free(path_fifo);
    free(ts_before);
    free(ts_after);
    free(fifo_stat);
    
    return result;
}

int check_interfaces_file_new_mkfifo_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.files.new.mkfifo.mac/");
    char* path_fifo = misc_concat(path_dir, (char*) "mkfifo");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    mkfifo(path_fifo, 0700);
    
    struct stat_macb* fifo_stat = get_path_timestamps(path_fifo);

    int result = 0;
    if (misc_timespec_eq(&(fifo_stat->st_mtim), &(fifo_stat->st_atim)) != 0 || misc_timespec_eq(&(fifo_stat->st_atim), &(fifo_stat->st_ctim)) != 0){
        log_warning(output_file, error_file, "%s - MAC not equal", __func__);
        result = 2;
    }
    
    free(path_dir);
    free(path_fifo);
    free(fifo_stat);
    
    return result;
}

int check_interfaces_file_new_mkfifo_mac_1s(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.files.new.mkfifo.mac_1s/");
    char* path_fifo = misc_concat(path_dir, (char*) "mkfifo");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    mkfifo(path_fifo, 0700);
    misc_sleep(1);
    
    struct stat_macb* fifo_stat = get_path_timestamps(path_fifo);

    int result = 0;
    if (misc_timespec_eq(&(fifo_stat->st_mtim), &(fifo_stat->st_atim)) != 0 || misc_timespec_eq(&(fifo_stat->st_atim), &(fifo_stat->st_ctim)) != 0){
        log_warning(output_file, error_file, "%s - MAC not equal", __func__);
        result = 2;
    }
    
    free(path_dir);
    free(path_fifo);
    free(fifo_stat);
    
    return result;
}

int check_interfaces_file_new_mkfifoat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.files.new.mkfifoat/");
    char* path_fifo = misc_concat(path_dir, (char*) "mkfifo");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    mkfifoat(AT_FDCWD, path_fifo, 0700);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* fifo_stat = get_path_timestamps(path_fifo);
    struct stat_macb* parent_dir_stat = get_path_timestamps(path_dir);
    
    int fifo_result = result_MAC_updated(UPDATE_MANDATORY, UPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, fifo_stat);
    int parent_dir_result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, parent_dir_stat);
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, fifo_result, ts_before, ts_after, fifo_stat, "dir");
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, parent_dir_result, ts_before, ts_after, parent_dir_stat, "parent dir");
    
    int result = misc_max2(fifo_result, parent_dir_result);
    
    free(path_dir);
    free(path_fifo);
    free(ts_before);
    free(ts_after);
    free(fifo_stat);
    
    return result;
}

int check_interfaces_file_new_mkfifoat_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.files.new.mkfifoat.mac/");
    char* path_fifo = misc_concat(path_dir, (char*) "mkfifo");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    mkfifoat(AT_FDCWD, path_fifo, 0700);
    
    struct stat_macb* fifo_stat = get_path_timestamps(path_fifo);

    int result = 0;
    if (misc_timespec_eq(&(fifo_stat->st_mtim), &(fifo_stat->st_atim)) != 0 || misc_timespec_eq(&(fifo_stat->st_atim), &(fifo_stat->st_ctim)) != 0){
        log_warning(output_file, error_file, "%s - MAC not equal", __func__);
        result = 2;
    }
    
    free(path_dir);
    free(path_fifo);
    free(fifo_stat);
    
    return result;
}

int check_interfaces_file_new_mkfifoat_mac_1s(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat(dir_path, (char*) "interfaces.files.new.mkfifoat.mac_1s/");
    char* path_fifo = misc_concat(path_dir, (char*) "mkfifo");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    mkfifoat(AT_FDCWD, path_fifo, 0700);
    misc_sleep(1);
    
    struct stat_macb* fifo_stat = get_path_timestamps(path_fifo);

    int result = 0;
    if (misc_timespec_eq(&(fifo_stat->st_mtim), &(fifo_stat->st_atim)) != 0 || misc_timespec_eq(&(fifo_stat->st_atim), &(fifo_stat->st_ctim)) != 0){
        log_warning(output_file, error_file, "%s - MAC not equal", __func__);
        result = 2;
    }
    
    free(path_dir);
    free(path_fifo);
    free(fifo_stat);
    
    return result;
}

int check_interfaces_file_new_mkpipe(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    int pipefd[2];
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    pipe(pipefd);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    struct stat_macb* pipe0_stat = get_fd_timestamps(pipefd[0]);
    struct stat_macb* pipe1_stat = get_fd_timestamps(pipefd[1]);

    int pipe0_result = result_MAC_updated(UPDATE_MANDATORY, UPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, pipe0_stat);
    int pipe1_result = result_MAC_updated(UPDATE_MANDATORY, UPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, pipe1_stat);
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, pipe0_result, ts_before, ts_after, pipe0_stat, "pipe0");
    log_info_ts_stat_on_error_message(output_file, error_file, __func__, pipe1_result, ts_before, ts_after, pipe1_stat, "pipe1");
    
    int result = misc_max2(pipe0_result, pipe1_result);
    
    free(pipe0_stat);
    free(pipe1_stat);
    free(ts_before);
    free(ts_after);
    
    return result;
}


#endif
