#ifndef INTERFACES_C
#define INTERFACES_C

#include "interfaces.h"

int check_interfaces_exec_execvp(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_ls = (char*) "/bin/ls";
    
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    pid_t child_pid = fork();
    if (child_pid == 0) {
        // Child code
        char *args[]={path_ls, NULL}; 
        int ret = execvp(args[0],args);
        _exit(ret);
    }
    
    int wstatus;    
    if (waitpid(child_pid, &wstatus, 0) == -1) {
            log_error(output_file, error_file, "%s - waitpid failed with errno %d", __func__, errno);
    }
    else {
        if (WIFEXITED(wstatus)){
            if (WEXITSTATUS(wstatus) != 0){
                int exitstatus = WEXITSTATUS(wstatus);
                log_error(output_file, error_file, "%s - waitpid unexpected exit status: %d\n", __func__, exitstatus); 
            }
        }
        else {        
            log_error(output_file, error_file, "%s - childpid exited not normally", __func__);
        }
    }
    
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY); // Delay
    struct stat_macb* file_stat = get_path_timestamps(path_ls);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, UPDATE_MANDATORY, NOUPDATE_OPTIONAL, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}


int check_interfaces_exec_execvp_local(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_ls = (char*) "/bin/ls";
    char* path_ls_local = misc_concat(dir_path, "ls_local");
    misc_cp_rwx_no_overwrite(path_ls, path_ls_local);
    
    misc_nanosleep(ns_DELAY); // Delay  
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    pid_t child_pid = fork();
    if (child_pid == 0) {
        // Child code
        char *args[]={path_ls_local, NULL}; 
        int ret = execvp(args[0],args);
        _exit(ret);
    }
    
    int wstatus;    
    if (waitpid(child_pid, &wstatus, 0) == -1) {
            log_error(output_file, error_file, "%s - waitpid failed with errno %d", __func__, errno);
    }
    else {
        if (WIFEXITED(wstatus)){
            if (WEXITSTATUS(wstatus) != 0){
                int exitstatus = WEXITSTATUS(wstatus);
                log_error(output_file, error_file, "%s - waitpid unexpected exit status: %d\n", __func__, exitstatus); 
            }
        }
        else {        
            log_error(output_file, error_file, "%s - childpid exited not normally", __func__);
        }
    }
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    struct stat_macb* file_stat = get_path_timestamps(path_ls_local);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, UPDATE_MANDATORY, NOUPDATE_OPTIONAL, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path_ls_local);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}


int check_interfaces_attr_chmod(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists(dir_path, __func__, 0, 0, output_file, error_file, __func__);
    
    misc_nanosleep(ns_DELAY); // Delay
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    char mode[] = "0777";
    int i;
    i = strtol(mode, 0, 8);
    chmod(path,i) ;
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY); // Delay
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_interfaces_attr_chown_grp(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists(dir_path, __func__, 0, 0, output_file, error_file, __func__);
    
    misc_nanosleep(ns_DELAY); // Delay
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    uid_t uid = -1;
    gid_t gid = getgid();
    chown(path, uid, gid);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY); // Delay
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_interfaces_attr_chown_usr(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists(dir_path, __func__, 0, 0, output_file, error_file, __func__);
    
    misc_nanosleep(ns_DELAY); // Delay
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    uid_t uid = getuid();
    gid_t gid = -1;
    chown(path, uid, gid);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY); // Delay
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_interfaces_attr_chown_grp_usr(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists(dir_path, __func__, 0, 0, output_file, error_file, __func__);
    
    misc_nanosleep(ns_DELAY); // Delay
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    uid_t uid = getuid();
    gid_t gid = getgid();
    chown(path, uid, gid);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY); // Delay
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    int result = result_MAC_updated(NOUPDATE_OPTIONAL, NOUPDATE_OPTIONAL, UPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

int check_interfaces_attr_chown_nochange(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path = misc_concat_ensure_file_exists(dir_path, __func__, 0, 0, output_file, error_file, __func__);
    
    misc_nanosleep(ns_DELAY); // Delay
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    uid_t uid = -1;
    gid_t gid = -1;
    chown(path, uid, gid);
    
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    misc_nanosleep(ns_DELAY); // Delay
    struct stat_macb* file_stat = get_path_timestamps(path);
    
    int result = result_MAC_updated(NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, NOUPDATE_MANDATORY, output_file, error_file, __func__, ts_before, ts_after, file_stat);
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, ts_before, ts_after, file_stat);
    
    free(path);
    free(ts_before);
    free(ts_after);
    free(file_stat);
    
    return result;
}

#endif
