#ifndef I_FOPEN_C
#define I_FOPEN_C

#include "i_fopen.h"

int helper_interfaces_file_fopen_new_writemode(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path, char* mode){
    char* path_generic = (char*) misc_concat(dir_path, "interfaces.file.fopen.new.writemode");
    char* path_dot = (char*) misc_concat(path_generic, ".");
    char* path_mode = (char*) misc_concat(path_dot, mode);
    
    if (misc_file_exists(path_mode) == 0){
        log_warning(output_file, error_file, "%s - %s %s", __func__, path_mode, "already exists");
    }
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    FILE* fd = fopen(path_mode, mode);
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_path_timestamps(path_mode);
    struct stat* dir_stat = get_path_timestamps(dir_path);
      
    int result_file = result_MAC_updated(UPDATE_MANDATORY, UPDATE_MANDATORY, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    int result_dir = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result_file, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result_dir, ts_before, ts_after, dir_stat);
    
    fclose(fd);
    
    free(path_generic);
    free(path_dot);
    free(path_mode);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    free(dir_stat);
    
    int result = misc_max2(result_file, result_dir);
    return result; 
}

int check_interfaces_file_fopen_new_W(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_new_writemode(csv_file, output_file, error_file, dir_path, "w");
}

int check_interfaces_file_fopen_new_WB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_new_writemode(csv_file, output_file, error_file, dir_path, "wb");
}

int check_interfaces_file_fopen_new_A(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_new_writemode(csv_file, output_file, error_file, dir_path, "a");
}

int check_interfaces_file_fopen_new_AB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_new_writemode(csv_file, output_file, error_file, dir_path, "ab");
}
int check_interfaces_file_fopen_new_WP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_new_writemode(csv_file, output_file, error_file, dir_path, "w+");
}

int check_interfaces_file_fopen_new_WBP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_new_writemode(csv_file, output_file, error_file, dir_path, "wb+");
}

int check_interfaces_file_fopen_new_WPB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_new_writemode(csv_file, output_file, error_file, dir_path, "w+b");
}

int check_interfaces_file_fopen_new_AP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_new_writemode(csv_file, output_file, error_file, dir_path, "a+");
}

int check_interfaces_file_fopen_new_ABP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_new_writemode(csv_file, output_file, error_file, dir_path, "ab+");
}

int check_interfaces_file_fopen_new_APB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_new_writemode(csv_file, output_file, error_file, dir_path, "a+b");
}

int helper_interfaces_file_fopen_existing_writemode(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path, char* mode){
    char* path_generic = (char*) misc_concat(dir_path, "interfaces.file.fopen.existing.writemode");
    char* path_dot = (char*) misc_concat(path_generic, ".");
    char* path_mode = (char*) misc_concat_ensure_file_exists(path_dot, mode, s_0s, ns_after_open, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    FILE* fd = fopen(path_mode, mode);
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_path_timestamps(path_mode);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    fclose(fd);
    
    free(path_generic);
    free(path_dot);
    free(path_mode);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_fopen_existing_W(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_existing_writemode(csv_file, output_file, error_file, dir_path, "w");
}

int check_interfaces_file_fopen_existing_WB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_existing_writemode(csv_file, output_file, error_file, dir_path, "wb");
}

int check_interfaces_file_fopen_existing_WP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_existing_writemode(csv_file, output_file, error_file, dir_path, "w+");
}

int check_interfaces_file_fopen_existing_WBP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_existing_writemode(csv_file, output_file, error_file, dir_path, "wb+");
}

int check_interfaces_file_fopen_existing_WPB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_existing_writemode(csv_file, output_file, error_file, dir_path, "w+b");
}

int helper_interfaces_file_fopen_fwrite_existing_writemode(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path, char* mode){
    char* path_generic = (char*) misc_concat(dir_path, "interfaces.file.fopen_fwrite.existing.writemode");
    char* path_dot = (char*) misc_concat(path_generic, ".");
    char* path_mode = (char*) misc_concat_ensure_file_exists(path_dot, mode, s_0s, ns_after_open, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    FILE* fd = fopen(path_mode, mode);
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    fwrite("Hihallo", 7, 1, fd);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_path_timestamps(path_mode);
      
    int result = result_MAC_updated(UPDATE_MANDATORY, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    fclose(fd);
    
    free(path_generic);
    free(path_dot);
    free(path_mode);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_fopen_fwrite_existing_W(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fwrite_existing_writemode(csv_file, output_file, error_file, dir_path, "w");
}

int check_interfaces_file_fopen_fwrite_existing_WB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fwrite_existing_writemode(csv_file, output_file, error_file, dir_path, "wb");
}

int check_interfaces_file_fopen_fwrite_existing_WP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fwrite_existing_writemode(csv_file, output_file, error_file, dir_path, "w+");
}

int check_interfaces_file_fopen_fwrite_existing_WBP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fwrite_existing_writemode(csv_file, output_file, error_file, dir_path, "wb+");
}

int check_interfaces_file_fopen_fwrite_existing_WPB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fwrite_existing_writemode(csv_file, output_file, error_file, dir_path, "w+b");
}

int check_interfaces_file_fopen_fwrite_existing_RP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fwrite_existing_writemode(csv_file, output_file, error_file, dir_path, "r+");
}

int check_interfaces_file_fopen_fwrite_existing_RBP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fwrite_existing_writemode(csv_file, output_file, error_file, dir_path, "rb+");
}

int check_interfaces_file_fopen_fwrite_existing_RPB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fwrite_existing_writemode(csv_file, output_file, error_file, dir_path, "r+b");
}


int helper_interfaces_file_fopen_fwrite_existing_dir_writemode(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path, char* mode){
    char* path_generic = (char*) misc_concat(dir_path, "interfaces.file.fopen.existing.dir.writemode");
    char* path_dot = (char*) misc_concat(path_generic, ".");
    char* path_mode = (char*) misc_concat_ensure_file_exists(path_dot, mode, s_0s, ns_after_open, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    FILE* fd = fopen(path_mode, mode);
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    fwrite("Hihallo", 7, 1, fd);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* dir_stat = get_path_timestamps(dir_path);
      
    int result = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, dir_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, dir_stat);
    
    fclose(fd);
    
    free(path_generic);
    free(path_dot);
    free(path_mode);
    free(ts_before);
    free(ts_after);
    free(dir_stat);
    
    return result; 
}

int check_interfaces_file_fopen_fwrite_existing_dir_W(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fwrite_existing_dir_writemode(csv_file, output_file, error_file, dir_path, "w");
}

int check_interfaces_file_fopen_fwrite_existing_dir_WB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fwrite_existing_dir_writemode(csv_file, output_file, error_file, dir_path, "wb");
}

int check_interfaces_file_fopen_fwrite_existing_dir_WP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fwrite_existing_dir_writemode(csv_file, output_file, error_file, dir_path, "w+");
}

int check_interfaces_file_fopen_fwrite_existing_dir_WBP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fwrite_existing_dir_writemode(csv_file, output_file, error_file, dir_path, "wb+");
}

int check_interfaces_file_fopen_fwrite_existing_dir_WPB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fwrite_existing_dir_writemode(csv_file, output_file, error_file, dir_path, "w+b");
}

int check_interfaces_file_fopen_fwrite_existing_dir_RP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fwrite_existing_dir_writemode(csv_file, output_file, error_file, dir_path, "r+");
}

int check_interfaces_file_fopen_fwrite_existing_dir_RBP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fwrite_existing_dir_writemode(csv_file, output_file, error_file, dir_path, "rb+");
}

int check_interfaces_file_fopen_fwrite_existing_dir_RPB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fwrite_existing_dir_writemode(csv_file, output_file, error_file, dir_path, "r+b");
}

int helper_interfaces_file_fopen_existing_readmode(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path, char* mode){
    char* path_generic = (char*) misc_concat(dir_path, "interfaces.file.fopen.existing.readmode");
    char* path_dot = (char*) misc_concat(path_generic, ".");
    char* path_mode = (char*) misc_concat_ensure_file_exists(path_dot, mode, s_0s, ns_after_open, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    FILE* fd = fopen(path_mode, mode);
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_path_timestamps(path_mode);
      
    int result = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    fclose(fd);
    
    free(path_generic);
    free(path_dot);
    free(path_mode);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_fopen_existing_R(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_existing_readmode(csv_file, output_file, error_file, dir_path, "r");
}

int check_interfaces_file_fopen_existing_RB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_existing_readmode(csv_file, output_file, error_file, dir_path, "rb");
}

int check_interfaces_file_fopen_existing_RP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_existing_readmode(csv_file, output_file, error_file, dir_path, "r+");
}

int check_interfaces_file_fopen_existing_RBP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_existing_readmode(csv_file, output_file, error_file, dir_path, "rb+");
}

int check_interfaces_file_fopen_existing_RPB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_existing_readmode(csv_file, output_file, error_file, dir_path, "r+b");
}


int helper_interfaces_file_fopen_fread_existing_readmode(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path, char* mode){
    char* path_generic = (char*) misc_concat(dir_path, "interfaces.file.fopen_fread.existing.readmode");
    char* path_dot = (char*) misc_concat(path_generic, ".");
    char* path_mode = (char*) misc_concat_ensure_file_exists_filled(path_dot, mode, 4, s_0s, ns_after_open, output_file, error_file, __func__);

    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    FILE* fd = fopen(path_mode, mode);
    if (fd == NULL) {
        log_warning(output_file, error_file, "%s - %s", __func__, "error opening/creating file");
        return 1;
    }
    
    char* buf = (char*) calloc(3, sizeof(char));
    int n_read = fread(buf, 1, 2, fd);
    
    if (n_read != 2){
        log_warning(output_file, error_file, "%s - %s", __func__, "could not read data from file");
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_path_timestamps(path_mode);
      
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, UPDATE_MANDATORY, NOUPDATE_OPTIONAL, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(buf);
    fclose(fd);
    
    free(path_generic);
    free(path_dot);
    free(path_mode);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_fopen_fread_existing_R(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fread_existing_readmode(csv_file, output_file, error_file, dir_path, "r");
}

int check_interfaces_file_fopen_fread_existing_RB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fread_existing_readmode(csv_file, output_file, error_file, dir_path, "rb");
}

int check_interfaces_file_fopen_fread_existing_RP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fread_existing_readmode(csv_file, output_file, error_file, dir_path, "r+");
}

int check_interfaces_file_fopen_fread_existing_RBP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fread_existing_readmode(csv_file, output_file, error_file, dir_path, "rb+");
}

int check_interfaces_file_fopen_fread_existing_RPB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fread_existing_readmode(csv_file, output_file, error_file, dir_path, "r+b");
}

int helper_interfaces_file_fopen_fread_existing_writemode(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path, char* mode){
    char* path_generic = (char*) misc_concat(dir_path, "interfaces.file.fopen_fread.existing.writemode");
    char* path_dot = (char*) misc_concat(path_generic, ".");
    char* path_mode = (char*) misc_concat_ensure_file_exists_filled(path_dot, mode, 4, s_0s, ns_after_open, output_file, error_file, __func__);
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    FILE* f = fopen(path_mode, mode);
    char* buf = (char*) calloc(3, sizeof(char));
    int n_read = fread(buf, 1, 2, f);
    
    if (n_read != 2){
        log_warning(output_file, error_file, "%s - %s", __func__, "could not read data from file");
        return 1;
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat* file_stat = get_path_timestamps(path_mode);
      
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, UPDATE_MANDATORY, NOUPDATE_OPTIONAL, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(buf);
    fclose(f);
    
    free(path_generic);
    free(path_dot);
    free(path_mode);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result; 
}

int check_interfaces_file_fopen_fread_existing_WP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fread_existing_writemode(csv_file, output_file, error_file, dir_path, "w+");
}

int check_interfaces_file_fopen_fread_existing_WBP(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fread_existing_writemode(csv_file, output_file, error_file, dir_path, "wb+");
}

int check_interfaces_file_fopen_fread_existing_WPB(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
  return helper_interfaces_file_fopen_fread_existing_writemode(csv_file, output_file, error_file, dir_path, "w+b");
}



#endif
