#ifndef PROFILE_OS_C
#define PROFILE_OS_C

#include "profile_os.h"

int main (int argc, char **argv){
    if (argc >= 2){
        VERBOSE=1;
    }
  
    FILE* csv_file = log_open_csv("os_profile_results.csv");
    FILE* output_file = stdout;
//     FILE* output_file = fopen("os_profile_output.txt", "wb");
    FILE* error_file = stderr;
//     FILE* error_file = fopen("os_profile_error.txt", "wb");
  
    int i;
    char* dir_base_path = "tmp_os_profile";
    char* dir_path = NULL;
    for (i = 0; i <= 99; i++){
        char* buf = (char*) calloc(sizeof(char), strlen(dir_base_path)+6);
        sprintf(buf, "%s_%02d/", dir_base_path, i);
        struct stat* attr = (struct stat*) calloc(sizeof(struct stat), 1);
        if (stat(buf, attr) == -1) {
            mkdir(buf, 0700);
            dir_path = buf;
            free(attr);
            break;
        }
        free(buf);
        free(attr);
    }
    
    if (dir_path == NULL){
        log_error(output_file, error_file, "%s", "Impossible to find suitable directory for tests, exiting.");
        return 1;
    }
    log_info(output_file, error_file, "Directory for tests is: %s", dir_path);
    
    // pre-creating some of the test files
//     misc_concat_ensure_file_exists_free(dir_path, "interfaces.futimens", s_0s, ns_0ns, output_file, error_file, __func__);

//     misc_concat_ensure_file_exists_free(dir_path, "profile_os_pause", 2*s_1s, ns_0ns, output_file, error_file, __func__);
    
    testenv_struct* test_env = testenv_alloc(csv_file, output_file, error_file, dir_path);
    
//     log_csv_add_line(csv_file, 6, "Passed?", "Description", "Specified?", "Spec", "Level", "Ref", "Function");

    group_profileos_filerename(test_env);
    
    
   
//     free(test_env);
//     free(dir_path);
    
    log_close_csv(csv_file);
}

void group_profileos_filerename(testenv_struct* env){
    struct profile_info_struct* pi = profileos_filerename_interface_noreplace(env);
    char** mask = misc_char_array3("src", "dst", "dir");
    
//     misc_print_profile_masked(env->output_file, env->error_file, pi, mask);
//     if (VERBOSE){
//         log_info_ts_profile_on_error_message(env->output_file, env->error_file, "profile_cmd", 0, pi, "");
//     }
    
    struct profile_info_struct* pi2 = profileos_filerename_interface_replace(env);
    process_profiles2(mask, pi, pi2);
//     misc_print_profile_masked(env->output_file, env->error_file, pi2, mask);
//     if (VERBOSE){
//         log_info_ts_profile_on_error_message(env->output_file, env->error_file, "profile_cmd", 0, pi2, "");
//     }
}

#endif
