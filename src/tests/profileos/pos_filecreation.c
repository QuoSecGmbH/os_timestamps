#ifndef POS_FILECREATION_C
#define POS_FILECREATION_C

#include "pos_filecreation.h"

struct profile_info_struct* profileos_filecreation_interface(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dir, "newfile");
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array2(path_dir, path_new);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    FILE* fd = fopen(path_new, "wb");
    fclose(fd);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filecreation_interface_dir(testenv_struct* env){   
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dir, "newdir/");
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array2(path_dir, path_new);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    mkdir(path_new, 0700);
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filecreation_utilities(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dir, "newfile");
    misc_nanosleep(ns_after_open);
    
    char* command = "touch newfile";
    
    char** watch_array = misc_char_array2(path_dir, path_new);
    int watch_num = 2;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    
    return pi;
}

struct profile_info_struct* profileos_filecreation_utilities_dir(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_new = misc_concat(path_dir, "newdir/");
    misc_nanosleep(ns_after_open);
    
    char* command = "mkdir newdir";
    
    char** watch_array = misc_char_array2(path_dir, path_new);
    int watch_num = 2;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_dir, NULL, NULL, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    
    return pi;
}

#endif
