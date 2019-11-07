#ifndef POS_DIRLISTING_C
#define POS_DIRLISTING_C

#include "pos_dirlisting.h"

struct profile_info_struct* profileos_dirlisting_interface_notempty(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    DIR *dp = opendir(path_dir);
    if (dp == NULL) {
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error opening directory");
        return 1;
    }
    struct dirent *de;   
    int first = 0;

    while (de != NULL || first == 0){
        de = readdir(dp);
        first = 1;
    }
    closedir(dp);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_dirlisting_interface_symlink(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dir_dir = misc_concat_ensure_dir_exists(path_dir, "dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_dir_link = misc_concat(path_dir, "symlink");
    misc_nanosleep(ns_after_open);
    
    int r = symlink("dir/", path_dir_link);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array3(path_dir_dir, path_dir_link, path);
    int watch_num = 3;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    DIR *dp = opendir(path_dir_link);
    if (dp == NULL) {
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error opening directory");
        return 1;
    }
    struct dirent *de;   
    int first = 0;

    while (de != NULL || first == 0){
        de = readdir(dp);
        first = 1;
    }
    closedir(dp);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_dirlisting_interface_empty(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    misc_nanosleep(ns_after_open); 
    
    char** watch_array = misc_char_array1(path_dir);
    int watch_num = 1;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    DIR *dp = opendir(path_dir);
    if (dp == NULL) {
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error opening directory");
        return 1;
    }
    struct dirent *de;   
    int first = 0;

    while (de != NULL || first == 0){
        de = readdir(dp);
        first = 1;
    }
    closedir(dp);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_dirlisting_utilities_notempty(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char* command = "ls";
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}
struct profile_info_struct* profileos_dirlisting_utilities_empty(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    misc_nanosleep(ns_after_open); 
    
    char* command = "ls";
    
    char** watch_array = misc_char_array1(path_dir);
    int watch_num = 1;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}
struct profile_info_struct* profileos_dirlisting_utilities_symlink(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_dir_dir = misc_concat_ensure_dir_exists(path_dir, "dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_dir_link = misc_concat(path_dir, "symlink");
    misc_nanosleep(ns_after_open);
    
    int r = symlink("dir/", path_dir_link);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array3(path_dir_dir, path_dir_link, path);
    int watch_num = 3;
    
    char* command = "ls";
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir_link, NULL, NULL, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

#endif
