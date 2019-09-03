#ifndef CP_C
#define CP_C

#include "u_cp.h"

int check_utilities_cp_new(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.cp.new/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_srcdir = (char*) misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, output_file, error_file, __func__);
    char* path_file = misc_concat_ensure_file_exists_filled(path_srcdir, "file", 7, s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_targetdir = (char*) misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    char* path_copy = (char*) misc_concat(path_targetdir, "copy");
    
    char* command = "cp ../srcdir/file ../targetdir/copy";
    
    char** watch_array = misc_char_array5(path_file, path_pwd, path_srcdir, path_targetdir, path_copy);
    int watch_num = 5;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, path_srcdir, path_targetdir, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = UPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = NOUPDATE_OPTIONAL;
    r2[1] = NOUPDATE_OPTIONAL;
    r2[2] = NOUPDATE_OPTIONAL;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = NOUPDATE_OPTIONAL;
    r3[1] = NOUPDATE_OPTIONAL;
    r3[2] = NOUPDATE_OPTIONAL;
    int* r4 = calloc(sizeof(int), 3);
    r4[0] = UPDATE_OPTIONAL;
    r4[1] = NOUPDATE_OPTIONAL;
    r4[2] = UPDATE_OPTIONAL;
    int* r5 = calloc(sizeof(int), 3);
    r5[0] = UPDATE_MANDATORY;
    r5[1] = UPDATE_MANDATORY;
    r5[2] = UPDATE_MANDATORY;
    
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    requirements[2] = r3;
    requirements[3] = r4;
    requirements[4] = r5;
    
    int result = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}

int check_utilities_cp_new_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.cp.new.mac/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_srcdir = (char*) misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, output_file, error_file, __func__);
    misc_concat_ensure_file_exists_filled(path_srcdir, "file", 7, s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_targetdir = (char*) misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    char* path_copy = (char*) misc_concat(path_targetdir, "copy");
    
    
    char* command = "cp ../srcdir/file ../targetdir/copy";
    
    char** watch_array = misc_char_array1(path_copy);
    int watch_num = 1;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, path_srcdir, path_targetdir, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    
    struct stat* file_stat = pi->multi_stat_after[0];
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat->st_mtim), &(file_stat->st_atim)) != 0 || misc_timespec_eq(&(file_stat->st_atim), &(file_stat->st_ctim)) != 0){
        log_warning(output_file, error_file, "%s - MAC not equal", __func__);
        result = 2;
    }
    
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, pi->ts_before, pi->ts_after, file_stat);
    return result;
}

int check_utilities_cp_new_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.cp.new.dir/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_srcdir = (char*) misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, output_file, error_file, __func__);
    misc_concat_ensure_file_exists_filled(path_srcdir, "file", 7, s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_targetdir = (char*) misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    
    
    char* command = "cp ../srcdir/file ../targetdir/copy";
    
    char** watch_array = misc_char_array3(path_pwd, path_srcdir, path_targetdir);
    int watch_num = 3;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, path_srcdir, path_targetdir, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = NOUPDATE_MANDATORY;
    r2[1] = NOUPDATE_MANDATORY;
    r2[2] = NOUPDATE_MANDATORY;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = UPDATE_MANDATORY;
    r3[1] = NOUPDATE_OPTIONAL;
    r3[2] = UPDATE_MANDATORY;
    
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    requirements[2] = r3;
    
    int result = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}

int check_utilities_cp_new_dir_mc(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.cp.new.dir.mc/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_srcdir = (char*) misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, output_file, error_file, __func__);
    misc_concat_ensure_file_exists_filled(path_srcdir, "file", 7, s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_targetdir = (char*) misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    
    
    char* command = "cp ../srcdir/file ../targetdir/copy";
    
    char** watch_array = misc_char_array1(path_targetdir);
    int watch_num = 1;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, path_srcdir, path_targetdir, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    
    struct stat* file_stat = pi->multi_stat_after[0];
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat->st_mtim), &(file_stat->st_ctim)) != 0){
        log_warning(output_file, error_file, "%s - MC not equal", __func__);
        result = 2;
    }
    
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, pi->ts_before, pi->ts_after, file_stat);
    return result;
}

int check_utilities_cp_existing(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.cp.existing/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_srcdir = (char*) misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, output_file, error_file, __func__);
    char* path_file = misc_concat_ensure_file_exists_filled(path_srcdir, "file", 7, s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_targetdir = (char*) misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    char* path_copy = misc_concat_ensure_file_exists_filled(path_targetdir, "copy", 9, s_0s, ns_0ns, output_file, error_file, __func__);
    
    
    char* command = "cp ../srcdir/file ../targetdir/copy";
    
    char** watch_array = misc_char_array5(path_pwd, path_srcdir, path_targetdir, path_file, path_copy);
    int watch_num = 5;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, path_srcdir, path_targetdir, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = NOUPDATE_OPTIONAL;
    r2[1] = NOUPDATE_OPTIONAL;
    r2[2] = NOUPDATE_OPTIONAL;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = NOUPDATE_OPTIONAL;
    r3[1] = NOUPDATE_OPTIONAL;
    r3[2] = NOUPDATE_OPTIONAL;
    int* r4 = calloc(sizeof(int), 3);
    r4[0] = NOUPDATE_OPTIONAL;
    r4[1] = UPDATE_OPTIONAL;
    r4[2] = NOUPDATE_OPTIONAL;
    int* r5 = calloc(sizeof(int), 3);
    r5[0] = UPDATE_MANDATORY;
    r5[1] = NOUPDATE_OPTIONAL;
    r5[2] = UPDATE_MANDATORY;
    
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    requirements[2] = r3;
    requirements[3] = r4;
    requirements[4] = r5;
    
    int result = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}

int check_utilities_cp_existing_mc(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.cp.existing.mac/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_srcdir = (char*) misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, output_file, error_file, __func__);
    misc_concat_ensure_file_exists_filled(path_srcdir, "file", 7, s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_targetdir = (char*) misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    char* path_copy = misc_concat_ensure_file_exists_filled(path_targetdir, "copy", 9, s_0s, ns_0ns, output_file, error_file, __func__);
    
    
    char* command = "cp ../srcdir/file ../targetdir/copy";
    
    char** watch_array = misc_char_array1(path_copy);
    int watch_num = 1;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, path_srcdir, path_targetdir, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    
    struct stat* file_stat = pi->multi_stat_after[0];
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat->st_mtim), &(file_stat->st_ctim)) != 0){
        log_warning(output_file, error_file, "%s - MAC not equal", __func__);
        result = 2;
    }
    
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, pi->ts_before, pi->ts_after, file_stat);
    return result;
}

int check_utilities_cp_existing_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.cp.existing.dir/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_srcdir = (char*) misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, output_file, error_file, __func__);
    misc_concat_ensure_file_exists_filled(path_srcdir, "file", 7, s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_targetdir = (char*) misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    misc_concat_ensure_file_exists_filled(path_targetdir, "copy", 9, s_0s, ns_0ns, output_file, error_file, __func__);
    
    
    char* command = "cp ../srcdir/file ../targetdir/copy";
    
    char** watch_array = misc_char_array3(path_pwd, path_srcdir, path_targetdir);
    int watch_num = 3;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, path_srcdir, path_targetdir, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    
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
    r3[1] = NOUPDATE_OPTIONAL;
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
