#ifndef PROFILE_C
#define PROFILE_C

#include "profile.h"

int get_profile_value(struct timespec* ts_before, struct timespec* ts_after, struct timespec* ts_after_delay, struct timespec* ts_file_before, struct timespec* ts_file_command, struct timespec* W0_before, struct timespec* ts_file_delay){
    int value = 0;
    if (W0_before != NULL && ts_file_command != NULL){
        if (ts_file_before == NULL || misc_timespec_eq(ts_file_before, ts_file_command) == 1){
            if (misc_timespec_eq(ts_file_command, W0_before) == 0){
                // Case: file timestamp changed between before and after command
                //         AND file timestamp after command == before timestamp of first file
                    value |= PROFILE_SAMEAS_W0_BEFORE;
            }
        }
    }

    if (misc_timespec_leq_leq(ts_before, ts_file_command, ts_after) == 0){
            value |= PROFILE_UPDATE_COMMAND;
    }
    if (misc_timespec_l_leq(ts_after, ts_file_delay, ts_after_delay) == 0){
        if(PROFILE_TREAT_DELAY_AS_COMMAND){
            value |= PROFILE_UPDATE_COMMAND;
        }
        else {
            value |= PROFILE_UPDATE_DELAY;
        }
    }
    
    if (ts_file_before == NULL || misc_timespec_eq(ts_file_before, ts_file_command) == 1){
        if (ts_file_command != NULL && misc_timespec_l(ts_file_command, ts_before) == 0){
                value |= PROFILE_EARLIER;
        }
        
        if (ts_file_command != NULL && misc_timespec_l(ts_after, ts_file_command) == 0){
            if (PROFILE_TREAT_DELAY_AS_COMMAND){
                if (misc_timespec_l(ts_after_delay, ts_file_command) == 0){ 
                    value |= PROFILE_LATER;
                }
            }
            else{
                value |= PROFILE_LATER;
            }
        }
    }
    
    if (ts_file_before != NULL && ts_file_command != NULL && misc_timespec_eq(ts_file_before, ts_file_command) == 0){
            value |= PROFILE_EQ_COMMAND;
    }
    return value;
}

int** compute_profile(struct timespec* ts_before, struct timespec* ts_after, struct timespec* ts_after_delay, int watch_num, struct stat** multi_stat_before, struct stat** multi_stat_after, struct stat** multi_stat_after_delay){
    int** profile = (int**) calloc(sizeof(int*), watch_num);
    
    struct timespec* stat_w0_before_M = NULL;
    struct timespec* stat_w0_before_A = NULL;
    struct timespec* stat_w0_before_C = NULL;
    struct timespec* stat_w0_before_B = NULL;
    if (watch_num >= 1){
        struct stat_macb* file_stat_w0_before = multi_stat_before[0];
        
        if (file_stat_w0_before != NULL){
            stat_w0_before_M = &(file_stat_w0_before->st_mtim);
            stat_w0_before_A = &(file_stat_w0_before->st_atim);
            stat_w0_before_C = &(file_stat_w0_before->st_ctim);
            stat_w0_before_B = &(file_stat_w0_before->st_btim);
        }
    }
    
    int i;
    for (i=0; i<watch_num; i++){
        profile[i] = (int*) calloc(sizeof(int), 4);
        
        struct stat_macb* file_stat_before = multi_stat_before[i];
        struct stat_macb* file_stat_command = multi_stat_after[i];
        struct stat_macb* file_stat_delay = multi_stat_after_delay[i];
        
        if (file_stat_command == NULL || file_stat_delay == NULL){
            profile[i][0] = -1;
            profile[i][1] = -1;
            profile[i][2] = -1;
            profile[i][3] = -1;
            continue;
        }
        
        struct timespec* file_stat_before_timespec_M = NULL;
        struct timespec* file_stat_before_timespec_A = NULL;
        struct timespec* file_stat_before_timespec_C = NULL;
        struct timespec* file_stat_before_timespec_B = NULL;
        if (file_stat_before != NULL){
            file_stat_before_timespec_M = &(file_stat_before->st_mtim);
            file_stat_before_timespec_A = &(file_stat_before->st_atim);
            file_stat_before_timespec_C = &(file_stat_before->st_ctim);
            file_stat_before_timespec_B = &(file_stat_before->st_btim);
        }
        
        struct timespec* file_stat_command_timespec_M = NULL;
        struct timespec* file_stat_command_timespec_A = NULL;
        struct timespec* file_stat_command_timespec_C = NULL;
        struct timespec* file_stat_command_timespec_B = NULL;
        if (file_stat_command != NULL){
            file_stat_command_timespec_M = &(file_stat_command->st_mtim);
            file_stat_command_timespec_A = &(file_stat_command->st_atim);
            file_stat_command_timespec_C = &(file_stat_command->st_ctim);
            file_stat_command_timespec_B = &(file_stat_command->st_btim);
        }
        
        struct timespec* file_stat_delay_timespec_M = NULL;
        struct timespec* file_stat_delay_timespec_A = NULL;
        struct timespec* file_stat_delay_timespec_C = NULL;
        struct timespec* file_stat_delay_timespec_B = NULL;
        if (file_stat_delay != NULL){
            file_stat_delay_timespec_M = &(file_stat_delay->st_mtim);
            file_stat_delay_timespec_A = &(file_stat_delay->st_atim);
            file_stat_delay_timespec_C = &(file_stat_delay->st_ctim);
            file_stat_delay_timespec_B = &(file_stat_delay->st_btim);
        }
        
        // M, A, C: PROFILE_UPDATE_COMMAND, PROFILE_UPDATE_DELAY or both
        int value_M = get_profile_value(ts_before, ts_after, ts_after_delay, file_stat_before_timespec_M, file_stat_command_timespec_M, stat_w0_before_M, file_stat_delay_timespec_M);
        int value_A = get_profile_value(ts_before, ts_after, ts_after_delay, file_stat_before_timespec_A, file_stat_command_timespec_A, stat_w0_before_A, file_stat_delay_timespec_A);
        int value_C = get_profile_value(ts_before, ts_after, ts_after_delay, file_stat_before_timespec_C, file_stat_command_timespec_C, stat_w0_before_C, file_stat_delay_timespec_C);
        int value_B = get_profile_value(ts_before, ts_after, ts_after_delay, file_stat_before_timespec_B, file_stat_command_timespec_B, stat_w0_before_B, file_stat_delay_timespec_B);
        
        profile[i][0] = value_M;
        profile[i][1] = value_A;
        profile[i][2] = value_C;
        profile[i][3] = value_B;
    }
    
    return profile;
}

struct profile_info_struct* profile_command(FILE* output_file, FILE* error_file, char* pwd_dir, char* src_dir, char* target_dir, int watch_num, char** watch_array, char* precommand, time_t wait_pre_s, long wait_pre_ns, char* command, time_t wait_command_s, long wait_command_ns){
    if (src_dir != NULL){        
        misc_ensure_dir_exists(src_dir, 0, 0, output_file, error_file, __func__);
    }
    
    if (target_dir != NULL){
        misc_ensure_dir_exists(target_dir, 0, 0, output_file, error_file, __func__);
    }
    
    char saved_pwd[256];
    if (pwd_dir != NULL) {
        misc_ensure_dir_exists(pwd_dir, 0, 0, output_file, error_file, __func__);
    
        char* retc = getcwd(saved_pwd, 256);
        if (retc == NULL){
            log_warning(output_file, error_file, "%s - %s", __func__, "error getting saved_pwd");
        }
        int ret = chdir(pwd_dir);
        if (ret != 0){
            log_warning(output_file, error_file, "%s - %s", __func__, "error setting pwd with chdir");
        }
    }
    
    if (precommand != NULL){
        misc_exec(precommand);
    }
    
    misc_sleep(wait_pre_s);
    misc_nanosleep(wait_pre_ns);
    
    if (pwd_dir != NULL){
        int ret = chdir(saved_pwd);
        if (ret != 0){
            log_warning(output_file, error_file, "%s - %s", __func__, "error setting pwd to saved_pwd with chdir");
        }
    }
    struct stat_macb** multi_stat_before = get_multi_path_timestamps(watch_num, watch_array);
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    if (pwd_dir != NULL){
        int ret = chdir(pwd_dir);
        if (ret != 0){
            log_warning(output_file, error_file, "%s - %s", __func__, "error setting pwd with chdir");
        }
    }
    
    misc_exec(command);
    
    
    if (pwd_dir != NULL){
        int ret = chdir(saved_pwd);
        if (ret != 0){
            log_warning(output_file, error_file, "%s - %s", __func__, "error setting pwd to saved_pwd with chdir");
        }
    }
    
    struct stat_macb** multi_stat_after = get_multi_path_timestamps(watch_num, watch_array);
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    misc_sleep(wait_command_s);
    misc_nanosleep(wait_command_ns);
    
    struct stat_macb** multi_stat_after_delay = get_multi_path_timestamps(watch_num, watch_array);
    struct timespec* ts_after_delay = current_time_ns_fslike_osspecific();
    
    int** profile = compute_profile(ts_before, ts_after, ts_after_delay, watch_num, multi_stat_before, multi_stat_after, multi_stat_after_delay);
    struct profile_info_struct* pi = (struct profile_info_struct*) calloc(sizeof(struct profile_info_struct), 1);
    pi->profile = profile;
    pi->watch_num = watch_num;
    pi->watch_array = watch_array;
    pi->multi_stat_before = multi_stat_before;
    pi->multi_stat_after = multi_stat_after;
    pi->multi_stat_after_delay = multi_stat_after_delay;
    pi->ts_before = ts_before;
    pi->ts_after = ts_after;
    pi->ts_after_delay = ts_after_delay;
    
    return pi;
}

struct profile_init_struct* profile_init(int watch_num, char** watch_array){
    struct stat_macb** multi_stat_before = get_multi_path_timestamps(watch_num, watch_array);        
    struct timespec* ts_before = current_time_ns_fslike_osspecific();
    
    struct profile_init_struct* pis = (struct profile_init_struct*) calloc(sizeof(struct profile_init_struct), 1);
    pis->multi_stat_before = multi_stat_before;
    pis->ts_before = ts_before;
    
    return pis;
}

struct profile_info_struct* profile_analyze(struct profile_init_struct* pis, int watch_num, char** watch_array, time_t wait_command_s, long wait_command_ns){
    struct stat_macb** multi_stat_after = get_multi_path_timestamps(watch_num, watch_array);
    struct timespec* ts_after = current_time_ns_fslike_osspecific();
    
    misc_sleep(wait_command_s);
    misc_nanosleep(wait_command_ns);
    
    struct stat_macb** multi_stat_after_delay = get_multi_path_timestamps(watch_num, watch_array);
    struct timespec* ts_after_delay = current_time_ns_fslike_osspecific();
    
    int** profile = compute_profile(pis->ts_before, ts_after, ts_after_delay, watch_num, pis->multi_stat_before, multi_stat_after, multi_stat_after_delay);
    struct profile_info_struct* pi = (struct profile_info_struct*) calloc(sizeof(struct profile_info_struct), 1);
    pi->profile = profile;
    pi->watch_num = watch_num;
    pi->watch_array = watch_array;
    pi->multi_stat_before = pis->multi_stat_before;
    pi->multi_stat_after = multi_stat_after;
    pi->multi_stat_after_delay = multi_stat_after_delay;
    pi->ts_before = pis->ts_before;
    pi->ts_after = ts_after;
    pi->ts_after_delay = ts_after_delay;
    
    return pi;
}

#endif
