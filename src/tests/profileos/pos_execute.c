#ifndef POS_EXECUTE_C
#define POS_EXECUTE_C

#include "pos_execute.h"

struct profile_info_struct* profileos_execute_system_interface(testenv_struct* env){
    char* path_pwd = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "_pwd/"), 0, 0, env->output_file, env->error_file, __func__);
    misc_nanosleep(ns_after_open); 
    char* path_id = (char*) "/usr/bin/id";
    
    char** watch_array = misc_char_array3(path_id, "/bin", path_pwd);
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
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

struct profile_info_struct* profileos_execute_system_utilities(testenv_struct* env){
    char* path_pwd = misc_concat_ensure_dir_exists(env->dir_path, misc_concat(__func__, "_pwd/"), 0, 0, env->output_file, env->error_file, __func__);
    char* command = "/usr/bin/id";
    
    char** watch_array = misc_char_array3("/usr/bin/id", "/bin", path_pwd);
    int watch_num = 3;
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_pwd, NULL, NULL, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
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
    
    struct profile_info_struct* pi = profile_analyze(pis, watch_num, watch_array, CMD_DELAY_S, CMD_DELAY_NS);
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
    
    struct profile_info_struct* pi = profile_command(env->output_file, env->error_file, path_pwd, NULL, NULL, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    return pi;
}

#endif
