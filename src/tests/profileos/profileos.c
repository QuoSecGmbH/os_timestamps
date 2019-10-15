#ifndef PROFILEOS_C
#define PROFILEOS_C

#include "profileos.h"

struct profile_info_struct* profileos_filerename_interface_noreplace(testenv_struct* env){
    char* path_dir = misc_concat(env->dir_path, (char*) "profileos.filerename.interface.noreplace/");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "orig", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dir, "renamed");
    
    char** watch_array = misc_char_array3(path, path_new, path_dir);
    int watch_num = 3;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    rename(path, path_new);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filerename_interface_replace(testenv_struct* env){
    char* path_dir = misc_concat(env->dir_path, (char*) "profileos.filerename.interface.replace/");
    mkdir(path_dir, 0700);
    misc_nanosleep(ns_after_open);
    
    char* path = misc_concat_ensure_file_exists_filled(path_dir, "orig", 10, s_0s, ns_after_open, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat_ensure_file_exists_filled(path_dir, "renamed", 15, s_0s, ns_after_open, env->output_file, env->error_file, __func__);;
    
    char** watch_array = misc_char_array3(path, path_new, path_dir);
    int watch_num = 3;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    rename(path, path_new);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    
    return pi;
}

#endif
