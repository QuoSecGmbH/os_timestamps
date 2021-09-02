#ifndef U_MV_C
#define U_MV_C

#include "u_mv.h"

int check_utilities_mv_new(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.mv.new/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_srcdir = (char*) misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, ns_after_open, output_file, error_file, __func__);
    char* path_src = misc_concat_ensure_file_exists_filled(path_srcdir, "file", 7, s_0s, ns_after_open, output_file, error_file, __func__);
    char* path_targetdir = (char*) misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    char* path_copy = (char*) misc_concat(path_targetdir, "moved");
    
    char* command = "mv ../srcdir/file ../targetdir/moved";
    
    char** watch_array = misc_char_array5(path_src, path_pwd, path_srcdir, path_targetdir, path_copy);
    int watch_num = 5;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, path_srcdir, path_targetdir, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = NOUPDATE_OPTIONAL;
    r2[1] = NOUPDATE_OPTIONAL;
    r2[2] = NOUPDATE_OPTIONAL;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = UPDATE_MANDATORY;
    r3[1] = NOUPDATE_OPTIONAL;
    r3[2] = UPDATE_MANDATORY;
    int* r4 = calloc(sizeof(int), 3);
    r4[0] = UPDATE_MANDATORY;
    r4[1] = NOUPDATE_OPTIONAL;
    r4[2] = UPDATE_MANDATORY;
    int* r5 = calloc(sizeof(int), 3);
    r5[0] = NOUPDATE_MANDATORY;
    r5[1] = NOUPDATE_MANDATORY;
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

int check_utilities_mv_new_eq(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.mv.new.eq/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_srcdir = (char*) misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, output_file, error_file, __func__);
    misc_concat_ensure_file_exists_filled(path_srcdir, "file", 7, s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_targetdir = (char*) misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    char* path_copy = (char*) misc_concat(path_targetdir, "moved");
    
    char* command = "mv ../srcdir/file ../targetdir/moved";
    
    char** watch_array = misc_char_array3(path_srcdir, path_targetdir, path_copy);
    int watch_num = 3;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, path_srcdir, path_targetdir, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    struct stat_macb* srcdir_stat = pi->multi_stat_after[0];
    struct stat_macb* targetdir_stat = pi->multi_stat_after[1];
    struct stat_macb* copy_stat = pi->multi_stat_after[2];

    int result = 0;
    if (misc_timespec_eq(&(srcdir_stat->st_mtim), &(srcdir_stat->st_ctim)) != 0 || 
        misc_timespec_eq(&(srcdir_stat->st_ctim), &(targetdir_stat->st_mtim)) != 0 ||
        misc_timespec_eq(&(targetdir_stat->st_mtim), &(targetdir_stat->st_ctim)) != 0 ||
        misc_timespec_eq(&(targetdir_stat->st_ctim), &(copy_stat->st_ctim)) != 0) {
        log_warning(output_file, error_file, "%s - MAC not equal", __func__);
        result = 2;
    }
    
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}

int check_utilities_mv_existing(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.mv.existing/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_srcdir = (char*) misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, ns_after_open, output_file, error_file, __func__);
    char* path_src = misc_concat_ensure_file_exists_filled(path_srcdir, "file", 7, s_0s, ns_after_open, output_file, error_file, __func__);
    char* path_targetdir = (char*) misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    char* path_copy = (char*) misc_concat_ensure_file_exists_filled(path_targetdir, "moved", 3, s_0s, ns_0ns, output_file, error_file, __func__);
    
    char* command = "mv ../srcdir/file ../targetdir/moved";
    
    char** watch_array = misc_char_array5(path_src, path_pwd, path_srcdir, path_targetdir, path_copy);
    int watch_num = 5;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, path_srcdir, path_targetdir, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = NOUPDATE_OPTIONAL;
    r2[1] = NOUPDATE_OPTIONAL;
    r2[2] = NOUPDATE_OPTIONAL;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = UPDATE_MANDATORY;
    r3[1] = NOUPDATE_OPTIONAL;
    r3[2] = UPDATE_MANDATORY;
    int* r4 = calloc(sizeof(int), 3);
    r4[0] = UPDATE_MANDATORY;
    r4[1] = NOUPDATE_OPTIONAL;
    r4[2] = UPDATE_MANDATORY;
    int* r5 = calloc(sizeof(int), 3);
    r5[0] = NOUPDATE_MANDATORY;
    r5[1] = NOUPDATE_MANDATORY;
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

int check_utilities_mv_existing_eq(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.mv.existing.eq/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_srcdir = (char*) misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, output_file, error_file, __func__);
    misc_concat_ensure_file_exists_filled(path_srcdir, "file", 7, s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_targetdir = (char*) misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    char* path_copy = (char*) misc_concat_ensure_file_exists_filled(path_targetdir, "moved", 3, s_0s, ns_0ns, output_file, error_file, __func__);
    
    char* command = "mv ../srcdir/file ../targetdir/moved";
    
    char** watch_array = misc_char_array3(path_srcdir, path_targetdir, path_copy);
    int watch_num = 3;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, path_srcdir, path_targetdir, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    struct stat_macb* srcdir_stat = pi->multi_stat_after[0];
    struct stat_macb* targetdir_stat = pi->multi_stat_after[1];
    struct stat_macb* copy_stat = pi->multi_stat_after[2];

    int result = 0;
    if (misc_timespec_eq(&(srcdir_stat->st_mtim), &(srcdir_stat->st_ctim)) != 0 || 
        misc_timespec_eq(&(srcdir_stat->st_ctim), &(targetdir_stat->st_mtim)) != 0 ||
        misc_timespec_eq(&(targetdir_stat->st_mtim), &(targetdir_stat->st_ctim)) != 0 ||
        misc_timespec_eq(&(targetdir_stat->st_ctim), &(copy_stat->st_ctim)) != 0) {
        log_warning(output_file, error_file, "%s - MAC not equal", __func__);
        result = 2;
    }
    
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}

#endif
