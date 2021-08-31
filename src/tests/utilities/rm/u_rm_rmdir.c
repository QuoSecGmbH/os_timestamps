#ifndef U_RMDIR_C
#define U_RMDIR_C

#include "u_rm_rmdir.h"

int check_utilities_rm_rmdir_empty(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.rm.rmdir.empty/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_targetdir = misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    
    misc_concat_ensure_dir_exists(path_targetdir, "dir/", 0, 0, output_file, error_file, __func__);
    
    char* command = "rmdir ../targetdir/dir/";
    
    char** watch_array = misc_char_array2(path_pwd, path_targetdir);
    int watch_num = 2;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, NULL, path_targetdir, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = UPDATE_MANDATORY;
    r2[1] = NOUPDATE_MANDATORY;
    r2[2] = UPDATE_MANDATORY;
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    
    int result = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}

int check_utilities_rm_rmdir_notempty(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.rm.rmdir.notempty/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_targetdir = misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    
    char* path_rmdir_dir = misc_concat_ensure_dir_exists(path_targetdir, "dir/", 0, 0, output_file, error_file, __func__);
    char* path_file = misc_concat_ensure_file_exists_filled(path_rmdir_dir, "file", 7, 0, 0, output_file, error_file, __func__);
    
    char* command = "rmdir ../targetdir/dir/";
    
    char** watch_array = misc_char_array4(path_pwd, path_targetdir, path_rmdir_dir, path_file);
    int watch_num = 4;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, NULL, path_targetdir, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = NOUPDATE_OPTIONAL;
    r2[1] = NOUPDATE_OPTIONAL;
    r2[2] = NOUPDATE_OPTIONAL;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = NOUPDATE_MANDATORY;
    r3[1] = NOUPDATE_MANDATORY;
    r3[2] = NOUPDATE_MANDATORY;
    int* r4 = calloc(sizeof(int), 3);
    r4[0] = NOUPDATE_OPTIONAL;
    r4[1] = NOUPDATE_OPTIONAL;
    r4[2] = NOUPDATE_OPTIONAL;
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    requirements[2] = r3;
    requirements[3] = r4;
    
    int result = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}

int check_utilities_rm_rmdir_notempty_parentdir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.rm.rmdir.notempty.parentdir/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_targetdir = misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    
    char* path_rmdir_dir = misc_concat_ensure_dir_exists(path_targetdir, "dir/", 0, 0, output_file, error_file, __func__);
    char* path_file = misc_concat_ensure_file_exists_filled(path_rmdir_dir, "file", 7, 0, 0, output_file, error_file, __func__);
    
    char* command = "rmdir ../targetdir/dir/";
    
    char** watch_array = misc_char_array4(path_pwd, path_targetdir, path_rmdir_dir, path_file);
    int watch_num = 4;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, NULL, path_targetdir, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = NOUPDATE_MANDATORY;
    r2[1] = NOUPDATE_MANDATORY;
    r2[2] = NOUPDATE_MANDATORY;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = NOUPDATE_OPTIONAL;
    r3[1] = NOUPDATE_OPTIONAL;
    r3[2] = NOUPDATE_OPTIONAL;
    int* r4 = calloc(sizeof(int), 3);
    r4[0] = NOUPDATE_OPTIONAL;
    r4[1] = NOUPDATE_OPTIONAL;
    r4[2] = NOUPDATE_OPTIONAL;
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    requirements[2] = r3;
    requirements[3] = r4;
    
    int result = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}


#endif
