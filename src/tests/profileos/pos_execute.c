#ifndef POS_EXECUTE_C
#define POS_EXECUTE_C

#include "pos_execute.h"

struct profile_info_struct* profileos_execute_system_interface(testenv_struct* env){
    char* path_pwd = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "_pwd/"), 0, 0, env->output_file, env->error_file, __func__);
    misc_nanosleep(ns_after_open); 
    char* path_id = (char*) "/usr/bin/id";
    
    char** watch_array = misc_char_array3(path_id, "/usr/bin", path_pwd);
    int watch_num = 3;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    chdir(path_pwd);
    
    pid_t child_pid = fork();
    if (child_pid == 0) {
        // Child code
        char *args[]={path_id, NULL}; 
        int ret = execvp(args[0],args);
        _exit(ret);
    }
    
    int wstatus;    
    if (waitpid(child_pid, &wstatus, 0) == -1) {
            log_error(env->output_file, env->error_file, "%s - waitpid failed with errno %d", __func__, errno);
    }
    else {
        if (WIFEXITED(wstatus)){
            if (WEXITSTATUS(wstatus) != 0){
                int exitstatus = WEXITSTATUS(wstatus);
                log_error(env->output_file, env->error_file, "%s - waitpid unexpected exit status: %d\n", __func__, exitstatus); 
            }
        }
        else {        
            log_error(env->output_file, env->error_file, "%s - childpid exited not normally", __func__);
        }
    }
    
    chdir("../../");
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_execute_system_utilities(testenv_struct* env){
    char* path_pwd = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "_pwd/"), 0, 0, env->output_file, env->error_file, __func__);
    char* command = "/usr/bin/id";
    
    char** watch_array = misc_char_array3("/usr/bin/id", "/usr/bin", path_pwd);
    int watch_num = 3;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_pwd, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    return pi;
}


struct profile_info_struct* profileos_execute_local_interface(testenv_struct* env){
    char* path_pwd = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "_pwd/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_bindir = misc_concat_ensure_dir_exists(path_pwd, "bindir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_id = (char*) "/usr/bin/id";
    char* path_id_local = misc_concat(path_bindir, "id_local");
    misc_cp_rwx_no_overwrite(path_id, path_id_local);
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array3(path_id_local, path_bindir, path_pwd);
    int watch_num = 3;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    chdir(path_pwd);
    
    pid_t child_pid = fork();
    if (child_pid == 0) {
        // Child code
        char *args[]={"bindir/id_local", NULL}; 
        int ret = execvp(args[0],args);
        _exit(ret);
    }
    
    int wstatus;    
    if (waitpid(child_pid, &wstatus, 0) == -1) {
            log_error(env->output_file, env->error_file, "%s - waitpid failed with errno %d", __func__, errno);
    }
    else {
        if (WIFEXITED(wstatus)){
            if (WEXITSTATUS(wstatus) != 0){
                int exitstatus = WEXITSTATUS(wstatus);
                log_error(env->output_file, env->error_file, "%s - waitpid unexpected exit status: %d\n", __func__, exitstatus); 
            }
        }
        else {        
            log_error(env->output_file, env->error_file, "%s - childpid exited not normally", __func__);
        }
    }
    
    chdir("../../");
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_execute_local_interface_symlink(testenv_struct* env){
    char* path_pwd = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "_pwd/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_bindir = misc_concat_ensure_dir_exists(path_pwd, "bindir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_linkdir = misc_concat_ensure_dir_exists(path_pwd, "linkdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_id = (char*) "/usr/bin/id";
    char* path_id_local = misc_concat(path_bindir, "id_local");
    char* path_id_link = misc_concat(path_linkdir, "id_local_link");
    misc_cp_rwx_no_overwrite(path_id, path_id_local);
    misc_nanosleep(ns_after_open);
    
    int r = symlink("../bindir/id_local", path_id_link);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array5(path_id_local, path_id_link, path_bindir, path_linkdir, path_pwd);
    int watch_num = 5;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    chdir(path_pwd);
    
    pid_t child_pid = fork();
    if (child_pid == 0) {
        // Child code
        char *args[]={"linkdir/id_local_link", NULL}; 
        int ret = execvp(args[0],args);
        _exit(ret);
    }
    
    int wstatus;    
    if (waitpid(child_pid, &wstatus, 0) == -1) {
            log_error(env->output_file, env->error_file, "%s - waitpid failed with errno %d", __func__, errno);
    }
    else {
        if (WIFEXITED(wstatus)){
            if (WEXITSTATUS(wstatus) != 0){
                int exitstatus = WEXITSTATUS(wstatus);
                log_error(env->output_file, env->error_file, "%s - waitpid unexpected exit status: %d\n", __func__, exitstatus); 
            }
        }
        else {        
            log_error(env->output_file, env->error_file, "%s - childpid exited not normally", __func__);
        }
    }
    
    chdir("../../");

    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_execute_local_interface_intosymlinkdir(testenv_struct* env){
    char* path_pwd = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "_pwd/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_bindir = misc_concat_ensure_dir_exists(path_pwd, "bindir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_bindir_link = misc_concat(path_pwd, "bindir_link");
    char* path_id = (char*) "/usr/bin/id";
    char* path_id_local = misc_concat(path_bindir, "id_local");
    misc_cp_rwx_no_overwrite(path_id, path_id_local);
    misc_nanosleep(ns_after_open);
    
    int r = symlink("bindir/", path_bindir_link);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    char** watch_array = misc_char_array4(path_id_local, path_bindir, path_bindir_link, path_pwd);
    int watch_num = 4;
    profile_init_struct* pis = profile_init(watch_num, watch_array);
    
    chdir(path_pwd);
    
    pid_t child_pid = fork();
    if (child_pid == 0) {
        // Child code
        char *args[]={"bindir_link/id_local", NULL}; 
        int ret = execvp(args[0],args);
        _exit(ret);
    }
    
    int wstatus;    
    if (waitpid(child_pid, &wstatus, 0) == -1) {
            log_error(env->output_file, env->error_file, "%s - waitpid failed with errno %d", __func__, errno);
    }
    else {
        if (WIFEXITED(wstatus)){
            if (WEXITSTATUS(wstatus) != 0){
                int exitstatus = WEXITSTATUS(wstatus);
                log_error(env->output_file, env->error_file, "%s - waitpid unexpected exit status: %d\n", __func__, exitstatus); 
            }
        }
        else {        
            log_error(env->output_file, env->error_file, "%s - childpid exited not normally", __func__);
        }
    }
    
    chdir("../../");
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_execute_local_utilities(testenv_struct* env){
    char* path_pwd = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "_pwd/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_bindir = misc_concat_ensure_dir_exists(path_pwd, "bindir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_id = (char*) "/usr/bin/id";
    char* path_id_local = misc_concat(path_bindir, "id_local");
    misc_cp_rwx_no_overwrite(path_id, path_id_local);
    misc_nanosleep(ns_after_open); 
    
    char* command = "./bindir/id_local";
    
    char** watch_array = misc_char_array3(path_id_local, path_bindir, path_pwd);
    int watch_num = 3;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_pwd, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_execute_local_utilities_symlink(testenv_struct* env){
    char* path_pwd = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "_pwd/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_bindir = misc_concat_ensure_dir_exists(path_pwd, "bindir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_linkdir = misc_concat_ensure_dir_exists(path_pwd, "linkdir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_id = (char*) "/usr/bin/id";
    char* path_id_local = misc_concat(path_bindir, "id_local");
    char* path_id_link = misc_concat(path_linkdir, "id_local_link");
    misc_cp_rwx_no_overwrite(path_id, path_id_local);
    misc_nanosleep(ns_after_open); 
    
    int r = symlink("../bindir/id_local", path_id_link);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    char* command = "./linkdir/id_local_link";
    
    char** watch_array = misc_char_array5(path_id_local, path_id_link, path_bindir, path_linkdir, path_pwd);
    int watch_num = 5;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_pwd, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_execute_local_utilities_intosymlinkdir(testenv_struct* env){
    char* path_pwd = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "_pwd/"), 0, 0, env->output_file, env->error_file, __func__);
    char* path_bindir = misc_concat_ensure_dir_exists(path_pwd, "bindir/", 0, 0, env->output_file, env->error_file, __func__);
    char* path_bindir_link = misc_concat(path_pwd, "bindir_link");
    char* path_id = (char*) "/usr/bin/id";
    char* path_id_local = misc_concat(path_bindir, "id_local");
    misc_cp_rwx_no_overwrite(path_id, path_id_local);
    misc_nanosleep(ns_after_open); 
    
    int r = symlink("bindir/", path_bindir_link);
    if (r != 0){
        log_warning(env->output_file, env->error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    misc_nanosleep(ns_after_open);
    
    char* command = "./bindir_link/id_local";
    
    char** watch_array = misc_char_array4(path_id_local, path_bindir, path_bindir_link, path_pwd);
    int watch_num = 4;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_pwd, NULL, NULL, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    return pi;
}

#endif
