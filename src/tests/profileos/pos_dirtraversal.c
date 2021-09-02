#ifndef POS_DIRTRAVERSAL_C
#define POS_DIRTRAVERSAL_C

#include "pos_dirtraversal.h"

struct profile_info_struct* profileos_dirtraversal_interface(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_dir, "dir/", 0, 0, env->output_file, env->error_file, __func__);
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array1(path);
    int watch_num = 1;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    char* saved_pwd[256];
    char* retc = getcwd(saved_pwd, 256);
    if (retc == NULL){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error getting saved_pwd");
    }
    int ret = chdir(path);
    if (ret != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error setting pwd with chdir");
    }
    misc_nanosleep(ns_after_open); 
    ret = chdir(saved_pwd);
    if (ret != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error setting pwd with chdir");
    }
    misc_nanosleep(ns_after_open); 
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_dirtraversal_utilities(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_dir, "dir/", 0, 0, env->output_file, env->error_file, __func__);
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array1(path);
    int watch_num = 1;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    char* cmd1 = misc_concat("cd ", path);
    char* command = misc_concat(cmd1, " ; sleep 1 ; cd -");
    
    system(cmd1);
    misc_nanosleep(ns_after_open); 
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_dirtraversal_utilities_profileos(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_dir, "dir/", 0, 0, env->output_file, env->error_file, __func__);
    misc_nanosleep(ns_after_open);
    
    char* command = "";
    
    char** watch_array = misc_char_array1(path);
    int watch_num = 1;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_dirtraversal_interface_symlink(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_dir, "dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_link = misc_concat(path_dir, "symlink");
    
    int r = symlink("dir/", path_link);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array2(path, path_link);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    char* saved_pwd[256];
    char* retc = getcwd(saved_pwd, 256);
    if (retc == NULL){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error getting saved_pwd");
    }
    int ret = chdir(path_link);
    if (ret != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error setting pwd with chdir");
    }
    misc_nanosleep(ns_after_open); 
    ret = chdir(saved_pwd);
    if (ret != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error setting pwd with chdir");
    }
    misc_nanosleep(ns_after_open); 
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_dirtraversal_utilities_symlink(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_dir, "dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_link = misc_concat(path_dir, "symlink");
    
    int r = symlink("dir/", path_link);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array2(path, path_link);
    int watch_num = 2;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    char* cmd1 = misc_concat("cd ", path_link);
    char* command = misc_concat(cmd1, " ; sleep 1 ; cd -");
    
    system(cmd1);
    misc_nanosleep(ns_after_open); 
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_dirtraversal_utilities_profileos_symlink(testenv_struct* env){
    char* path_dir = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path = misc_concat_ensure_dir_exists(path_dir, "dir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_link = misc_concat(path_dir, "symlink");
    
    int r = symlink("dir/", path_link);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    char* command = "";
    
    char** watch_array = misc_char_array2(path, path_link);
    int watch_num = 2;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_link, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    return pi;
}


#endif
