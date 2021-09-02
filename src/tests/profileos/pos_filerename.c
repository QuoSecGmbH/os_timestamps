#ifndef POS_FILERENAME_C
#define POS_FILERENAME_C

#include "pos_filerename.h"

struct profile_info_struct* profileos_filerename_interface_new(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "orig", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dir, "renamed");
    
    char** watch_array = misc_char_array3(path, path_new, path_dir);
    int watch_num = 3;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    rename(path, path_new);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filerename_interface_existing(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "orig", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat_ensure_file_exists_filled(path_dir, "renamed", 15, s_0s, ns_after_open, env->output_file, env->error_file, __func__);;
    
    char** watch_array = misc_char_array3(path, path_new, path_dir);
    int watch_num = 3;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    rename(path, path_new);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filerename_interface_dir_new(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_dir, "orig/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    misc_concat_ensure_file_exists_filled(path, "dirfile", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dir, "renamed");
    
    char** watch_array = misc_char_array3(path, path_new, path_dir);
    int watch_num = 3;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    rename(path, path_new);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filerename_interface_dir_existing(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_dir, "orig/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    misc_concat_ensure_file_exists_filled(path, "dirfile", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat_ensure_dir_exists(path_dir, "renamed/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);;
    
    char** watch_array = misc_char_array3(path, path_new, path_dir);
    int watch_num = 3;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
//     unlink(path_new); // (equivalent with or without as per POSIX description)
    rename(path, path_new);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filerename_utilities_new(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "orig", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dir, "renamed");
    
    char* command = "mv orig renamed";
    
    char** watch_array = misc_char_array3(path, path_new, path_dir);
    int watch_num = 3;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filerename_utilities_existing(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "orig", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat_ensure_file_exists_filled(path_dir, "renamed", 15, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char* command = "mv orig renamed";
    
    char** watch_array = misc_char_array3(path, path_new, path_dir);
    int watch_num = 3;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filerename_utilities_dir_new(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_dir, "orig/", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    misc_concat_ensure_file_exists_filled(path, "dirfile", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dir, "renamed");
    
    char* command = "mv orig renamed";
    
    char** watch_array = misc_char_array3(path, path_new, path_dir);
    int watch_num = 3;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    return pi;
}

// struct profile_info_struct* profileos_filerename_utilities_dir_existing(testenv_struct* env){
//     char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
//     char* path = misc_concat_ensure_dir_exists(path_dir, "orig", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
//     misc_concat_ensure_file_exists_filled(path, "dirfile", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
//     char* path_new = misc_concat_ensure_dir_exists(path_dir, "renamed", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
//     
//     char* command = "mv orig renamed";
//     
//     char** watch_array = misc_char_array3(path, path_new, path_dir);
//     int watch_num = 3;
//     
//     struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
//     
//     return pi;
// }

#endif
