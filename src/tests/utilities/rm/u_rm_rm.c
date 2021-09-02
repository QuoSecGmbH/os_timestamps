#ifndef U_RM_C
#define U_RM_C

#include "u_rm_rm.h"

int check_utilities_rm_rm_dir_empty(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.rm.rm.dir.emtpy/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_targetdir = misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    
    char* path_dir_rm = misc_concat_ensure_dir_exists(path_targetdir, "dir/", 0, 0, output_file, error_file, __func__);
    
    char* command = "rm ../targetdir/dir/";
    
    char** watch_array = misc_char_array3(path_pwd, path_targetdir, path_dir_rm);
    int watch_num = 3;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, NULL, path_targetdir, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = NOUPDATE_MANDATORY;
    r2[1] = NOUPDATE_MANDATORY;
    r2[2] = NOUPDATE_MANDATORY;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = NOUPDATE_MANDATORY;
    r3[1] = NOUPDATE_MANDATORY;
    r3[2] = NOUPDATE_MANDATORY;
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    requirements[2] = r3;
    
    int result = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}

int check_utilities_rm_rm_r_dir_empty(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.rm.rm.r.dir.emtpy/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_targetdir = misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    
    misc_concat_ensure_dir_exists(path_targetdir, "dir/", 0, 0, output_file, error_file, __func__);
    
    char* command = "rm -r ../targetdir/dir/";
    
    char** watch_array = misc_char_array2(path_pwd, path_targetdir);
    int watch_num = 2;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, NULL, path_targetdir, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = UPDATE_MANDATORY;
    r2[1] = NOUPDATE_MANDATORY;
    r2[2] = UPDATE_MANDATORY;
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    
    int result = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}

int check_utilities_rm_rm_r_dir_notempty(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.rm.rm.r.dir.notemtpy/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_targetdir = misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    
    char* path_dir_rm = misc_concat_ensure_dir_exists(path_targetdir, "dir/", 0, 0, output_file, error_file, __func__);
    misc_concat_ensure_file_exists_filled(path_dir_rm, "file", 10, 0, 0, output_file, error_file, __func__);
    
    char* command = "rm -r ../targetdir/dir/";
    
    char** watch_array = misc_char_array2(path_pwd, path_targetdir);
    int watch_num = 2;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, NULL, path_targetdir, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = UPDATE_MANDATORY;
    r2[1] = NOUPDATE_MANDATORY;
    r2[2] = UPDATE_MANDATORY;
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    
    int result = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}

int check_utilities_rm_rm_file_last(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.rm.rm.file.last/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_targetdir = misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    
    misc_concat_ensure_file_exists_filled(path_targetdir, "file", 10, 0, 0, output_file, error_file, __func__);
    
    char* command = "rm ../targetdir/file";
    
    char** watch_array = misc_char_array2(path_pwd, path_targetdir);
    int watch_num = 2;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, NULL, path_targetdir, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = UPDATE_MANDATORY;
    r2[1] = NOUPDATE_MANDATORY;
    r2[2] = UPDATE_MANDATORY;
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    
    int result = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}

int check_utilities_rm_rm_file_notlast(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.rm.rm.file.notlast/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_targetdir = misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    
    char* path_file = misc_concat_ensure_file_exists_filled(path_targetdir, "file", 10, 0, 0, output_file, error_file, __func__);
    char* path_link = misc_concat(path_targetdir, (char*) "link");
    int r = link(path_file, path_link);
    if (r != 0){
        log_warning(output_file, error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    
    char* command = "rm ../targetdir/link";
    
    char** watch_array = misc_char_array3(path_pwd, path_targetdir, path_file);
    int watch_num = 3;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, NULL, path_targetdir, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = UPDATE_OPTIONAL;
    r2[1] = NOUPDATE_OPTIONAL;
    r2[2] = UPDATE_OPTIONAL;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = NOUPDATE_OPTIONAL;
    r3[1] = NOUPDATE_OPTIONAL;
    r3[2] = UPDATE_MANDATORY;
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    requirements[2] = r3;
    
    int result = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}

int check_utilities_rm_rm_file_notlast_dir(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.rm.rm.file.notlast.dir/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_targetdir = misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    
    char* path_file = misc_concat_ensure_file_exists_filled(path_targetdir, "file", 10, 0, 0, output_file, error_file, __func__);
    char* path_link = misc_concat(path_targetdir, (char*) "link");
    int r = link(path_file, path_link);
    if (r != 0){
        log_warning(output_file, error_file, "%s - %s", __func__, "error creating link");
        return 1;
    }
    
    char* command = "rm ../targetdir/link";
    
    char** watch_array = misc_char_array3(path_pwd, path_targetdir, path_file);
    int watch_num = 3;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, NULL, path_targetdir, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = UPDATE_MANDATORY;
    r2[1] = NOUPDATE_OPTIONAL;
    r2[2] = UPDATE_MANDATORY;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = NOUPDATE_OPTIONAL;
    r3[1] = NOUPDATE_OPTIONAL;
    r3[2] = UPDATE_OPTIONAL;
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    requirements[2] = r3;
    
    int result = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}



#endif
