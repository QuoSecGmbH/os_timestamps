#ifndef U_LN_CH
#define U_LN_C

#include "u_ln.h"

int check_utilities_ln_new(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.ln.new/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_srcdir = (char*) misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, output_file, error_file, __func__);
    char* path_file = misc_concat_ensure_file_exists_filled(path_srcdir, "file", 7, s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_targetdir = (char*) misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    char* path_link = (char*) misc_concat(path_targetdir, "link");
    
    char* command = "ln ../srcdir/file ../targetdir/link";
    
    char** watch_array = misc_char_array5(path_file, path_pwd, path_srcdir, path_targetdir, path_link);
    int watch_num = 5;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, path_srcdir, path_targetdir, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = UPDATE_MANDATORY;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = NOUPDATE_OPTIONAL;
    r2[1] = NOUPDATE_OPTIONAL;
    r2[2] = NOUPDATE_OPTIONAL;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = NOUPDATE_OPTIONAL;
    r3[1] = NOUPDATE_OPTIONAL;
    r3[2] = NOUPDATE_OPTIONAL;
    int* r4 = calloc(sizeof(int), 3);
    r4[0] = UPDATE_MANDATORY;
    r4[1] = NOUPDATE_OPTIONAL;
    r4[2] = UPDATE_MANDATORY;
    int* r5 = calloc(sizeof(int), 3);
    r5[0] = NOUPDATE_OPTIONAL;
    r5[1] = NOUPDATE_OPTIONAL;
    r5[2] = UPDATE_MANDATORY;
    
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    requirements[2] = r3;
    requirements[3] = r4;
    requirements[4] = r5;
    
    int result = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}

int check_utilities_ln_existing(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.ln.existing/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_srcdir = (char*) misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, output_file, error_file, __func__);
    char* path_file = misc_concat_ensure_file_exists_filled(path_srcdir, "file", 7, s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_targetdir = (char*) misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    char* path_link = (char*) misc_concat_ensure_file_exists(path_targetdir, "target", 0, 0, output_file, error_file, __func__);
    
    char* command = "ln ../srcdir/file ../targetdir/target";
    
    char** watch_array = misc_char_array5(path_file, path_pwd, path_srcdir, path_targetdir, path_link);
    int watch_num = 5;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, path_srcdir, path_targetdir, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = NOUPDATE_OPTIONAL;
    r2[1] = NOUPDATE_OPTIONAL;
    r2[2] = NOUPDATE_OPTIONAL;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = NOUPDATE_OPTIONAL;
    r3[1] = NOUPDATE_OPTIONAL;
    r3[2] = NOUPDATE_OPTIONAL;
    int* r4 = calloc(sizeof(int), 3);
    r4[0] = NOUPDATE_MANDATORY;
    r4[1] = NOUPDATE_MANDATORY;
    r4[2] = NOUPDATE_MANDATORY;
    int* r5 = calloc(sizeof(int), 3);
    r5[0] = NOUPDATE_MANDATORY;
    r5[1] = NOUPDATE_MANDATORY;
    r5[2] = NOUPDATE_MANDATORY;
    
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    requirements[2] = r3;
    requirements[3] = r4;
    requirements[4] = r5;
    
    int result = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}

int check_utilities_ln_s_new(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.ln.s.new/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_srcdir = (char*) misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, output_file, error_file, __func__);
    char* path_file = misc_concat_ensure_file_exists_filled(path_srcdir, "file", 7, s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_targetdir = (char*) misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    char* path_link = (char*) misc_concat(path_targetdir, "link");
    
    char* command = "ln -s ../srcdir/file ../targetdir/link";
    
    char** watch_array = misc_char_array5(path_file, path_pwd, path_srcdir, path_targetdir, path_link);
    int watch_num = 5;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, path_srcdir, path_targetdir, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = NOUPDATE_OPTIONAL;
    r2[1] = NOUPDATE_OPTIONAL;
    r2[2] = NOUPDATE_OPTIONAL;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = NOUPDATE_OPTIONAL;
    r3[1] = NOUPDATE_OPTIONAL;
    r3[2] = NOUPDATE_OPTIONAL;
    int* r4 = calloc(sizeof(int), 3);
    r4[0] = UPDATE_MANDATORY;
    r4[1] = NOUPDATE_OPTIONAL;
    r4[2] = UPDATE_MANDATORY;
    int* r5 = calloc(sizeof(int), 3);
    r5[0] = UPDATE_MANDATORY;
    r5[1] = UPDATE_MANDATORY;
    r5[2] = UPDATE_MANDATORY;
    
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    requirements[2] = r3;
    requirements[3] = r4;
    requirements[4] = r5;
    
    int result = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}
int check_utilities_ln_s_existing(FILE* csv_file, FILE* output_file, FILE* error_file, char* dir_path){
    char* path_dir = misc_concat_ensure_dir_exists(dir_path, "utilities.ln.s.existing/", 0, 0, output_file, error_file, __func__);
    
    char* path_pwd = (char*) misc_concat(path_dir, "pwd/");
    char* path_srcdir = (char*) misc_concat_ensure_dir_exists(path_dir, "srcdir/", 0, 0, output_file, error_file, __func__);
    char* path_file = misc_concat_ensure_file_exists_filled(path_srcdir, "file", 7, s_0s, ns_0ns, output_file, error_file, __func__);
    char* path_targetdir = (char*) misc_concat_ensure_dir_exists(path_dir, "targetdir/", 0, 0, output_file, error_file, __func__);
    char* path_link = (char*) misc_concat_ensure_file_exists(path_targetdir, "target", 0, 0, output_file, error_file, __func__);
    
    char* command = "ln -s ../srcdir/file ../targetdir/target";
    
    char** watch_array = misc_char_array5(path_file, path_pwd, path_srcdir, path_targetdir, path_link);
    int watch_num = 5;
    
    struct profile_info_struct* pi = profile_command(output_file, error_file, path_pwd, path_srcdir, path_targetdir, watch_num, watch_array, NULL, ns_DELAY, command, CMD_DELAY_NS);
    
    int* r1 = calloc(sizeof(int), 3);
    r1[0] = NOUPDATE_OPTIONAL;
    r1[1] = NOUPDATE_OPTIONAL;
    r1[2] = NOUPDATE_OPTIONAL;
    int* r2 = calloc(sizeof(int), 3);
    r2[0] = NOUPDATE_OPTIONAL;
    r2[1] = NOUPDATE_OPTIONAL;
    r2[2] = NOUPDATE_OPTIONAL;
    int* r3 = calloc(sizeof(int), 3);
    r3[0] = NOUPDATE_OPTIONAL;
    r3[1] = NOUPDATE_OPTIONAL;
    r3[2] = NOUPDATE_OPTIONAL;
    int* r4 = calloc(sizeof(int), 3);
    r4[0] = NOUPDATE_MANDATORY;
    r4[1] = NOUPDATE_MANDATORY;
    r4[2] = NOUPDATE_MANDATORY;
    int* r5 = calloc(sizeof(int), 3);
    r5[0] = NOUPDATE_MANDATORY;
    r5[1] = NOUPDATE_MANDATORY;
    r5[2] = NOUPDATE_MANDATORY;
    
    
    int ** requirements = calloc(sizeof(int*), watch_num);
    requirements[0] = r1;
    requirements[1] = r2;
    requirements[2] = r3;
    requirements[3] = r4;
    requirements[4] = r5;
    
    int result = misc_check_profile_requirements(output_file, error_file, __func__, pi, requirements);
    log_info_ts_profile_on_error_message(output_file, error_file, __func__, result, pi, "");
    return result;
}

#endif
