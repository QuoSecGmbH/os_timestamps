#ifndef U_ED_C
#define U_ED_C

#include "u_ed.h"

int check_utilities_ed_new_i_w_q(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.ed.new.i.w.q/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_targetdir = misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    char* path_file = misc_concat(path_targetdir, "file");
    
    char* command = "ed ../targetdir/file";
    
    char** watch_array = misc_char_array3(path_pwd, path_targetdir, path_file);
    int watch_num = 3;
    
    log_info(output_file, error_file, "ed will now be tested.");
    log_info(output_file, error_file, "Please:\n 1 - set input more (i then enter)\n 2 - type hello world\n 3 - quit input mode (. then enter)\n 4 - execute the write command (w then enter)\n 5 - wait 1s\n 6 - quit (q then enter)");
    log_info(output_file, error_file, "Press enter when ready.");
    getchar();
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, NULL, path_targetdir, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = UPDATE_MANDATORY;
    r2[1] = NOUPDATE_OPTIONAL;
    r2[2] = UPDATE_MANDATORY;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = UPDATE_MANDATORY;
    r3[1] = UPDATE_MANDATORY;
    r3[2] = UPDATE_MANDATORY;
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    requirements[2] = r3;
    
    struct timespec* ts_after = pi->ts_after;
    
    struct timespec ts_file_M = pi->multi_stat_after[2]->st_mtim;
    struct timespec ts_file_C = pi->multi_stat_after[2]->st_ctim;
    
    struct timespec* ts_500ms = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_500ms->tv_sec = 0;
    ts_500ms->tv_nsec = 5*ns_100ms;
    
    int resM = 0;
    struct timespec* diff_M = misc_timespec_diff_abs(ts_after, &ts_file_M);
    if (misc_timespec_geq(diff_M, ts_500ms) == 1){
        // abs difference is less than 500ms
        resM = 2;
    }
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, resM, pi, "resM");  
    
    int resC = 0;
    struct timespec* diff_C = misc_timespec_diff_abs(ts_after, &ts_file_C);
    if (misc_timespec_geq(diff_C, ts_500ms) == 1){
        // abs difference is less than 500ms
        resC = 2;
    }
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, resC, pi, "resC");  
    
    int result_req = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result_req, pi, "profile requirements");    
    
    int result = misc_max3(resM, resC, result_req);
    
    return result;
}

int check_utilities_ed_new_i_w_q_mac(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_file = misc_concat(dir_path, "utilities.ed.new.i.w.q/targetdir/file");
    
    struct stat_macb* file_stat = get_path_timestamps(path_file);
    if (file_stat == NULL){
        log_warning(output_file, error_file, "%s - could not do stat on %s", __func__, path_file);
        return 1;
    }
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat->st_mtim), &(file_stat->st_atim)) != 0 || misc_timespec_eq(&(file_stat->st_atim), &(file_stat->st_ctim)) != 0){
        result = 2;
    }
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, NULL, NULL, file_stat);
    
    free(path_file);
    free(file_stat);
    
    return result;
}

int check_utilities_ed_existing_i_w_q(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.ed.existing.i.w.q/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_targetdir = misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    char* path_file = misc_concat_ensure_file_exists_filled(path_targetdir, "file", 5, 0, 0, output_file, error_file, __func__);
    
    char* command = "ed ../targetdir/file";
    
    char** watch_array = misc_char_array3(path_pwd, path_targetdir, path_file);
    int watch_num = 3;
    
    log_info(output_file, error_file, "ed will now be tested.");
    log_info(output_file, error_file, "Please:\n 1 - set input more (i then enter)\n 2 - type hello world\n 3 - quit input mode (. then enter)\n 4 - execute the write command (w then enter)\n 5 - wait 1s\n 6 - quit (q then enter)");
    log_info(output_file, error_file, "Press enter when ready.");
    getchar();
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, NULL, path_targetdir, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = NOUPDATE_OPTIONAL;
    r2[1] = NOUPDATE_OPTIONAL;
    r2[2] = NOUPDATE_OPTIONAL;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = UPDATE_MANDATORY;
    r3[1] = UPDATE_MANDATORY;
    r3[2] = UPDATE_MANDATORY;
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    requirements[2] = r3;
    
    struct timespec* ts_before = pi->ts_before;
    struct timespec* ts_after = pi->ts_after;
    
    struct timespec ts_file_M = pi->multi_stat_after[2]->st_mtim;
    struct timespec ts_file_A = pi->multi_stat_after[2]->st_atim;
    struct timespec ts_file_C = pi->multi_stat_after[2]->st_ctim;
    
    struct timespec* ts_500ms = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_500ms->tv_sec = 0;
    ts_500ms->tv_nsec = 5*ns_100ms;
    
    int resM = 0;
    struct timespec* diff_M = misc_timespec_diff_abs(ts_after, &ts_file_M);
    if (misc_timespec_geq(diff_M, ts_500ms) == 1){
        // abs difference is less than 500ms
        resM = 2;
    }
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, resM, pi, "resM");  
    
    int resA = 0;
    struct timespec* diff_A = misc_timespec_diff_abs(ts_before, &ts_file_A);
    if (misc_timespec_geq(diff_A, ts_500ms) != 1){
        // abs difference is more than 500ms
        resA = 2;
    }
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, resA, pi, "resA");  
    
    int resC = 0;
    struct timespec* diff_C = misc_timespec_diff_abs(ts_after, &ts_file_C);
    if (misc_timespec_geq(diff_C, ts_500ms) == 1){
        // abs difference is more less 500ms
        resC = 2;
    }
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, resC, pi, "resC");  
    
    int result_req = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result_req, pi, "profile requirements");    
    
    int result = misc_max4(resM, resA, resC, result_req);
    
    return result;
}

int check_utilities_ed_existing_i_w_q_mc(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_file = misc_concat(dir_path, "utilities.ed.existing.i.w.q/targetdir/file");
    
    struct stat_macb* file_stat = get_path_timestamps(path_file);
    if (file_stat == NULL){
        log_warning(output_file, error_file, "%s - could not do stat on %s", __func__, path_file);
        return 1;
    }
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat->st_mtim), &(file_stat->st_ctim)) != 0){
        result = 2;
    }
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, NULL, NULL, file_stat);
    
    free(path_file);
    free(file_stat);
    
    return result;
}

int check_utilities_ed_existing_i_wq(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.ed.existing.i.wq/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_targetdir = misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    char* path_file = misc_concat_ensure_file_exists_filled(path_targetdir, "file", 5, 0, 0, output_file, error_file, __func__);
    
    char* command = "ed ../targetdir/file";
    
    char** watch_array = misc_char_array3(path_pwd, path_targetdir, path_file);
    int watch_num = 3;
    
    log_info(output_file, error_file, "ed will now be tested.");
    log_info(output_file, error_file, "Please:\n 1 - set input more (i then enter)\n 2 - type hello world\n 3 - quit input mode (. then enter)\n 4 - wait 1s\n 5 - execute the write and quit command (wq then enter)");
    log_info(output_file, error_file, "Press enter when ready.");
    getchar();
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, NULL, path_targetdir, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = NOUPDATE_OPTIONAL;
    r2[1] = NOUPDATE_OPTIONAL;
    r2[2] = NOUPDATE_OPTIONAL;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = UPDATE_MANDATORY;
    r3[1] = UPDATE_MANDATORY;
    r3[2] = UPDATE_MANDATORY;
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    requirements[2] = r3;
    
    struct timespec* ts_before = pi->ts_before;
    struct timespec* ts_after = pi->ts_after;
    
    struct timespec ts_file_M = pi->multi_stat_after[2]->st_mtim;
    struct timespec ts_file_A = pi->multi_stat_after[2]->st_atim;
    struct timespec ts_file_C = pi->multi_stat_after[2]->st_ctim;
    
    struct timespec* ts_500ms = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_500ms->tv_sec = 0;
    ts_500ms->tv_nsec = 5*ns_100ms;
    
    int resM = 0;
    struct timespec* diff_M = misc_timespec_diff_abs(ts_after, &ts_file_M);
    if (misc_timespec_geq(diff_M, ts_500ms) != 1){
        // abs difference is less than 500ms
        resM = 2;
    }
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, resM, pi, "resM");  
    
    int resA = 0;
    struct timespec* diff_A = misc_timespec_diff_abs(ts_before, &ts_file_A);
    if (misc_timespec_geq(diff_A, ts_500ms) != 1){
        // abs difference is more than 500ms
        resA = 2;
    }
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, resA, pi, "resA");  
    
    int resC = 0;
    struct timespec* diff_C = misc_timespec_diff_abs(ts_after, &ts_file_C);
    if (misc_timespec_geq(diff_C, ts_500ms) != 1){
        // abs difference is more less 500ms
        resC = 2;
    }
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, resC, pi, "resC");  
    
    int result_req = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result_req, pi, "profile requirements");    
    
    int result = misc_max4(resM, resA, resC, result_req);
    
    return result;
}

int check_utilities_ed_existing_i_wq_mc(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_file = misc_concat(dir_path, "utilities.ed.existing.i.wq/targetdir/file");
    
    struct stat_macb* file_stat = get_path_timestamps(path_file);
    if (file_stat == NULL){
        log_warning(output_file, error_file, "%s - could not do stat on %s", __func__, path_file);
        return 1;
    }
    
    int result = 0;
    if (misc_timespec_eq(&(file_stat->st_mtim), &(file_stat->st_ctim)) != 0){
        result = 2;
    }
    log_info_ts_stat_on_error(output_file, error_file, __func__, result, NULL, NULL, file_stat);
    
    free(path_file);
    free(file_stat);
    
    return result;
}

int check_utilities_ed_existing_i_Q(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.ed.existing.i.Q/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_targetdir = misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    char* path_file = misc_concat_ensure_file_exists_filled(path_targetdir, "file", 5, 0, 0, output_file, error_file, __func__);
    
    char* command = "ed ../targetdir/file";
    
    char** watch_array = misc_char_array3(path_pwd, path_targetdir, path_file);
    int watch_num = 3;
    
    log_info(output_file, error_file, "ed will now be tested.");
    log_info(output_file, error_file, "Please:\n 1 - set input more (i then enter)\n 2 - type hello world\n 3 - quit input mode (. then enter)\n 4 - execute the quit with no write (Q then enter)");
    log_info(output_file, error_file, "Press enter when ready.");
    getchar();
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, NULL, path_targetdir, watch_num, watch_array, NULL, 0, ns_after_open, command, CMD_DELAY_S, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = NOUPDATE_OPTIONAL;
    r2[1] = NOUPDATE_OPTIONAL;
    r2[2] = NOUPDATE_OPTIONAL;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = NOUPDATE_MANDATORY;
    r3[1] = UPDATE_MANDATORY;
    r3[2] = NOUPDATE_MANDATORY;
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    requirements[2] = r3;
    
    struct timespec* ts_before = pi->ts_before;
    
    struct timespec ts_file_A = pi->multi_stat_after[2]->st_atim;
    
    struct timespec* ts_500ms = (struct timespec*) calloc(sizeof(struct timespec), 1);
    ts_500ms->tv_sec = 0;
    ts_500ms->tv_nsec = 5*ns_100ms;
    
    int resA = 0;
    struct timespec* diff_A = misc_timespec_diff_abs(ts_before, &ts_file_A);
    if (misc_timespec_geq(diff_A, ts_500ms) != 1){
        // abs difference is more than 500ms
        resA = 2;
    }
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, resA, pi, "resA");  
    
    
    int result_req = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result_req, pi, "profile requirements");    
    
    int result = misc_max2(resA, result_req);
    
    return result;
}


#endif
