#ifndef POS_FILEDELETE_C
#define POS_FILEDELETE_C

#include "pos_filedelete.h"

struct profile_info_struct* profileos_filedelete_last_interface_empty(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists(path_dir, "file", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    unlink(path);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_filedelete_last_interface_notempty(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    unlink(path);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_filedelete_last_utilities_empty(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists(path_dir, "file", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char* command = "rm file";
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_filedelete_last_utilities_notempty(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char* command = "rm file";
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_filedelete_notlast_interface_empty(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists(path_dir, "file", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_link = misc_concat(path_dir, (char*) "link");
    int r = link(path, path_link);
    misc_nanosleep(ns_after_open); 
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    unlink(path_link);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_filedelete_notlast_interface_notempty(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_link = misc_concat(path_dir, (char*) "link");
    int r = link(path, path_link);
    misc_nanosleep(ns_after_open); 
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    unlink(path_link);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_filedelete_notlast_utilities_empty(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists(path_dir, "file", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_link = misc_concat(path_dir, (char*) "link");
    int r = link(path, path_link);
    misc_nanosleep(ns_after_open); 
    
    char* command = "rm link";
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_filedelete_notlast_utilities_notempty(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "file", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_link = misc_concat(path_dir, (char*) "link");
    int r = link(path, path_link);
    misc_nanosleep(ns_after_open); 
    
    char* command = "rm link";
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_dirdelete_interface(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_dir, "dir", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    rmdir(path);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_dirdelete_utilities_rm(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_dir, "dir", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char* command = "rm -r dir";
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_dirdelete_utilities_rmdir(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_dir, "dir", s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    
    char* command = "rmdir dir";
    
    char** watch_array = misc_char_array2(path_dir, path);
    int watch_num = 2;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

#endif
