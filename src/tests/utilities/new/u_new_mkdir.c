#ifndef U_NEW_MKDIR_C
#define U_NEW_MKDIR_C

#include "u_new_mkdir.h"

int check_utilities_new_mkdir_new(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.new.mkdir.new/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_targetdir = misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    
    char* path_newdir = misc_concat(path_targetdir, "dir/");
    
    char* command = "mkdir ../targetdir/dir/";
    
    char** watch_array = misc_char_array3(path_pwd, path_targetdir, path_newdir);
    int watch_num = 3;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, NULL, path_targetdir, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = UPDATE_MANDATORY;
    r2[1] = NOUPDATE_OPTIONAL;
    r2[2] = UPDATE_MANDATORY;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = UPDATE_MANDATORY;
    r3[1] = UPDATE_MANDATORY;
    r3[2] = UPDATE_MANDATORY;
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    requirements[2] = r3;
    
    int result = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}

int check_utilities_new_mkdir_new_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.new.mkdir.new.mac/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_targetdir = misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    
    char* path_newdir = misc_concat(path_targetdir, "dir/");
    
    char* command = "mkdir ../targetdir/dir/";
    
    char** watch_array = misc_char_array1(path_newdir);
    int watch_num = 1;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, NULL, path_targetdir, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    struct stat_macb* file_stat = pi->multi_stat_after[0];
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat->st_mtim), &(file_stat->st_ctim)) != 0){
        log_warning(output_file, error_file, "%s - MAC not equal", __func__);
        result = 2;
    }
    
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}

int check_utilities_new_mkdir_existing(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.new.mkdir.existing/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_targetdir = misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    
    char* path_newdir = misc_concat_ensure_dir_exists(path_targetdir, "dir/", 0, 0, output_file, error_file, __func__);
    
    char* command = "mkdir ../targetdir/dir/";
    
    char** watch_array = misc_char_array3(path_pwd, path_targetdir, path_newdir);
    int watch_num = 3;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, NULL, path_targetdir, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = NOUPDATE_MANDATORY;
    r2[1] = NOUPDATE_MANDATORY;
    r2[2] = NOUPDATE_MANDATORY;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = NOUPDATE_MANDATORY;
    r3[1] = NOUPDATE_MANDATORY;
    r3[2] = NOUPDATE_MANDATORY;
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    requirements[2] = r3;
    
    int result = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}

#endif
