#ifndef GENERAL_C
#define GENERAL_C

#include "general.h"

int check_general_new_file_realtime(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat(dir_path, "general.new_file_realtime");
    
    struct timespec* ts_before = current_time_ns();
    
    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "check_general_new_file - error opening/creating file");
        return 1;
    }
    
    fclose(fd);
    
    struct timespec* ts_after = current_time_ns();
    struct stat* file_stat = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_mtim), ts_after) != 0){
        log_warning(output_file, error_file, "check_general_new_file - M not updated");
        result = 2;
    }
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_atim), ts_after) != 0){
        log_warning(output_file, error_file, "check_general_new_file - A not updated");
        result = 2;
    }
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_ctim), ts_after) != 0){
        log_warning(output_file, error_file, "check_general_new_file - C not updated");
        result = 2;
    }
    
    if (result != 0){
        log_info(output_file, error_file, "Before: %lds %ldns ; After: %lds %ldns", ts_before->tv_sec, ts_before->tv_nsec, ts_after->tv_sec, ts_after->tv_nsec);
        log_info(output_file, error_file, "M: %lds %ldns", file_stat->st_mtim.tv_sec, file_stat->st_mtim.tv_nsec);
        log_info(output_file, error_file, "A: %lds %ldns", file_stat->st_atim.tv_sec, file_stat->st_atim.tv_nsec);
        log_info(output_file, error_file, "C: %lds %ldns", file_stat->st_ctim.tv_sec, file_stat->st_ctim.tv_nsec);
    }
    
    return result;
}

int check_general_new_file(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat(dir_path, "general.new_file");
    
    struct timespec* ts_before = current_time_ns_coarse();
    
    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "check_general_new_file - error opening/creating file");
        return 1;
    }
    
    fclose(fd);
    
    struct timespec* ts_after = current_time_ns_coarse();
    struct stat* file_stat = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_mtim), ts_after) != 0){
        log_warning(output_file, error_file, "check_general_new_file - M not updated");
        result = 2;
    }
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_atim), ts_after) != 0){
        log_warning(output_file, error_file, "check_general_new_file - A not updated");
        result = 2;
    }
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_ctim), ts_after) != 0){
        log_warning(output_file, error_file, "check_general_new_file - C not updated");
        result = 2;
    }
    
    if (result != 0){
        log_info(output_file, error_file, "Before: %lds %ldns ; After: %lds %ldns", ts_before->tv_sec, ts_before->tv_nsec, ts_after->tv_sec, ts_after->tv_nsec);
        log_info(output_file, error_file, "M: %lds %ldns", file_stat->st_mtim.tv_sec, file_stat->st_mtim.tv_nsec);
        log_info(output_file, error_file, "A: %lds %ldns", file_stat->st_atim.tv_sec, file_stat->st_atim.tv_nsec);
        log_info(output_file, error_file, "C: %lds %ldns", file_stat->st_ctim.tv_sec, file_stat->st_ctim.tv_nsec);
    }
    
    return result;
}



int check_general_new_file_mac_eq(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat(dir_path, "general.new_file_mac_eq");

    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "check_general_new_file - error opening/creating file");
        return 1;
    }
    
    fclose(fd);
    
    struct stat* file_stat = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat->st_mtim), &(file_stat->st_atim)) != 0 || misc_timespec_eq(&(file_stat->st_atim), &(file_stat->st_ctim)) != 0){
        log_warning(output_file, error_file, "check_general_new_file_mac_eq - MAC not equal");
        result = 2;
    }
    
    if (result != 0){
        log_info(output_file, error_file, "M: %lds %ldns", file_stat->st_mtim.tv_sec, file_stat->st_mtim.tv_nsec);
        log_info(output_file, error_file, "A: %lds %ldns", file_stat->st_atim.tv_sec, file_stat->st_atim.tv_nsec);
        log_info(output_file, error_file, "C: %lds %ldns", file_stat->st_ctim.tv_sec, file_stat->st_ctim.tv_nsec);
    }
    
    return result;
}


int check_general_update_write_close(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat(dir_path, "general.new_file");
    
    struct timespec* ts_before = current_time_ns_coarse();
    
    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "check_general_update_write_close - error opening/creating file");
        return 1;
    }
    fwrite("Hallo", 5, 1, fd);
    
    fclose(fd);
    
    struct timespec* ts_after = current_time_ns_coarse();
    struct stat* file_stat = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_mtim), ts_after) != 0){
        log_warning(output_file, error_file, "check_general_update_write_close - M not updated");
        result = 2;
    }
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_atim), ts_after) == 0){
        log_warning(output_file, error_file, "check_general_update_write_close - A updated");
    }
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_ctim), ts_after) != 0){
        log_warning(output_file, error_file, "check_general_update_write_close - C not updated");
        result = 2;
    }
    
    if (result != 0){
        log_info(output_file, error_file, "Before: %lds %ldns ; After: %lds %ldns", ts_before->tv_sec, ts_before->tv_nsec, ts_after->tv_sec, ts_after->tv_nsec);
        log_info(output_file, error_file, "M: %lds %ldns", file_stat->st_mtim.tv_sec, file_stat->st_mtim.tv_nsec);
        log_info(output_file, error_file, "A: %lds %ldns", file_stat->st_atim.tv_sec, file_stat->st_atim.tv_nsec);
        log_info(output_file, error_file, "C: %lds %ldns", file_stat->st_ctim.tv_sec, file_stat->st_ctim.tv_nsec);
    }
    
    return result;
}

int check_general_update_read_close(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat(dir_path, "general.new_file");
    
    struct timespec* ts_before = current_time_ns_coarse();
    
    FILE* fd = fopen(path, "rb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "check_general_update_read_close - error opening/creating file");
        return 1;
    }
    
    char buf[6];
    fread(buf, 5, 1, fd);
    
    fclose(fd);
    
    struct timespec* ts_after = current_time_ns_coarse();
    struct stat* file_stat = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_mtim), ts_after) == 0){
        log_warning(output_file, error_file, "check_general_update_read_close - M updated");
    }
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_atim), ts_after) != 0){
        log_warning(output_file, error_file, "check_general_update_read_close - A not updated");
        result = 2;
    }
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_ctim), ts_after) == 0){
        log_warning(output_file, error_file, "check_general_update_read_close - C updated");
    }
    
    if (result != 0){
        log_info(output_file, error_file, "Before: %lds %ldns ; After: %lds %ldns", ts_before->tv_sec, ts_before->tv_nsec, ts_after->tv_sec, ts_after->tv_nsec);
        log_info(output_file, error_file, "M: %lds %ldns", file_stat->st_mtim.tv_sec, file_stat->st_mtim.tv_nsec);
        log_info(output_file, error_file, "A: %lds %ldns", file_stat->st_atim.tv_sec, file_stat->st_atim.tv_nsec);
        log_info(output_file, error_file, "C: %lds %ldns", file_stat->st_ctim.tv_sec, file_stat->st_ctim.tv_nsec);
    }
    
    return result;
}

int check_general_update_write_stat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat(dir_path, "general.new_file");
    
    struct timespec* ts_before = current_time_ns_coarse();
    
    FILE* fd = fopen(path, "wb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "check_general_update_write_stat - error opening/creating file");
        return 1;
    }
    fwrite("Hallo", 5, 1, fd);
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    fstat(fd, attr);
    
    struct timespec* ts_after = current_time_ns_coarse();
    struct stat* file_stat = get_path_timestamps(path);
    
    
    fclose(fd);
    
    int result = 0;
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_mtim), ts_after) != 0){
        log_warning(output_file, error_file, "check_general_update_write_stat - M not updated");
        result = 2;
    }
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_atim), ts_after) == 0){
        log_warning(output_file, error_file, "check_general_update_write_stat - A updated");
    }
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_ctim), ts_after) != 0){
        log_warning(output_file, error_file, "check_general_update_write_stat - C not updated");
        result = 2;
    }
    
    if (result != 0){
        log_info(output_file, error_file, "Before: %lds %ldns ; After: %lds %ldns", ts_before->tv_sec, ts_before->tv_nsec, ts_after->tv_sec, ts_after->tv_nsec);
        log_info(output_file, error_file, "M: %lds %ldns", file_stat->st_mtim.tv_sec, file_stat->st_mtim.tv_nsec);
        log_info(output_file, error_file, "A: %lds %ldns", file_stat->st_atim.tv_sec, file_stat->st_atim.tv_nsec);
        log_info(output_file, error_file, "C: %lds %ldns", file_stat->st_ctim.tv_sec, file_stat->st_ctim.tv_nsec);
    }
    
    return result;
}

int check_general_update_read_stat(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat(dir_path, "general.new_file");
    
    struct timespec* ts_before = current_time_ns_coarse();
    
    FILE* fd = fopen(path, "rb");
    if (fd == NULL) {
        log_warning(output_file, error_file, "check_general_update_read_stat - error opening/creating file");
        return 1;
    }
    
    char buf[6];
    fread(buf, 5, 1, fd);
    
    struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
    fstat(fd, attr);
    
    
    struct timespec* ts_after = current_time_ns_coarse();
    struct stat* file_stat = get_path_timestamps(path);
    
    fclose(fd);
    
    int result = 0;
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_mtim), ts_after) == 0){
        log_warning(output_file, error_file, "check_general_update_read_stat - M updated");
    }
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_atim), ts_after) != 0){
        log_warning(output_file, error_file, "check_general_update_read_stat - A not updated");
        result = 2;
    }
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_ctim), ts_after) == 0){
        log_warning(output_file, error_file, "check_general_update_read_stat - C updated");
    }
    
    if (result != 0){
        log_info(output_file, error_file, "Before: %lds %ldns ; After: %lds %ldns", ts_before->tv_sec, ts_before->tv_nsec, ts_after->tv_sec, ts_after->tv_nsec);
        log_info(output_file, error_file, "M: %lds %ldns", file_stat->st_mtim.tv_sec, file_stat->st_mtim.tv_nsec);
        log_info(output_file, error_file, "A: %lds %ldns", file_stat->st_atim.tv_sec, file_stat->st_atim.tv_nsec);
        log_info(output_file, error_file, "C: %lds %ldns", file_stat->st_ctim.tv_sec, file_stat->st_ctim.tv_nsec);
    }
    
    return result;
}

int check_general_update_chmod(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = (char*) misc_concat(dir_path, "general.new_file");
    
    struct timespec* ts_before = current_time_ns_coarse();
    
    char mode[] = "0777";
    int i;
    i = strtol(mode, 0, 8);
    chmod(path,i) ;
    
    struct timespec* ts_after = current_time_ns_coarse();
    struct stat* file_stat = get_path_timestamps(path);
    
    int result = 0;
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_mtim), ts_after) == 0){
        log_warning(output_file, error_file, "check_general_update_chmod - M updated");
    }
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_atim), ts_after) == 0){
        log_warning(output_file, error_file, "check_general_update_chmod - A updated");
    }
    if (misc_timespec_leq_leq(ts_before, &(file_stat->st_ctim), ts_after) != 0){
        log_warning(output_file, error_file, "check_general_update_chmod - C not updated");
        result = 2;
    }
    
    if (result != 0){
        log_info(output_file, error_file, "Before: %lds %ldns ; After: %lds %ldns", ts_before->tv_sec, ts_before->tv_nsec, ts_after->tv_sec, ts_after->tv_nsec);
        log_info(output_file, error_file, "M: %lds %ldns", file_stat->st_mtim.tv_sec, file_stat->st_mtim.tv_nsec);
        log_info(output_file, error_file, "A: %lds %ldns", file_stat->st_atim.tv_sec, file_stat->st_atim.tv_nsec);
        log_info(output_file, error_file, "C: %lds %ldns", file_stat->st_ctim.tv_sec, file_stat->st_ctim.tv_nsec);
    }
    
    return result;
}

#endif
